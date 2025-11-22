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
# Cellular Network Simulator

This repository contains the IIITD Cellular Network Simulator.

All I/O in the project uses the provided low-level `basicIO` API
(`include/basicIO.h`, `src/basicIO.cpp`) and the assembly syscall
wrapper `src/syscall.S`. Do NOT use `iostream`, `printf`, or other
standard I/O functions — the simulator is designed to use the supplied
I/O implementation.

Progress so far (commits):

- COMMIT 1: Abstract `CommunicationProtocol` + scaffold
- COMMIT 2: `UserDevice` and `CellTower` implementations
- COMMIT 3: `CellularCore` coordinator with message handling
- COMMIT 4: `Protocol2G`, `Protocol3G`, `Protocol4G`, `Protocol5G`
- COMMIT 5: `Makefile` build system
- COMMIT 6: `main.cpp` demonstration and tests

## Build Instructions

### Linux / WSL (recommended)

```bash
cd "d:/IIITD Subjects/Semester-1/Object Oriented Programming and Design/Project"
make all
make run
```

### Windows

If using MSYS2/MinGW you can use `make` similarly. If using MSVC
toolchain, adapt the commands for `nmake` (Makefile is targeted at GNU compilers).

## Project Structure

```
project/
├── include/
│   ├── CommunicationProtocol.h
│   ├── UserDevice.h
	├── CellTower.h
	├── CellularCore.h
	├── Protocol2G.h
	├── Protocol3G.h
	├── Protocol4G.h
	├── Protocol5G.h
	├── basicIO.h
├── src/
│   ├── main.cpp
│   ├── UserDevice.cpp
	├── CellTower.cpp
	├── CellularCore.cpp
	├── Protocol2G.cpp
	├── Protocol3G.cpp
	├── Protocol4G.cpp
	├── Protocol5G.cpp
	├── basicIO.cpp
	└── syscall.S
├── build/
│   ├── debug/
	└── release/
├── Makefile
├── README.md
└── .gitignore
```

## Requirements

- C++17 or later (GNU toolchain recommended)
- GNU Make (Linux/macOS/WSL)

## Running the demo

After building, run the simulator to see:

- Max user capacity for each protocol
- Frequency allocations for sample devices
- Users per channel for the first frequency
- Required core calculations for 4G/5G

```bash
make run
```

## Notes

- The project intentionally uses a supplied `basicIO` implementation and
  an assembly syscall shim. Keep all I/O calls routed through `basicIO`.
- When ready, push commits incrementally to GitHub following the project's
  progressive commit workflow.
