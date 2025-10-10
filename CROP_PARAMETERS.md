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

## Debug Ausgabe

Mit `-d` Option werden die angewandten Crop-Parameter in den Debug-Dateien dokumentiert:
- `ImageProcessor_digit_X_crop=Xpct_width_Xpct_height`
- `ImageProcessor_digit_X_crop=Xpct_width_Xpct_height_AOI` (für AOI-Ziffer)