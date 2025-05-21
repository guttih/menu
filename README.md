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
sudo apt install build-essential g++ libncurses5-dev libncursesw5-dev
```

> `g++` is included in `build-essential`, but we list it explicitly for clarity.

---

### 2. Build the program

```bash
make
```

This will:
- Create the required `obj/` and `out/` directories
- Compile all source files
- Output the final binary to `out/menu`

---

### 3. Run the test script

```bash
./test.sh
```

This script demonstrates the menu UI and allows interaction using the arrow keys. It returns the selected option’s index as an exit code and prints the result.

---

### 4. Clean the build

To remove all compiled files:

```bash
make clean
```

To remove only dependency files:

```bash
make cleandep
```

---

## Build Instructions (fedora)
### 1. Install dependencies

```bash
sudo dnf install make gcc-c++ ncurses-devel

```

rest, same as Ubuntu I guess

## 🛠 Troubleshooting

- If you get `Error executable does not exist` when running `test.sh`, make sure you’ve run `make` successfully and `out/menu` exists.
- If `make` says "'obj' is up to date." but nothing gets built, use `make clean && make` to force a rebuild.
