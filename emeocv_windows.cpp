/*
 * emeocv_windows.cpp - Windows-portierte Version mit OCR-Funktionalität
 * Erweiterte Version von camera_test.cpp mit vollständiger OCR-Pipeline
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

// Windows-spezifische Includes
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <sys/stat.h>
#define usleep(x) Sleep((x) / 1000)
#define stat _stat
#define S_ISDIR(m) (((m) & _S_IFMT) == _S_IFDIR)
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

// Vereinfachte Config-Klasse für Windows
class SimpleConfig {
public:
    SimpleConfig() : 
        _digitMinHeight(25), 
        _digitMaxHeight(35),
        _digitYAlignment(32),
        _rotationDegrees(0),
        _cannyThreshold1(100),
        _cannyThreshold2(200),
        _ocrMaxDist(80000.0f),
        _trainingDataFilename("training.yml"),
        _testMode(false) {}

    int getDigitMinHeight() const { return _digitMinHeight; }
    int getDigitMaxHeight() const { return _digitMaxHeight; }
    int getDigitYAlignment() const { return _digitYAlignment; }
    int getRotationDegrees() const { return _rotationDegrees; }
    int getCannyThreshold1() const { return _cannyThreshold1; }
    int getCannyThreshold2() const { return _cannyThreshold2; }
    float getOcrMaxDist() const { return _ocrMaxDist; }
    std::string getTrainingDataFilename() const { return _trainingDataFilename; }
    bool getTestMode() const { return _testMode; }

private:
    int _digitMinHeight;
    int _digitMaxHeight;
    int _digitYAlignment;
    int _rotationDegrees;
    int _cannyThreshold1;
    int _cannyThreshold2;
    float _ocrMaxDist;
    std::string _trainingDataFilename;
    bool _testMode;
};

// Vereinfachte ImageProcessor-Klasse
class SimpleImageProcessor {
public:
    SimpleImageProcessor(const SimpleConfig& config) : _config(config) {}

    void setInput(cv::Mat& img) {
        _img = img.clone();
        if (_img.channels() == 3) {
            cv::cvtColor(_img, _imgGray, cv::COLOR_BGR2GRAY);
        } else {
            _imgGray = _img.clone();
        }
    }

    void process() {
        _digits.clear();
        
        // Bildvorverarbeitung
        cv::Mat processed;
        cv::GaussianBlur(_imgGray, processed, cv::Size(5, 5), 0);
        cv::threshold(processed, processed, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
        
        // Konturen finden
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(processed, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        // Bounding boxes für potentielle Ziffern
        std::vector<cv::Rect> boundingBoxes;
        for (const auto& contour : contours) {
            cv::Rect rect = cv::boundingRect(contour);
            
            // Filter für Zifferngrößen
            if (rect.height >= _config.getDigitMinHeight() && 
                rect.height <= _config.getDigitMaxHeight() &&
                rect.width >= 10 && rect.width <= 30) {
                boundingBoxes.push_back(rect);
            }
        }
        
        // Sortiere von links nach rechts
        std::sort(boundingBoxes.begin(), boundingBoxes.end(), 
                  [](const cv::Rect& a, const cv::Rect& b) { return a.x < b.x; });
        
        // Extrahiere Ziffern
        for (const auto& rect : boundingBoxes) {
            cv::Mat digit = _imgGray(rect);
            cv::Mat resized;
            cv::resize(digit, resized, cv::Size(20, 30));
            _digits.push_back(resized);
        }
        
        std::cout << "Gefunden " << _digits.size() << " potentielle Ziffern" << std::endl;
    }

    const std::vector<cv::Mat>& getOutput() const { return _digits; }

private:
    cv::Mat _img;
    cv::Mat _imgGray;
    std::vector<cv::Mat> _digits;
    SimpleConfig _config;
};

// Vereinfachte OCR-Klasse ohne ML (erstmal nur Mock)
class SimpleOCR {
public:
    SimpleOCR(const SimpleConfig& config) : _config(config) {}

    std::string recognize(const std::vector<cv::Mat>& digits) {
        std::string result;
        
        for (size_t i = 0; i < digits.size(); ++i) {
            // Einfache Mock-Erkennung basierend auf Pixelintensität
            cv::Scalar meanIntensity = cv::mean(digits[i]);
            int digit = static_cast<int>(meanIntensity[0] / 25.5) % 10;
            result += std::to_string(digit);
            
            // Punkt nach der 4. Ziffer (typisch für kWh-Zähler)
            if (i == 3 && digits.size() > 4) {
                result += ".";
            }
        }
        
        return result.empty() ? "------" : result;
    }

private:
    SimpleConfig _config;
};

// Vereinfachte Plausibilitätsprüfung
class SimplePlausi {
public:
    SimplePlausi() : _lastValue(0.0), _hasLastValue(false) {}

    bool check(const std::string& result, time_t timestamp) {
        if (result == "------" || result.empty()) {
            return false;
        }

        try {
            double value = std::stod(result);
            
            if (!_hasLastValue) {
                _checkedValue = value;
                _lastValue = value;
                _hasLastValue = true;
                return true;
            }
            
            // Einfache Plausibilitätsprüfung: Wert sollte nicht rückwärts gehen
            // und nicht zu stark springen
            double diff = value - _lastValue;
            if (diff < -0.1 || diff > 100.0) {
                return false;
            }
            
            _checkedValue = value;
            _lastValue = value;
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }

    double getCheckedValue() const { return _checkedValue; }

private:
    double _lastValue;
    double _checkedValue;
    bool _hasLastValue;
};

// Hauptfunktion für OCR-Verarbeitung
void processWithOCR() {
    std::cout << "=== EME OCR Windows Version mit Kamera ===" << std::endl;
    
    SimpleConfig config;
    SimpleImageProcessor processor(config);
    SimpleOCR ocr(config);
    SimplePlausi plausi;
    
    // Kamera initialisieren
    cv::VideoCapture cap;
    
    // Versuche verschiedene Kamera-Backends
    std::vector<int> backends = {cv::CAP_DSHOW, cv::CAP_MSMF, cv::CAP_ANY};
    bool cameraOpened = false;
    
    for (int backend : backends) {
        cap.open(0, backend);
        if (cap.isOpened()) {
            std::cout << "Kamera geöffnet mit Backend: " << backend << std::endl;
            cameraOpened = true;
            break;
        }
    }
    
    if (!cameraOpened) {
        std::cout << "Fehler: Kamera konnte nicht geöffnet werden!" << std::endl;
        std::cout << "Drücke Enter zum Beenden..." << std::endl;
        std::cin.get();
        return;
    }
    
    // Kamera-Einstellungen
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 30);
    
    std::cout << "Kamera-Auflösung: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) 
              << "x" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << "Drücke 'q' zum Beenden, 's' zum Speichern eines Bildes" << std::endl;
    
    cv::Mat frame, processedFrame;
    int frameCount = 0;
    
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cout << "Warnung: Leerer Frame empfangen" << std::endl;
            continue;
        }
        
        frameCount++;
        
        // Bild verarbeiten
        processor.setInput(frame);
        processor.process();
        
        // OCR nur alle 30 Frames (ca. 1x pro Sekunde)
        if (frameCount % 30 == 0) {
            std::string result = ocr.recognize(processor.getOutput());
            time_t now = time(nullptr);
            
            std::cout << "OCR-Ergebnis: " << result;
            
            if (plausi.check(result, now)) {
                std::cout << " -> " << std::fixed << std::setprecision(3) 
                          << plausi.getCheckedValue() << " kWh" << std::endl;
            } else {
                std::cout << " -> [nicht plausibel]" << std::endl;
            }
        }
        
        // Kamerabild anzeigen
        cv::imshow("EME OCR - Kamera", frame);
        
        // Tastatureingabe verarbeiten
        int key = cv::waitKey(1) & 0xFF;
        if (key == 'q' || key == 27) { // 'q' oder ESC
            std::cout << "Beende Programm..." << std::endl;
            break;
        } else if (key == 's') {
            // Bild speichern
            std::time_t now = std::time(nullptr);
            std::string filename = "capture_" + std::to_string(now) + ".jpg";
            cv::imwrite(filename, frame);
            std::cout << "Bild gespeichert: " << filename << std::endl;
        }
        
        usleep(33000); // ~30 FPS
    }
    
    cap.release();
    cv::destroyAllWindows();
}

int main(int argc, char* argv[]) {
    std::cout << "EME OCR für Windows" << std::endl;
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    std::cout << "Starte Kamera-Initialisierung..." << std::endl;
    
    try {
        processWithOCR();
    } catch (const cv::Exception& e) {
        std::cerr << "OpenCV Fehler: " << e.what() << std::endl;
        std::cout << "Drücke Enter zum Beenden..." << std::endl;
        std::cin.get();
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "Allgemeiner Fehler: " << e.what() << std::endl;
        std::cout << "Drücke Enter zum Beenden..." << std::endl;
        std::cin.get();
        return -1;
    }
    
    std::cout << "Programm beendet." << std::endl;
    return 0;
}