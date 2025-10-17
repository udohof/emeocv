Die Option -A aktiviert die AOI (Area of Interest) Vorhersage für die 7. Ziffer (Dezimalstelle).

Was macht die -A Option?

## Grundprinzip:
Die -A Option erweitert die normale 6-Ziffern-Erkennung um eine intelligente Vorhersage der Position der 7. Ziffer (Dezimalstelle) und fügt diese automatisch hinzu.

## Algorithmus-Ablauf:

# Schritt 1: Analyse der erkannten 6 Ziffern (Analysiere Abstände zwischen den ersten 6 Ziffern)

# Schritt 2: Qualitätskontrolle mit konfigurierbaren Parametern
smartSpacingTolerance: 0.5 # 50% Toleranz für Abstände
smartSizeTolerance: 0.3 # 30% Toleranz für Größen

Prüfung der Regelmäßigkeit:
Spacing-Check: Sind die Abstände zwischen den Ziffern regelmäßig? (±50%)
Size-Check: Sind die Zifferngrößen ähnlich? (±30%)

# Schritt 3: AOI-Berechnung (nur bei regulären Mustern)
aoiWidthMultiplier: 1.2 # 120% der durchschnittlichen Ziffernbreite

# Schritt 4: Edge-Density-Validierung
aoiMinEdgeDensity: 0.05 # Mindestens 5% Kanten erforderlich
aoiMaxEdgeDensity: 0.5 # Maximal 50% Kanten erlaubt

## Praktisches Beispiel:
Eingabe: 6 erkannte Ziffern
[1] [2] [3] [4] [5] [6] ?
│ │ │ │ │ │ │
20 20 21 19 20 20 ?? ← Abstände in Pixeln

# Analyse:
Durchschnittsabstand: 20 Pixel
Spacing-Toleranz: ±10 Pixel (50% von 20)
Alle Abstände im Bereich: 19-21 Pixel ✅
Größen ähnlich: Alle ~30x45 Pixel ✅

# AOI-Vorhersage:
Position X: 6te_Ziffer.x + 6te_Ziffer.width + 20 = 247
Position Y: Durchschnitts-Y = 15
Breite: 30 \* 1.2 = 36 Pixel (20% Sicherheitsmargin)
Höhe: 45 Pixel

# Edge-Density-Check:
AOI-Box: 36x45 = 1620 Pixel
Gefundene Kanten: 364 Pixel
Edge-Density: 364/1620 = 0.22 (22%)
✅ Zwischen 5% und 50% → Gültige Ziffer!

Wann funktioniert -A NICHT?
❌ Unregelmäßige Abstände:
[1] [2][3] [4] [5] [6]
│ │ │ │ │ │
20 2 25 15 20 19 ← Zu unregelmäßig!

❌ Unterschiedliche Größen:
[1] [2] [?] [4] [5] [6]
28x45 30x44 15x20 31x44 28x45 30x44
↑ Fragment! Größe zu unterschiedlich

❌ Leerer Bereich:
Vorhergesagte AOI-Box:
┌─────────────────┐
│ │ Edge-Density: 0.01 (1%)
│ │ ❌ Unter 5% → Abgelehnt
│ │
└─────────────────┘
🔧 Konfigurierbare Aspekte deiner config.yml:
# Smart Fragment Filtering (bestimmt OB AOI aktiviert wird):
smartSpacingTolerance: 0.5 # Wie regelmäßig müssen Abstände sein?
smartSizeTolerance: 0.3 # Wie ähnlich müssen Größen sein?

# AOI-Geometrie (bestimmt WIE die Box berechnet wird):
aoiWidthMultiplier: 1.2 # Wie breit soll die AOI-Box sein?

# AOI-Validierung (bestimmt ob Inhalt gültig ist):
aoiMinEdgeDensity: 0.05 # Mindest-Kantendichte
aoiMaxEdgeDensity: 0.5 # Maximal-Kantendichte

# AOI-Beschneidung (nach erfolgreicher Erkennung):
cropPercentHorizontalAOI: 0.15 # 15% horizontale Beschneidung
cropPercentVerticalAOI: 0.02 # 2% vertikale Beschneidung

## Vorteile der -A Option:
# Automatische 7-Digit-Erkennung
Kein manuelles Definieren der Dezimalstellen-Position nötig
Adaptiert sich an verschiedene Zählertypen und -größen

# Intelligente Qualitätskontrolle
Nur bei regelmäßigen, erkannten 6 Ziffern wird AOI aktiviert
Edge-Density verhindert falsche Positive bei leeren Bereichen

# Robuste Parameter
Alle Schwellwerte sind konfigurierbar
Balance zwischen Sensitivität und Falsch-Positiv-Rate

# Integration mit anderen Features
Funktioniert mit -C (Smart Fragment Filtering)
Nutzt Perspektivkorrektur-Skalierung bei -P
Kompatibel mit Enclosed Area Detection

## Fazit:
Die -A Option ist ein intelligenter "7. Ziffer-Autopilot", der:
Analysiert ob die ersten 6 Ziffern regelmäßig erkannt wurden
Berechnet die wahrscheinliche Position der 7. Ziffer
Validiert ob dort tatsächlich eine Ziffer vorhanden ist
Fügt hinzu die 7. Ziffer zur Erkennung, falls alle Tests bestehen
Das macht die Zählererkennung vollständiger und robuster, ohne manuelle Konfiguration der Dezimalstellen-Position!
