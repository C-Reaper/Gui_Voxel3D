# Project README

## Overview
The project is a simple 3D voxel-based game written in C. It uses the X11 library for the graphical user interface and provides a Makefile for building on Linux, Windows, Wine, and WebAssembly.

## Features
- Basic 3D rendering of voxels.
- User interaction through keyboard and mouse input.
- Cross-platform support: Linux, Windows, Wine, and WebAssembly.

## Project Structure
```
Gui_Voxel3D/
├── build/              # .exe files produced by Main.c
├── src/                # source code
│   ├── Main.c          # Entry point
│   └── *.h             # standalone Header-based C-files, without *.c files that implement it
├── Makefile.linux      # Linux Build configuration
├── Makefile.windows    # Windows Build configuration
├── Makefile.wine       # Wine Build configuration
├── Makefile.web        # Emscripten Build configuration
└── README.md           # This file
└── LICENSE
└── .gitignore
```

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - Linux: X11
  - Windows: None (compiles directly to exe)
  - Wine: None (compiles directly to exe)
  - WebAssembly: Emscripten

## Build & Run
### Linux
To build and run on Linux:
```sh
cd Gui_Voxel3D
make -f Makefile.linux all
./build/Main
```

### Windows
To build and run on Windows, you need to use a tool like MinGW-w64 or Cygwin.
```sh
cd Gui_Voxel3D
make -f Makefile.windows all
./build/Main.exe
```

### Wine
To build and run on Linux using Wine:
```sh
cd Gui_Voxel3D
make -f Makefile.wine all
WINEPREFIX=~/wine64 WINEARCH=win64 wine ./build/Main.exe
```

### WebAssembly
To build and run on the web, you need to have Emscripten installed.
```sh
cd Gui_Voxel3D
make -f Makefile.web all
emrun --no_browser --port 8080 ./build/index.html
```

This README provides a clear overview of the project's structure, features, and build instructions for different platforms.