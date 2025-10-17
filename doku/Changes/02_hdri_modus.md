# Nutzung der HDRI-Funktionalität der Pi Cam

## Beschreibung und Vorteile

Die Pi Cam 3 unterstützt HDRI (High Dynamic Range Imaging). Im HDR-Modus werden mehrere Belichtungen kombiniert, um auch bei schwierigen Lichtverhältnissen (z.B. Gegenlicht, Schatten) optimale Ergebnisse zu erzielen. Die Integration in emeocv ermöglicht eine robustere Ziffernerkennung bei wechselnden Lichtbedingungen.

**Vorteile:**
- Bessere Lesbarkeit von Ziffern bei schwierigen Lichtverhältnissen
- Höherer Dynamikumfang, weniger Über- oder Unterbelichtung
- Supersampling durch natives Downscaling auf 640x480

## Codeänderungen

- Neuer Parameter `useHdri` in `CameraInput`.
- Im HDR-Modus werden spezielle Parameter an `rpicam-still` übergeben:
  - `--hdr auto`, `--zsl`, längeres Timeout, Autofokus direkt vor Aufnahme
- Nach HDR-Aufnahme wird das hochauflösende Bild auf 640x480 herunterskaliert (Supersampling).

**Wichtige Codeausschnitte:**

```cpp
if (_useHdri) {
    cmd += " --timeout 3000";
    cmd += " --hdr auto";
    cmd += " --zsl";
    cmd += " --autofocus-on-capture 1";
    // ...
    // Downscaling auf 640x480
    cv::resize(originalImg, _img, cv::Size(640, 480));
}
```

Siehe Datei: `ImageInput.cpp`, Methode `CameraInput::nextImage()`
