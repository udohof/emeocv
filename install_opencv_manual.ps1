# Alternative OpenCV Installation ohne vcpkg
# install_opencv_manual.ps1

Write-Host "============================================================" -ForegroundColor Cyan
Write-Host " OpenCV Installation - Alternative Methoden" -ForegroundColor Cyan
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host ""

Write-Host "Da vcpkg nicht verfügbar ist, hier sind alternative Lösungen:" -ForegroundColor Yellow
Write-Host ""

Write-Host "OPTION 1: Portable MinGW + OpenCV (Empfohlen)" -ForegroundColor Green
Write-Host "=" * 50 -ForegroundColor Green
Write-Host ""
Write-Host "1. Download MinGW-w64:" -ForegroundColor White
Write-Host "   https://www.mingw-w64.org/downloads/" -ForegroundColor Cyan
Write-Host "   oder" -ForegroundColor Gray
Write-Host "   https://github.com/niXman/mingw-builds-binaries/releases" -ForegroundColor Cyan
Write-Host ""
Write-Host "2. Download OpenCV Windows:" -ForegroundColor White
Write-Host "   https://opencv.org/releases/" -ForegroundColor Cyan
Write-Host "   -> opencv-4.8.0-windows.exe herunterladen" -ForegroundColor Cyan
Write-Host ""
Write-Host "3. Installation:" -ForegroundColor White
Write-Host "   - MinGW nach C:\mingw64 entpacken" -ForegroundColor Gray
Write-Host "   - OpenCV nach C:\opencv entpacken" -ForegroundColor Gray
Write-Host "   - C:\mingw64\bin zum PATH hinzufügen" -ForegroundColor Gray
Write-Host ""

Write-Host "OPTION 2: Nur Kompiler installieren (ohne OpenCV)" -ForegroundColor Yellow
Write-Host "=" * 50 -ForegroundColor Yellow
Write-Host ""
Write-Host "Für einen schnellen Test können wir zuerst nur den Compiler installieren" -ForegroundColor White
Write-Host "und eine Version ohne OpenCV-Abhängigkeiten erstellen:" -ForegroundColor White
Write-Host ""
Write-Host "Download TDM-GCC (einfache MinGW Distribution):" -ForegroundColor White
Write-Host "https://jmeubank.github.io/tdm-gcc/" -ForegroundColor Cyan
Write-Host ""

Write-Host "OPTION 3: MSYS2 reparieren (falls vorhanden)" -ForegroundColor Magenta
Write-Host "=" * 50 -ForegroundColor Magenta
Write-Host ""

# Prüfe ob MSYS2 vorhanden ist
if (Test-Path "C:\msys64") {
    Write-Host "MSYS2 ist installiert! Versuche GCC zu installieren..." -ForegroundColor Green
    Write-Host ""
    Write-Host "Führen Sie aus:" -ForegroundColor White
    Write-Host "1. MSYS2 Terminal öffnen (Start -> MSYS2)" -ForegroundColor Cyan
    Write-Host "2. pacman -S mingw-w64-x86_64-gcc" -ForegroundColor Cyan
    Write-Host "3. pacman -S mingw-w64-x86_64-opencv" -ForegroundColor Cyan
    Write-Host ""
    
    Write-Host "Oder automatisch über PowerShell versuchen:" -ForegroundColor White
    $continue = Read-Host "MSYS2 GCC Installation versuchen? (j/n)"
    
    if ($continue -eq "j" -or $continue -eq "y") {
        Write-Host "Versuche MSYS2 GCC Installation..." -ForegroundColor Yellow
        
        try {
            # Versuche MSYS2 Bash zu verwenden
            & "C:\msys64\usr\bin\bash.exe" -l -c "pacman --noconfirm -S mingw-w64-x86_64-gcc mingw-w64-x86_64-opencv"
            
            Write-Host "Installation abgeschlossen! Testen Sie:" -ForegroundColor Green
            Write-Host "g++ --version" -ForegroundColor Cyan
            
        } catch {
            Write-Host "Automatische Installation fehlgeschlagen." -ForegroundColor Red
            Write-Host "Bitte manuell im MSYS2 Terminal ausführen." -ForegroundColor Yellow
        }
    }
} else {
    Write-Host "MSYS2 nicht gefunden." -ForegroundColor Gray
}

Write-Host ""
Write-Host "EMPFEHLUNG:" -ForegroundColor Green
Write-Host "Für den schnellsten Erfolg:" -ForegroundColor White
Write-Host "1. TDM-GCC installieren (ca. 5 Minuten)" -ForegroundColor Cyan
Write-Host "2. Erst emeocv ohne OpenCV kompilieren (Test)" -ForegroundColor Cyan
Write-Host "3. Dann OpenCV nachinstallieren" -ForegroundColor Cyan
Write-Host ""

Write-Host "Welche Option möchten Sie wählen?" -ForegroundColor Yellow
Write-Host "1 = TDM-GCC Download-Links zeigen" -ForegroundColor White
Write-Host "2 = OpenCV manuell Download-Links zeigen" -ForegroundColor White  
Write-Host "3 = Ohne OpenCV kompilieren (Test-Version)" -ForegroundColor White
Write-Host "0 = Beenden" -ForegroundColor Gray

$choice = Read-Host "Ihre Wahl (0-3)"

switch ($choice) {
    "1" {
        Write-Host ""
        Write-Host "TDM-GCC Download:" -ForegroundColor Green
        Write-Host "https://jmeubank.github.io/tdm-gcc/" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "Nach Installation testen mit: g++ --version" -ForegroundColor Yellow
        Start-Process "https://jmeubank.github.io/tdm-gcc/"
    }
    
    "2" {
        Write-Host ""
        Write-Host "OpenCV Download:" -ForegroundColor Green
        Write-Host "https://opencv.org/releases/" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "Herunterladen: opencv-4.8.0-windows.exe" -ForegroundColor Yellow
        Write-Host "Nach C:\opencv entpacken" -ForegroundColor Yellow
        Start-Process "https://opencv.org/releases/"
    }
    
    "3" {
        Write-Host ""
        Write-Host "Erstelle Test-Version ohne OpenCV..." -ForegroundColor Yellow
        # Hier würden wir ein Build-Skript ohne OpenCV-Abhängigkeiten erstellen
        Write-Host "Dies wird in einem separaten Schritt durchgeführt." -ForegroundColor Green
    }
    
    default {
        Write-Host "Programm beendet." -ForegroundColor Gray
    }
}