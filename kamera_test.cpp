/*
 * kamera_test.cpp - Einfacher Kamera-Test für Debugging
 */

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::cout << "Kamera-Test für Windows" << std::endl;
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    
    cv::VideoCapture cap;
    
    std::cout << "Versuche Kamera zu öffnen..." << std::endl;
    
    // Teste verschiedene Backends
    std::vector<std::pair<int, std::string>> backends = {
        {cv::CAP_DSHOW, "DirectShow"},
        {cv::CAP_MSMF, "Media Foundation"}, 
        {cv::CAP_ANY, "Default"}
    };
    
    bool success = false;
    for (auto& backend : backends) {
        std::cout << "Teste " << backend.second << "..." << std::endl;
        cap.open(0, backend.first);
        if (cap.isOpened()) {
            std::cout << "✓ Kamera erfolgreich geöffnet mit " << backend.second << std::endl;
            success = true;
            break;
        } else {
            std::cout << "✗ " << backend.second << " fehlgeschlagen" << std::endl;
        }
    }
    
    if (!success) {
        std::cout << "Fehler: Keine Kamera gefunden oder verfügbar!" << std::endl;
        std::cout << "Drücke Enter zum Beenden..." << std::endl;
        std::cin.get();
        return -1;
    }
    
    // Kamera-Eigenschaften anzeigen
    std::cout << "Kamera-Eigenschaften:" << std::endl;
    std::cout << "  Breite: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "  Höhe: " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << "  FPS: " << cap.get(cv::CAP_PROP_FPS) << std::endl;
    
    std::cout << "Drücke 'q' zum Beenden" << std::endl;
    
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cout << "Warnung: Leerer Frame" << std::endl;
            continue;
        }
        
        cv::imshow("Kamera Test", frame);
        
        int key = cv::waitKey(30) & 0xFF;
        if (key == 'q' || key == 27) {
            break;
        }
    }
    
    cap.release();
    cv::destroyAllWindows();
    std::cout << "Test beendet." << std::endl;
    
    return 0;
}