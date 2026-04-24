# Pandemic Game - AI Players Competition

A strategy game where multiple AI players compete to survive and fight a pandemic. This project implements various player strategies for testing and comparing their effectiveness.

## 📋 Overview

**Pandemic** is a turn-based strategy game for 2-4 players on a grid. Players must:
- Move across the game board
- Protect themselves from infections
- Combat the pandemic through cooperation or competition
- Maintain maximum health

## 🎮 Features

- **Multiple AI Players**: Dummy (random moves), Echenique1 (custom strategies)
- **Configurable Game Parameters**: Map size, rounds, health, infection rate
- **Visual Simulation**: Interactive HTML5 viewer to replay game sessions
- **Seed-based Reproducibility**: Reproduce the same games with the same seed
- **Batch Testing**: Automatic tests over 1000 different seeds

## 🛠️ Installation

### Prerequisites
- C++11 or later
- g++ or clang
- Make
- Linux/Unix system

### Build

```bash
cd game
make
```

To clean:
```bash
make clean
```

## 🚀 Running the Game

### Simple Game
```bash
./Game -s 1 Echenique1 Dummy Dummy Dummy < test.cnf > game.log
```

### With Custom Seed
```bash
./Game -s 42 Echenique1 Dummy Dummy Dummy < default.cnf > game.log
```

### Available Commands
```bash
./Game --help                    # Show help
./Game --list                    # List registered players
./Game --version                 # Show version
```

### Command-line Options
| Option | Short | Description |
|--------|-------|-------------|
| `--seed=N` | `-s N` | Set random seed (required) |
| `--input=FILE` | `-i FILE` | Configuration file (default: stdin) |
| `--output=FILE` | `-o FILE` | Output file (default: stdout) |
| `--list` | `-l` | List players |
| `--version` | `-v` | Show version |
| `--help` | `-h` | Show help |

## 🎨 Visualization

### HTML Viewer

1. Run a game and save the output:
```bash
./Game -s 1 Echenique1 Dummy Dummy Dummy < test.cnf > game.log
```

2. Start a browser:
```bash
firefox Viewer/viewer.html
```

3. Load the `game.log` file in the viewer
4. Watch the simulation with step-by-step control

## ⚙️ Configuration

### Game Parameters (test.cnf)

```
Pandemic 1.0
nb_players            4          # Number of players
rows                  40         # Map height (min. 20)
cols                  40         # Map width (min. 20)
nb_rounds             20         # Number of rounds
initial_health        100        # Starting health
nb_units              15         # Units per player
bonus_per_city_cell   1          # Bonus per city cell
bonus_per_path_cell   1          # Bonus per path cell
factor_connected_component 2     # Connected component factor
infection_factor      50         # Infection rate
mask_protection       20         # Mask protection
GENERATOR1                        # Map generator
```

### Map Constraints

- Minimum size: 20×20 (minimum 400 cells)
- Required cells: `rows * cols >= 25 * nb_players * nb_units`
- Generator: GENERATOR1 creates procedurally generated maps

## 📊 Batch Testing

Test against 1000 different seeds:
```bash
bash test.sh
```

This compares standard and secondary game logic and reports differences.

## 📁 Project Structure

```
game/
├── AI*.cc              # Player implementations
├── Board.cc/.hh        # Board logic
├── Game.cc/.hh         # Game main logic
├── Main.cc             # Program entry point
├── Player.cc/.hh       # Player base class
├── Settings.cc/.hh     # Configuration management
├── State.cc/.hh        # Game state
├── Viewer/             # HTML5 visualization suite
│   ├── viewer.html     # Main page
│   ├── viewer.js       # Game logic
│   └── css/            # Styles
├── test.cnf            # Test configuration (small map)
├── default.cnf         # Default configuration (large map)
└── Makefile            # Build configuration
```

## 🎯 Implement Your Own Player

1. Copy [AINull.cc](AINull.cc) to `AIYourName.cc`
2. Change `#define PLAYER_NAME` to your name
3. Implement the `play()` method
4. Compile with `make`

```cpp
#define PLAYER_NAME YourAI

struct YourAI : public Player {
    static Player *factory() {
        return new YourAI;
    }
    
    void play() {
        // Your strategy here
        *this = Action(...);
    }
};
```

## 🔧 Optimization

### Faster Compilation

Edit `Makefile`:
```makefile
OPTIMIZE = 3  # Increase to 3 for more optimization
```

## 📝 Output Format

The game file contains:
- Game seed
- Settings (map size, players, etc.)
- Player names
- State transitions per round
- Final results (scores, health, etc.)

## 🐛 Common Issues

| Error | Solution |
|-------|----------|
| "Missing seed?" | Use `-s seedvalue`, e.g., `-s 1` |
| "Wrong number of rows" | Map size must be ≥ 20×20 |
| "Wrong parameters" | Increase map size: `rows * cols >= 25 * nb_players * nb_units` |
| "Player not registered" | Player not compiled or name misspelled |

## 👨‍💻 Authors

- **AI Players**: Echenique1(me) (custom strategy) 
    Universitat Politècnica de Catalunya

## 📄 License

(c) Universitat Politècnica de Catalunya, 2021

---

**Have fun playing and optimizing your AI players!** 🚀
