# Menu

A C++ terminal application for use in Bash scripts to ask the user to select between options using an interactive `ncurses` UI.

## 📦 Features

- Simple terminal menu using arrow key navigation
- Designed for Bash integration
- UTF-8 friendly (supports Icelandic characters, etc.)
- Returns selected option index as exit code

---

## 🔧 Build Instructions (Ubuntu)

### 1. Install dependencies

```bash
sudo apt update
sudo apt install build-essential libncurses5-dev libncursesw5-dev

