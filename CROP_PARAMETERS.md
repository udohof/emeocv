# Konfigurierbare Crop-Parameter

Die Option `-C` (Digit Cropping) verwendet jetzt konfigurierbare Parameter aus der `config.yml`:

## Verfügbare Parameter

### Standard Digit Cropping
- **cropPercentHorizontal**: Horizontaler Crop-Prozentsatz für normale Ziffern (Standard: 0.1 = 10%)
- **cropPercentVertical**: Vertikaler Crop-Prozentsatz für normale Ziffern (Standard: 0.02 = 2%)

### AOI (Area-of-Interest) Digit Cropping  
- **cropPercentHorizontalAOI**: Horizontaler Crop-Prozentsatz für AOI-Ziffer (Standard: 0.15 = 15%)
- **cropPercentVerticalAOI**: Vertikaler Crop-Prozentsatz für AOI-Ziffer (Standard: 0.02 = 2%)

## Funktionsweise

### Standard Ziffern (Ziffern 1-6)
Werden mit `cropPercentHorizontal` und `cropPercentVertical` beschnitten.

### AOI Ziffer (7. Ziffer bei -A Option)  
Wird mit `cropPercentHorizontalAOI` und `cropPercentVerticalAOI` beschnitten.
Der höhere horizontale Wert (15% statt 10%) hilft bei der besseren Erkennung der Dezimalstelle.

## Konfiguration ändern

### Über config.yml
```yaml
cropPercentHorizontal: 0.08      # 8% horizontal crop für normale Ziffern
cropPercentVertical: 0.03        # 3% vertical crop für normale Ziffern  
cropPercentHorizontalAOI: 0.12   # 12% horizontal crop für AOI-Ziffer
cropPercentVerticalAOI: 0.025    # 2.5% vertical crop für AOI-Ziffer
```

### Programmatisch (falls gewünscht)
```cpp
Config config;
config.setCropPercentHorizontal(0.08);
config.setCropPercentVertical(0.03);
config.setCropPercentHorizontalAOI(0.12);
config.setCropPercentVerticalAOI(0.025);
config.saveConfig();
```

## Empfohlene Werte

- **Standard Horizontal**: 0.05 - 0.15 (5% - 15%)
- **Standard Vertikal**: 0.01 - 0.05 (1% - 5%)  
- **AOI Horizontal**: 0.10 - 0.20 (10% - 20%)
- **AOI Vertikal**: 0.01 - 0.05 (1% - 5%)

## Morphologische Filter-Parameter

Die Option `-C` verwendet auch konfigurierbare morphologische Operationen zur Fragment-Filterung:

### Verfügbare Parameter

- **morphKernelSizeDivisor**: Teiler für Kernel-Größe (Standard: 15)
  - Kernel-Größe = min(Bildbreite, Bildhöhe) / morphKernelSizeDivisor
  - Kleinere Werte = größere Kernel = stärkere Verbindung von Kanten
  
- **morphIterations**: Anzahl Dilatation/Erosion Iterationen (Standard: 1) 
  - Höhere Werte = stärkere morphologische Effekte
  
- **morphSizeRatioThreshold**: Schwellwert für ähnlich große Konturen (Standard: 0.4)
  - Verhältnis zweitgrößte/größte Kontur für Ziffern mit Löchern (0, 6, 8, 9)

### Funktionsweise

1. **Dilatation**: Verdickt Kanten um nahe Fragmente zu verbinden
2. **Konturenanalyse**: Findet alle verbundenen Komponenten  
3. **Intelligente Filterung**: Behält Hauptstruktur, entfernt kleine Fragmente
4. **Erosion**: Stellt ursprüngliche Kantenstärke wieder her

### Konfiguration in config.yml
```yaml
morphKernelSizeDivisor: 12        # Größere Kernel (weniger konservativ)
morphIterations: 2                # Stärkere morphologische Effekte  
morphSizeRatioThreshold: 0.3      # Weniger tolerant bei ähnlichen Konturen
```

### Empfohlene Werte

- **morphKernelSizeDivisor**: 10-20 (Standard: 15)
- **morphIterations**: 1-3 (Standard: 1)
- **morphSizeRatioThreshold**: 0.2-0.6 (Standard: 0.4)

## Debug Ausgabe

Mit `-d` Option werden die angewandten Parameter in den Debug-Dateien dokumentiert:
- `ImageProcessor_digit_X_crop=Xpct_width_Xpct_height`
- `ImageProcessor_digit_X_crop=Xpct_width_Xpct_height_AOI` (für AOI-Ziffer)
- `ImageProcessor_digit_X_filter=fragments_removed_smart` (nach morphologischer Filterung)