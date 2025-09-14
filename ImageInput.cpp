/*
 * ImageInput.cpp
 *
 */

#include <ctime>
#include <string>
#include <list>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

#include "ImageInput.h"

ImageInput::~ImageInput() {
}

cv::Mat& ImageInput::getImage() {
    return _img;
}

time_t ImageInput::getTime() {
    return _time;
}

void ImageInput::setOutputDir(const std::string & outDir) {
    _outDir = outDir;
}

void ImageInput::saveImage() {
    struct tm date;
    localtime_r(&_time, &date);
    char filename[PATH_MAX];
    strftime(filename, PATH_MAX, "/%Y%m%d-%H%M%S.png", &date);
    std::string path = _outDir + filename;
    if (cv::imwrite(path, _img)) {
        log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "Image saved to " + path;
    } else {
        log4cpp::Category::getRoot() << log4cpp::Priority::ERROR << "Failed to save image to " + path;
    }
}

DirectoryInput::DirectoryInput(const Directory& directory) :
        _directory(directory) {
    _filenameList = _directory.list();
    _filenameList.sort();
    _itFilename = _filenameList.begin();
}

bool DirectoryInput::nextImage() {
    if (_itFilename == _filenameList.end()) {
        return false;
    }
    std::string path = _directory.fullpath(*_itFilename);

    _img = cv::imread(path.c_str());

    // read time from file name
    struct tm date;
    memset(&date, 0, sizeof(date));
    date.tm_year = atoi(_itFilename->substr(0, 4).c_str()) - 1900;
    date.tm_mon = atoi(_itFilename->substr(4, 2).c_str()) - 1;
    date.tm_mday = atoi(_itFilename->substr(6, 2).c_str());
    date.tm_hour = atoi(_itFilename->substr(9, 2).c_str());
    date.tm_min = atoi(_itFilename->substr(11, 2).c_str());
    date.tm_sec = atoi(_itFilename->substr(13, 2).c_str());
    _time = mktime(&date);

    log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "Processing " << *_itFilename << " of " << ctime(&_time);

    // save copy of image if requested
    if (!_outDir.empty()) {
        saveImage();
    }

    _itFilename++;
    return true;
}

CameraInput::CameraInput(int device) {
    // Raspberry Pi Kamera-Erfassung über rpicam (moderne libcamera)
    bool opened = false;
    
    log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "Versuche Pi-Kamera zu öffnen...";
    
    // Da OpenCV mit der modernen Pi-Kamera Probleme hat,
    // verwenden wir rpicam-still für einzelne Aufnahmen
    _useRpicam = true;
    
    // Test ob rpicam funktioniert
    std::string testCmd = "rpicam-still -o /tmp/pi_camera_test.jpg" +
                         std::string(" --width 640 --height 480") +
                         " --timeout 2 --nopreview" +
                         " --autofocus-mode auto" +
                         " --autofocus-range normal" +
                         " --autofocus-speed normal" +  // Normaler Fokus für Initialisierung
                         " > /dev/null 2>&1";
    int result = system(testCmd.c_str());
    
    if (result == 0) {
        // Test ob Datei erstellt wurde
        cv::Mat testImg = cv::imread("/tmp/pi_camera_test.jpg");
        if (!testImg.empty()) {
            opened = true;
            log4cpp::Category::getRoot() << log4cpp::Priority::INFO 
                << "Pi Kamera erfolgreich über rpicam-still geöffnet (Größe: " 
                << testImg.cols << "x" << testImg.rows << ")";
            // Testdatei wieder löschen
            system("rm -f /tmp/pi_camera_test.jpg");
        } else {
            log4cpp::Category::getRoot() << log4cpp::Priority::WARN << "rpicam-still: Testbild konnte nicht geladen werden";
        }
    } else {
        log4cpp::Category::getRoot() << log4cpp::Priority::WARN << "rpicam-still: Kommando fehlgeschlagen";
    }
    
    // Fallback: Versuche trotzdem OpenCV V4L2 (für den Fall dass es doch funktioniert)
    if (!opened) {
        log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "rpicam fehlgeschlagen, versuche OpenCV V4L2...";
        _useRpicam = false;
        
        _capture.open(0, cv::CAP_V4L2);
        if (_capture.isOpened()) {
            _capture.set(cv::CAP_PROP_BUFFERSIZE, 1);
            
            cv::Mat testFrame;
            // Mehrere Versuche mit größeren Pausen
            for (int i = 0; i < 10 && !opened; i++) {
                usleep(500000); // 500ms zwischen Versuchen
                if (_capture.read(testFrame) && !testFrame.empty()) {
                    opened = true;
                    log4cpp::Category::getRoot() << log4cpp::Priority::INFO 
                        << "Pi Kamera erfolgreich über V4L2 geöffnet nach " << (i+1) << " Versuchen";
                    break;
                }
            }
            
            if (!opened) {
                _capture.release();
                log4cpp::Category::getRoot() << log4cpp::Priority::WARN << "V4L2: Alle Versuche fehlgeschlagen";
            }
        }
    }
    
    // Letzte Option: Simulationsmodus
    if (!opened) {
        log4cpp::Category::getRoot() << log4cpp::Priority::ERROR 
            << "Pi Kamera konnte nicht geöffnet werden! Prüfen Sie:";
        log4cpp::Category::getRoot() << log4cpp::Priority::ERROR 
            << "1. Kamera angeschlossen und aktiviert (raspi-config)";
        log4cpp::Category::getRoot() << log4cpp::Priority::ERROR 
            << "2. rpicam-still verfügbar und funktionsfähig";
        
        // Für Entwicklung: Verwende ein statisches Testbild falls verfügbar
        cv::Mat testImg = cv::imread("test_images/test.png");
        if (!testImg.empty()) {
            log4cpp::Category::getRoot() << log4cpp::Priority::WARN 
                << "Verwende Testbild für Entwicklung";
            _testMode = true;
            _testImage = testImg.clone();
            opened = true; // Für die Anwendungslogik
        }
    }
}

bool CameraInput::nextImage() {
    time(&_time);
    bool success = false;
    
    if (_testMode && !_testImage.empty()) {
        // Test-Modus: verwende statisches Bild
        _img = _testImage.clone();
        success = true;
        log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "Test-Bild verwendet: " << success;
    } else if (_useRpicam) {
        // rpicam-still für Einzelaufnahmen mit optimiertem Autofokus für OCR
        std::string filename = "/tmp/current_frame.jpg";
        std::string cmd = "rpicam-still -o " + filename + 
                         " --width 640 --height 480" +
                         " --timeout 1 --nopreview" +
                         " --autofocus-mode auto" +         // Kontinuierlicher Autofokus
                         " --autofocus-range normal" +      // Normaler Fokusbereich  
                         " --autofocus-speed fast" +        // Schneller Fokus
                         " --lens-position 0.0" +          // Auto-Position
                         " --sharpness 1.5" +              // Erhöhte Schärfe für OCR
                         " --contrast 1.2" +               // Leicht erhöhter Kontrast
                         " --quality 95" +                 // Hohe Bildqualität
                         " > /dev/null 2>&1";
        
        int result = system(cmd.c_str());
        if (result == 0) {
            _img = cv::imread(filename);
            success = !_img.empty();
            // Temporäre Datei löschen
            system(("rm -f " + filename).c_str());
            log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "rpicam-still Bild erfasst: " << success;
        } else {
            log4cpp::Category::getRoot() << log4cpp::Priority::WARN << "rpicam-still fehlgeschlagen";
        }
    } else if (_capture.isOpened()) {
        // Normale OpenCV Kameraerfassung
        success = _capture.read(_img);
        log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "OpenCV Bild erfasst: " << success;
        
        if (!success || _img.empty()) {
            log4cpp::Category::getRoot() << log4cpp::Priority::WARN << "Kamera-Frame leer oder fehlgeschlagen, erneuter Versuch...";
            // Ein weiterer Versuch
            success = _capture.read(_img);
            log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "OpenCV Bild erfasst (retry): " << success;
        }
    } else {
        log4cpp::Category::getRoot() << log4cpp::Priority::ERROR << "Kamera nicht geöffnet";
    }

    // save copy of image if requested
    if (success && !_outDir.empty()) {
        saveImage();
    }

    return success;
}


