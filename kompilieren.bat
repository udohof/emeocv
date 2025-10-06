@echo off
echo ===============================================
echo  emeocv Windows - Hauptversion kompilieren
echo ===============================================
echo.

echo Kompiliere camera_test.cpp zu emeocv.exe...

g++ -o emeocv.exe camera_test.cpp -I"C:/msys64/mingw64/include/opencv4" -L"C:/msys64/mingw64/lib" -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_highgui -std=c++11

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✓ Kompilierung erfolgreich!
    echo ✓ emeocv.exe wurde erstellt
    echo.
    echo Teste die Anwendung:
    .\emeocv.exe
) else (
    echo.
    echo ✗ Kompilierungsfehler!
)

pause