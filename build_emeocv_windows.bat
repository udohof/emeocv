@echo off
echo === EME OCR Windows Build ===

REM Lösche alte exe-Dateien
if exist emeocv_windows.exe del emeocv_windows.exe

echo Kompiliere emeocv_windows.cpp...
g++ -o emeocv_windows.exe emeocv_windows.cpp ^
    -I"C:/msys64/mingw64/include/opencv4" ^
    -L"C:/msys64/mingw64/lib" ^
    -lopencv_core ^
    -lopencv_imgproc ^
    -lopencv_imgcodecs ^
    -lopencv_videoio ^
    -lopencv_highgui ^
    -lopencv_ml ^
    -std=c++11 ^
    -O2

if %ERRORLEVEL% == 0 (
    echo.
    echo === Erfolgreich kompiliert! ===
    echo Führe emeocv_windows.exe aus um das Programm zu starten
    echo.
    if exist emeocv_windows.exe (
        echo Starte Programm...
        emeocv_windows.exe
    )
) else (
    echo.
    echo === Kompilierung fehlgeschlagen! ===
    echo Überprüfe die Fehlermeldungen oben.
)

pause