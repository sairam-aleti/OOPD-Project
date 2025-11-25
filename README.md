📡 Cellular Network Simulator — README
📘 Overview

This project implements a Cellular Network Simulator for the OOPD course at IIIT-Delhi.
It demonstrates core Object-Oriented Programming concepts such as inheritance, abstraction, encapsulation, polymorphism, and composition, while simulating real-world cellular communication protocols:

2G (TDMA)

3G (CDMA)

4G (OFDM)

5G (Massive MIMO)

Custom protocol (user-defined)

The simulator models:

Protocol-specific bandwidth and capacity handling

Message generation & routing

Overhead calculations

Frequency/channel allocation

Device management inside cell towers

Multiple cellular cores (for 4G/5G)

🧩 Key Features
✔ Polymorphism

All protocols derive from the abstract class CommunicationProtocol.

✔ Encapsulation

Classes like UserDevice, CellTower, and CellularCore hide internal state using private members with validated setters.

✔ Inheritance

Protocol2G, Protocol3G, Protocol4G, Protocol5G, and CustomProtocol all extend the base protocol class.

✔ Composition

A CellTower has multiple UserDevice objects

A CellularCore manages multiple CellTower objects

✔ CSV File-Based Device Loading

The simulator can load user devices from a CSV file named:

users.csv


Format:

deviceId,Type
5001,D
5002,V
5003,D
...


Where:

D = Data connection

V = Voice connection

Up to 200 lines provided (folder must contain users.csv).

📁 Project Structure
.
├── include/
│   ├── CommunicationProtocol.h
│   ├── Protocol2G.h / Protocol3G.h / Protocol4G.h / Protocol5G.h
│   ├── CustomProtocol.h
│   ├── UserDevice.h
│   ├── CellTower.h
│   └── CellularCore.h
│
├── src/
│   ├── main.cpp
│   ├── BasicIO.cpp
│   ├── UserDevice.cpp
│   ├── CellTower.cpp
│   ├── CellularCore.cpp
│   ├── Protocol2G.cpp / Protocol3G.cpp / Protocol4G.cpp / Protocol5G.cpp
│   ├── CustomProtocol.cpp
│   └── syscall.S
│
├── users.csv                # Optional device input file
├── Makefile
└── README.md

🛠 Build Instructions

This project uses GNU Make.
A UNIX-like environment is required (Linux, WSL, or macOS).

✔ Build all targets:
make all

✔ Run the release build:
make run

✔ Run the debug build:
make run-debug

✔ Clean build artifacts:
make clean

▶ Running the Simulator

Once you run make run, you will see:

========== Cellular Network Simulator ==========
1. 2G (TDMA)
2. 3G (CDMA)
3. 4G (OFDM)
4. 5G (Massive MIMO)
5. Custom Protocol
6. Exit
Enter choice (1-6):


After selecting a protocol, the simulator displays:

Users per channel

Channel bandwidth

Number of channels

Maximum supported users

Required cores (4G/5G)

Then you enter:

Total messages

Overhead percentage

Whether to load devices from users.csv

If users.csv exists and is valid → devices load from file.
Else → simulator falls back to synthetic device generation.

The simulator then:

Allocates devices to channels

Assigns frequencies

Generates messages

Processes messages via CellularCore

Shows simulation statistics

📄 CSV Device Input File

Place users.csv in the root folder (same directory as Makefile).

Example:

5001,D
5002,V
5003,D
...


IDs must be positive integers

Type must be D (data) or V (voice)

No header row

If the file is missing or malformed, the program automatically switches to synthetic devices.


🧪 Assignment Requirements Checklist
Requirement	Status
OOP concepts (inheritance, polymorphism, abstraction, encapsulation)	✔ Completed
Communication protocol classes	✔ 2G/3G/4G/5G/Custom
Device, tower, and core classes	✔ Implemented
Frequency allocation	✔ Implemented
Overhead handling	✔ Implemented
Spectrum/capacity calculations	✔ Per protocol
Makefile with debug & release	✔ Included
Readme with instructions	✔ Included
Private GitHub repo with commits	✔ To be done by student
Load user devices from file	✔ Implemented
No STL (vector, map, string)	✔ Followed
Use of basicIO + syscalls	✔ Followed
📌 Notes

All I/O uses the provided basicIO wrapper.

No C++ STL containers are used (as required).

Raw pointers and fixed-size arrays are used throughout.

Designed for Linux/WSL execution (no Windows native console).

👨‍💻 Authors

Sai Ram Aleti
Aaditya Shinde

IIIT-Delhi — OOPD Course Project