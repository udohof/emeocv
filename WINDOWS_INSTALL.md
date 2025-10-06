# Windows Installation Guide für emeocv

Dieses Dokument beschreibt die Schritte zur Installation und Ausführung von emeocv unter Windows mit VS Code.

## Voraussetzungen

### 1. Visual Studio Code
- Download und Installation von [VS Code](https://code.visualstudio.com/)
- Installiere die folgenden VS Code Extensions:
  - C/C++ Extension Pack (ms-vscode.cpptools-extension-pack)
  - CMake Tools (ms-vscode.cmake-tools)

### 2. MinGW-w64 (GCC Compiler für Windows) - ERFORDERLICH

**Option A: MSYS2 (Empfohlen)**
1. Download und Installation von [MSYS2](https://www.msys2.org/)
2. Nach der Installation von MSYS2, öffne das MSYS2 Terminal und führe aus:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-cmake
   pacman -S mingw-w64-x86_64-make
   pacman -S mingw-w64-x86_64-pkg-config
   ```
3. **WICHTIG**: Füge `C:\msys64\mingw64\bin` zu deinem Windows PATH hinzu:
   - Windows-Taste → "Umgebungsvariablen" → "Systemumgebungsvariablen bearbeiten"
   - "Umgebungsvariablen..." → PATH auswählen → "Bearbeiten..."
   - "Neu" → `C:\msys64\mingw64\bin` hinzufügen → OK

**Option B: Standalone MinGW**
- Download von [MinGW-w64](https://www.mingw-w64.org/downloads/)
- Nach Installation PATH entsprechend anpassen

**Testen der Installation:**
```cmd
g++ --version
```
Sollte die GCC-Version anzeigen.

### 3. OpenCV für Windows
Option A: vcpkg (empfohlen)
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
.\vcpkg install opencv4[contrib]:x64-windows
```

Option B: Manuelle Installation
- Download OpenCV für Windows von [opencv.org](https://opencv.org/releases/)
- Entpacke nach `C:\opencv`
- Füge `C:\opencv\build\x64\vc15\bin` zum PATH hinzu

### 4. Optional: log4cpp und RRDtool
Diese Bibliotheken sind für die vollständige Funktionalität erforderlich, aber das Programm kann auch ohne sie kompiliert werden (mit eingeschränkter Funktionalität).

#### log4cpp via vcpkg:
```bash
.\vcpkg install log4cpp:x64-windows
```

#### RRDtool für Windows:
- Download von einer Windows-Port oder verwende alternative Datenbanken

## Build-Anleitung

Es gibt mehrere Möglichkeiten, das Projekt zu kompilieren:

### Option A: PowerShell Build-Skript (Empfohlen für Einsteiger)

1. **Projekt öffnen**
   - Öffne VS Code
   - File → Open Folder → Wähle den emeocv Ordner

2. **PowerShell öffnen**
   - Terminal → New Terminal in VS Code
   - Oder Windows PowerShell direkt öffnen

3. **Kompilieren**
   ```powershell
   # Debug-Version
   .\build.ps1 -Debug
   
   # Release-Version
   .\build.ps1
   
   # Bereinigen
   .\build.ps1 -Clean
   ```

### Option B: Makefile (für erfahrene Nutzer)

1. **Mit MinGW Make**
   ```cmd
   # Debug-Build
   mingw32-make -f Makefile.win
   
   # Release-Build  
   mingw32-make -f Makefile.win release
   
   # Bereinigen
   mingw32-make -f Makefile.win clean
   
   # Hilfe anzeigen
   mingw32-make -f Makefile.win help
   ```

### Option C: CMake (wenn installiert)

1. **CMake konfigurieren**
   ```cmd
   cmake -B build -S . -G "MinGW Makefiles"
   ```

2. **Kompilieren**
   ```cmd
   cmake --build build
   ```

### 4. Ausführen
```cmd
# Mit PowerShell-Build:
.\Debug\emeocv.exe -h

# Mit Makefile:
Debug\emeocv.exe -h

# Mit CMake:
build\emeocv.exe -h
```

## Verwendung

### Kamera-Kalibrierung (für USB-Kamera):
```cmd
emeocv.exe -c 0 -a
```

### OCR Training:
```cmd
emeocv.exe -i testbilder -l
```

### OCR Test:
```cmd
emeocv.exe -i testbilder -t
```

### Normaler Betrieb mit Bildern:
```cmd
emeocv.exe -i bildordner -w
```

### Normaler Betrieb mit Kamera:
```cmd
emeocv.exe -c 0 -w
```

## Bekannte Probleme und Lösungen

### Problem: OpenCV nicht gefunden
- Stelle sicher, dass OpenCV korrekt installiert ist
- Überprüfe den CMAKE_PREFIX_PATH in CMakeLists.txt
- Bei vcpkg: `.\vcpkg integrate install` ausführen

### Problem: Bibliotheken nicht gefunden zur Laufzeit
- Stelle sicher, dass alle DLL-Dateien im PATH sind
- Kopiere benötigte DLLs in das build-Verzeichnis

### Problem: log4cpp oder RRD nicht gefunden
- Das Programm kompiliert auch ohne diese Bibliotheken
- Funktionalität ist dann eingeschränkt (keine Logs/Datenbank)

## Unterschiede zur Linux-Version

- Pfadtrenner: `\\` statt `/`
- `Sleep()` statt `usleep()`
- Windows API für Datei-/Verzeichnisoperationen
- Andere Bibliotheks-Pfade

## Entwicklung

Das Projekt ist jetzt Windows-kompatibel und kann mit VS Code entwickelt werden:
- Debugging mit F5
- IntelliSense funktioniert
- CMake Integration
- Tasks für Build und Run
