/*
 * debug_test.cpp - Minimaler Test für Debugging
 */

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "Debug Test Start..." << std::endl;
    
    try {
        std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
        
        // Teste einfache OpenCV-Funktion
        cv::Mat testImg = cv::Mat::zeros(100, 100, CV_8UC3);
        std::cout << "OpenCV Mat erstellt: " << testImg.rows << "x" << testImg.cols << std::endl;
        
        // Versuche Kamera zu öffnen
        std::cout << "Versuche Kamera zu öffnen..." << std::endl;
        cv::VideoCapture cap(0);
        
        if (cap.isOpened()) {
            std::cout << "Kamera geöffnet!" << std::endl;
            cap.release();
        } else {
            std::cout << "Kamera konnte nicht geöffnet werden." << std::endl;
        }
        
        std::cout << "Test erfolgreich beendet." << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Fehler: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}