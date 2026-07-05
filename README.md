# Doodle Jump - AP Team Project

A simple Doodle Jump style game built in C++ using SFML.

## Overview

This repository contains a working phase of a Doodle Jump clone featuring:
- title menu with high score display
- player movement using keyboard controls
- procedural platform generation and vertical scrolling
- game over and restart flow

The game is implemented in C++ and built with a `Makefile` that supports macOS/Linux and Windows.

## Requirements

- C++17 compiler
- SFML 2.x
- `make`

Optional but recommended:
- SFML installed via Homebrew on macOS or pkg-config compatible installation on Linux

## Build and Run

### macOS / Linux

Open a terminal in the project root and run:

```bash
make release
./bin/release/game
```

To build a debug version:

```bash
make debug
./bin/debug/game_debug
```

### Windows

Open CMD in the project root and run:

```cmd
make release
bin\release\game.exe
```

If Windows is detected, the Makefile uses the bundled `SFML` folder located in the repository.

## Controls

- Left Arrow / Right Arrow: move the player
- Enter / Space: start game from menu or restart after game over
- R: restart from game over screen
- Escape: return to menu from game over screen
- Mouse: click Start, Restart, or Menu buttons

## Project Structure

- `src/` - C++ source files
- `include/` - header files
- `assets/` - required textures and graphics
- `SFML/` - bundled SFML include and lib support for Windows
- `Makefile` - build script for all platforms

## Notes

- The game loads textures from `assets/`:
  - `assets/background.png`
  - `assets/left_doodle.png`
  - `assets/right_doodle.png`
  - `assets/normal_platform.png`
- The code attempts to load a system font from common paths on macOS and Linux.
- If you use a custom SFML installation, make sure `pkg-config` can find `sfml-graphics`, `sfml-window`, and `sfml-system`.

## Cleaning

To remove build artifacts:

```bash
make clean
```

## License

This project does not include a license file.
