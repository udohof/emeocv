# Code-Änderungen Dokumentation

Dokumentation aller Änderungen zwischen dem Original-Repository (https://github.com/skaringa/emeocv.git) und der aktuellen Version.

Die Diff-Ansichten sind im Pull-Request-Stil erstellt, mit grünen Linien für hinzugefügte und roten Linien für entfernte Inhalte.

## Geänderte Dateien (Originalversion vs. aktuelle Version)

### Core C++ Dateien
- **Config.cpp** - Konfigurationsverwaltung
- **Config.h** - Konfiguration Header
- **ImageInput.cpp** - Bildeingabe-Klasse
- **ImageInput.h** - Bildeingabe Header
- **ImageProcessor.cpp** - Bildverarbeitung
- **ImageProcessor.h** - Bildverarbeitung Header
- **KNearestOcr.cpp** - OCR-Algorithmus
- **main.cpp** - Hauptprogramm

### Build und Konfiguration
- **Makefile** - Build-Konfiguration
- **config.yml** - Konfigurationsdatei
- **README.md** - Projektdokumentation

## Neue Dateien (nicht in der Originalversion vorhanden)

### Debug und Entwicklung
- **DebugOutput.cpp** - Debug-Ausgabe-Klasse
- **DebugOutput.h** - Debug-Ausgabe Header
- **Debug/trainctr.yml** - Debug-Konfiguration
- **compile_commands.json** - VS Code C++ Konfiguration

### Dokumentation
- **CROP_PARAMETERS.md** - Dokumentation der Crop-Parameter
- **emeocv.md** - Erweiterte Projektdokumentation

### Workflow-Diagramme (PlantUML)
- **option_c_complete_flow.puml** - Vollständiger Workflow für Option C
- **option_c_flow.puml** - Basis-Workflow für Option C

### Test-Skripte
- **test_crop_feature.sh** - Test für Crop-Feature
- **test_erosion_fix.sh** - Test für Erosion-Fix
- **test_fragment_filtering.sh** - Test für Fragment-Filterung

## Diff-Dateien Format

Alle PNG-Dateien zeigen die Änderungen im GitHub Pull-Request-Stil:
- **Grüne Zeilen** (+): Hinzugefügter Code/Inhalt
- **Rote Zeilen** (-): Entfernter Code/Inhalt
- **Weiße Zeilen**: Unveränderte Bereiche (Kontext)

## Verwendung

Die PNG-Dateien können direkt in Dokumentationen, Präsentationen oder Code-Reviews verwendet werden, um die Änderungen visuell darzustellen.

## Original-Quelle

Basis-Repository: https://github.com/skaringa/emeocv.git
Original-Dokumentation: https://en.kompf.de/cplus/emeocv.html

Erstellt am: $(date)