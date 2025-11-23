# Cellular Network Simulator

IIITD Object-Oriented Programming and Design (OOPD) course project demonstrating core OOP principles through a cellular network simulator supporting 2G, 3G, 4G, and 5G protocols.

## Overview

This project implements a modular network simulator with:
- **Polymorphic protocol interface** (abstract base class with 4 concrete implementations)
- **Data encapsulation** (private members with getter/setter validation)
- **Object composition** (devices connected to towers, towers managed by core)
- **Protocol-specific calculations** for capacity, overhead, and frequency management

## Architecture

- `CommunicationProtocol` - Abstract base defining protocol interface
- `Protocol2G/3G/4G/5G` - Concrete implementations with specification-based calculations
- `UserDevice` - Individual device with ID, frequency, and connection type
- `CellTower` - Manages devices and frequency allocation per protocol
- `CellularCore` - Central coordinator managing towers and message routing

## Build & Run

**Linux/WSL (Recommended):**
```bash
make all
make run
```

**Build Targets:**
- `make all` - Build debug and release
- `make debug` - Build debug version with symbols
- `make release` - Build optimized release
- `make run` - Build and run release version
- `make run-debug` - Build and run debug version
- `make clean` - Remove build artifacts

## Project Structure

```
.
├── include/
│   ├── CommunicationProtocol.h
│   ├── Protocol2G.h / Protocol3G.h / Protocol4G.h / Protocol5G.h
│   ├── UserDevice.h
│   ├── CellTower.h
│   ├── CellularCore.h
│   └── basicIO.h
├── src/
│   ├── main.cpp
│   ├── UserDevice.cpp / CellTower.cpp / CellularCore.cpp
│   ├── Protocol2G.cpp / Protocol3G.cpp / Protocol4G.cpp / Protocol5G.cpp
│   ├── basicIO.cpp
│   └── syscall.S
├── build/
│   ├── debug/simulator_debug
│   └── release/simulator
├── Makefile
└── README.md
```

## Demo Output

The simulator demonstrates:
1. Protocol capacity calculations (max users, channels, overhead)
2. Frequency allocation to sample devices across towers
3. User count per channel for each protocol
4. Message generation and processing through the core

## Key Design Constraints

- **C++17** with no STL containers (vector, map, string, etc.)
- **Raw pointers** and fixed-size C-style arrays (MAX_DEVICES=20000)
- **basicIO-only** I/O (no iostream, printf, or standard libraries except threading)
- **Assembly syscall wrappers** (`syscall3`, `syscall6`) for low-level operations

## Protocol Specifications

| Protocol | Bandwidth | Users/Channel | Max Users | Overhead | Cores |
|----------|-----------|---------------|-----------|----------|-------|
| 2G TDMA  | 200 kHz   | 16            | 80        | 10%      | N/A   |
| 3G CDMA  | 200 kHz   | 32            | 160       | 8%       | N/A   |
| 4G OFDM  | 10 kHz    | 30 (4 ant.)   | 12000     | 5%       | 12    |
| 5G MIMO  | 1 MHz     | 30 (16 ant.)  | 4800      | 3%       | 3     |

## Requirements

- C++17 compatible compiler (g++ recommended)
- GNU Make
- UNIX-like environment (Linux, macOS, WSL)

## Notes

All I/O must use the provided `basicIO` interface. Do not use `iostream`, `printf`, STL containers, or other standard libraries outside of threading support.
