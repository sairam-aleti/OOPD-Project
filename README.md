# Cellular Network Simulator

Project scaffold for the IIITD OOPD Cellular Network Simulator.

This repository contains initial project files and the abstract
`CommunicationProtocol` base class. All program I/O is routed through
the provided `Basicio` interface files.

## Build Instructions

### Linux / WSL
```bash
cd project
make all
make run
```

### macOS
```bash
cd project
make all
make run
```

### Windows (MSVC)
Use the included Makefile with `nmake`:
```cmd
nmake all
nmake run
```

## Project Structure

```
project/
├── include/
│   ├── CommunicationProtocol.h
│   ├── UserDevice.h
│   ├── CellTower.h
│   ├── CellularCore.h
│   ├── Protocol2G.h
│   ├── Protocol3G.h
│   ├── Protocol4G.h
│   ├── Protocol5G.h
│   ├── Basicio.h
│   └── syscall.h (if needed)
├── src/
│   ├── main.cpp
│   ├── UserDevice.cpp
│   ├── CellTower.cpp
│   ├── CellularCore.cpp
│   ├── Protocol2G.cpp
│   ├── Protocol3G.cpp
│   ├── Protocol4G.cpp
│   ├── Protocol5G.cpp
│   ├── Basicio.cpp
│   └── syscall.s
├── build/
│   ├── debug/
│   └── release/
├── Makefile
├── README.md
└── .gitignore
```

## Requirements

- C++17 or later
- GNU Make (Linux/macOS) or NMAKE (Windows with MSVC)
- WSL for Windows development

## Next Steps

After pushing this commit, implement:
1. `UserDevice` and `CellTower` classes
2. `CellularCore` network coordinator
3. Concrete protocol implementations (2G/3G/4G/5G)
4. Main simulator and test harness
