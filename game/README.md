# Pandemic Game - AI Players Competition

Ein Strategiespiel, in dem mehrere KI-Spieler versuchen zu überleben und eine Pandemie zu bekämpfen. Dieses Projekt implementiert verschiedene Spieler-Strategien zum Testen und Vergleichen ihrer Effektivität.

## 📋 Übersicht

**Pandemic** ist ein turnsbasiertes Strategiespiel für 2-4 Spieler auf einem Gitter. Die Spieler müssen:
- Sich auf dem Spielfeld bewegen
- Sich vor Infektionen schützen
- Die Pandemie durch Zusammenarbeit oder Konkurrenz bekämpfen
- Die maximale Gesundheit beibehalten

## 🎮 Features

- **Mehrere KI-Spieler**: Dummy (Zufallszüge), Echenique1 (benutzerdefinierte Strategien)
- **Konfigurierbare Spielparameter**: Kartengröße, Runden, Gesundheit, Infektionsrate
- **Visuelle Simulation**: Interaktiver HTML5-Viewer zur Wiedergabe von Spielpartien
- **Seed-basierte Reproduzierbarkeit**: Gleiche Spiele mit gleichem Seed reproduzierbar
- **Batch-Tests**: Automatische Tests über 1000 verschiedene Seeds

## 🛠️ Installation

### Voraussetzungen
- C++11 oder später
- g++ oder clang
- Make
- Linux/Unix-System

### Kompilieren

```bash
cd game
make
```

Zum Säubern:
```bash
make clean
```

## 🚀 Ausführung

### Einfaches Spiel
```bash
./Game -s 1 Echenique1 Dummy Dummy Dummy < test.cnf > game.log
```

### Mit eigenem Seed
```bash
./Game -s 42 Echenique1 Dummy Dummy Dummy < default.cnf > game.log
```

### Verfügbare Kommandos
```bash
./Game --help                    # Hilfe anzeigen
./Game --list                    # Registrierte Spieler auflisten
./Game --version                 # Version anzeigen
```

### Kommandozeilen-Optionen
| Option | Kurz | Beschreibung |
|--------|------|-------------|
| `--seed=N` | `-s N` | Zufallsseed setzen (erforderlich) |
| `--input=FILE` | `-i FILE` | Konfigurationsdatei (Standard: stdin) |
| `--output=FILE` | `-o FILE` | Ausgabedatei (Standard: stdout) |
| `--list` | `-l` | Spieler auflisten |
| `--version` | `-v` | Version anzeigen |
| `--help` | `-h` | Hilfe anzeigen |

## 🎨 Visualisierung

### HTML Viewer

1. Führe ein Spiel aus und speichere die Ausgabe:
```bash
./Game -s 1 Echenique1 Dummy Dummy Dummy < test.cnf > game.log
```

2. Starte einen Browser:
```bash
firefox Viewer/viewer.html
```

3. Lade die `game.log` Datei im Viewer
4. Beobachte die Simulation mit Schritt-für-Schritt-Kontrolle

## ⚙️ Konfiguration

### Spielparameter (test.cnf)

```
Pandemic 1.0
nb_players            4          # Anzahl der Spieler
rows                  40         # Kartenhöhe (min. 20)
cols                  40         # Kartenbreite (min. 20)
nb_rounds             20         # Anzahl der Runden
initial_health        100        # Start-Gesundheit
nb_units              15         # Einheiten pro Spieler
bonus_per_city_cell   1          # Bonus pro Stadt-Zelle
bonus_per_path_cell   1          # Bonus pro Pfad-Zelle
factor_connected_component 2     # Faktor verbundener Komponenten
infection_factor      50         # Infektionsrate
mask_protection       20         # Maskenschutz
GENERATOR1                        # Kartengenerator
```

### Karte

- Mindestgröße: 20×20 (minimum 400 Zellen)
- Erforderliche Zellen: `rows * cols >= 25 * nb_players * nb_units`
- Generator: GENERATOR1 erstellt procedurally generierte Karten

## 📊 Batch-Tests

Test gegen 1000 verschiedene Seeds:
```bash
bash test.sh
```

Dies vergleicht Standard- und Sekunden-Spiellogik und meldet Unterschiede.

## 📁 Projektstruktur

```
game/
├── AI*.cc              # Spieler-Implementierungen
├── Board.cc/.hh        # Spielfeld-Logik
├── Game.cc/.hh         # Spiel-Hauptlogik
├── Main.cc             # Programmeintritt
├── Player.cc/.hh       # Spieler-Basisklasse
├── Settings.cc/.hh     # Konfigurationsmanagement
├── State.cc/.hh        # Spielzustand
├── Viewer/             # HTML5 Visualisierungs-Suite
│   ├── viewer.html     # Hauptseite
│   ├── viewer.js       # Spiellogik
│   └── css/            # Stile
├── test.cnf            # Test-Konfiguration (kleine Karte)
├── default.cnf         # Standard-Konfiguration (große Karte)
└── Makefile            # Build-Konfiguration
```

## 🎯 Implementieren Sie einen eigenen Spieler

1. Kopie [AINull.cc](AINull.cc) zu `AIYourName.cc`
2. Ändern Sie `#define PLAYER_NAME` in Ihren Namen
3. Implementieren Sie die `play()` Methode
4. Kompilieren Sie mit `make`

```cpp
#define PLAYER_NAME YourAI

struct YourAI : public Player {
    static Player *factory() {
        return new YourAI;
    }
    
    void play() {
        // Ihre Strategie hier
        *this = Action(...);
    }
};
```

## 🔧 Optimierungen

### Schnellere Kompilierung

Bearbeiten Sie `Makefile`:
```makefile
OPTIMIZE = 3  # Erhöhen Sie auf 3 für mehr Optimierungen
```

## 📝 Ausgabeformat

Die Spieldatei enthält:
- Spielseed
- Einstellungen (Kartengröße, Spieler, etc.)
- Spielernamen
- Zustandübergänge pro Runde
- Endergebnisse (Punkte, Gesundheit, etc.)

## 🐛 Häufige Mängel

| Fehler | Lösung |
|--------|--------|
| "Missing seed?" | Verwenden Sie `-s seedvalue`, z.B. `-s 1` |
| "Wrong number of rows" | Kartengröße muss ≥ 20×20 sein |
| "Wrong parameters" | Vergrößern Sie die Karte: `rows * cols >= 25 * nb_players * nb_units` |
| "Player not registered" | Spieler compiliert nicht oder Name falsch geschrieben |

## 👨‍💻 Autoren

- **Original**: Martí Oller (UPC)
- **KI Spieler**: Echenique1 (benutzerdefinierte Strategie)

## 📧 Kontakt

Martí Oller (ollerriera.mart@gmail.com)  
Universitat Politècnica de Catalunya

## 📄 Lizenz

(c) Universitat Politècnica de Catalunya, 2021

---

**Viel Spaß beim Spielen und Optimieren Ihrer KI-Spieler!** 🚀
