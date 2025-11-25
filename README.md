# 📡 Cellular Network Simulator

## 📘 Overview

This project implements a **Cellular Network Simulator** for the Object-Oriented Programming and Design (OOPD) course at IIIT-Delhi. It demonstrates core OOP concepts including **inheritance**, **abstraction**, **encapsulation**, **polymorphism**, and **composition** while simulating real-world cellular communication protocols.

### Supported Protocols
- **2G (TDMA)** - Time Division Multiple Access
- **3G (CDMA)** - Code Division Multiple Access  
- **4G (OFDM)** - Orthogonal Frequency Division Multiplexing
- **5G (Massive MIMO)** - Multiple Input Multiple Output at 1800 MHz
- **Custom Protocol** - User-defined parameters

### Core Simulation Features
- Protocol-specific bandwidth and capacity handling
- Dynamic message generation & routing
- Overhead calculations with configurable percentages
- Intelligent frequency/channel allocation
- Device management across cell towers
- Multi-core support (4G/5G with automatic core calculation)
- Scalable architecture supporting up to **100,000 devices**
- Message queue capacity of **100,000 messages**

## 🧩 Key OOP Features

### ✔ Polymorphism
All communication protocols derive from the abstract base class `CommunicationProtocol`, enabling runtime protocol selection and uniform interface usage.

### ✔ Encapsulation
Classes like `UserDevice`, `CellTower`, and `CellularCore` hide internal state using private members with validated public setters and getters.

### ✔ Inheritance
`Protocol2G`, `Protocol3G`, `Protocol4G`, `Protocol5G`, and `CustomProtocol` all extend the base protocol class, inheriting common behavior while implementing protocol-specific logic.

### ✔ Composition
- A `CellTower` **has-a** collection of `UserDevice` objects
- A `CellularCore` **has-a** collection of `CellTower` objects
- Demonstrates real-world hierarchical network architecture

### ✔ Template Usage
Generic utility functions using C++ templates (e.g., `clampValue<T>`) for type-safe operations.

### ✔ CSV File-Based Device Loading
The simulator can load user devices from a CSV file:

**File:** `users.csv`

**Format:**
```
deviceId,Type
5001,D
5002,V
5003,D
...
```

**Legend:**
- `D` = Data connection (packet switching)
- `V` = Voice connection (circuit switching)
- No header row required
- IDs must be positive integers

The simulator automatically falls back to synthetic device generation if the file is missing or invalid.

## 📁 Project Structure
```
OOPD-Project/
├── include/                      # Header files
│   ├── CommunicationProtocol.h   # Abstract base class
│   ├── Protocol2G.h              # 2G TDMA implementation
│   ├── Protocol3G.h              # 3G CDMA implementation
│   ├── Protocol4G.h              # 4G OFDM implementation
│   ├── Protocol5G.h              # 5G Massive MIMO implementation
│   ├── CustomProtocol.h          # User-defined protocol
│   ├── UserDevice.h              # Device representation
│   ├── CellTower.h               # Tower & frequency management
│   ├── CellularCore.h            # Network coordinator
│   ├── basicIO.h                 # Custom I/O wrapper
│   └── Utility.h                 # Template utilities
│
├── src/                          # Implementation files
│   ├── main.cpp                  # Entry point & simulation logic
│   ├── basicIO.cpp               # Custom I/O implementation
│   ├── UserDevice.cpp
│   ├── CellTower.cpp
│   ├── CellularCore.cpp
│   ├── Protocol2G.cpp
│   ├── Protocol3G.cpp
│   ├── Protocol4G.cpp
│   ├── Protocol5G.cpp
│   └── syscall.S                 # Low-level syscall assembly
│
├── build/                        # Build output (generated)
│   ├── debug/
│   └── release/
│
├── users.csv                     # Optional device input file
├── Makefile                      # Build system
└── README.md                     # This file
```

## 🛠 Build Instructions

This project uses **GNU Make** and requires a UNIX-like environment (Linux, WSL, or macOS).

### Prerequisites
- `g++` with C++17 support
- `make`
- `as` (GNU assembler)

### Build Commands

```bash
# Build both debug and release versions
make all

# Build release version only (optimized)
make release

# Build debug version only (with symbols)
make debug

# Run the release build
make run

# Run the debug build
make run-debug

# Clean all build artifacts
make clean
```

## ▶ Running the Simulator

### Starting the Program
```bash
make run
```

### Interactive Menu
```
========== Cellular Network Simulator ==========
1. 2G (TDMA)
2. 3G (CDMA)
3. 4G (OFDM)
4. 5G (Massive MIMO)
5. Custom Protocol
6. Exit
Enter choice (1-6):
```

### Simulation Workflow

1. **Select Protocol** - Choose from 2G, 3G, 4G, 5G, or define a custom protocol
2. **View Protocol Info** - System displays:
   - Users per channel
   - Channel bandwidth (kHz)
   - Number of channels
   - Maximum users supported
   - Required cellular cores (for 4G/5G)

3. **Configure Simulation**
   - Enter total number of messages to generate
   - Set overhead percentage (0-100)
   - Choose device loading method:
     - Load from `users.csv` file
     - Generate synthetic devices automatically

4. **Device Allocation**
   - If file loading: Reads devices from CSV
   - If synthetic: Generates devices with mix of DATA/VOICE types
   - Validates capacity constraints

5. **Message Processing**
   - Generates messages based on protocol ratios
   - Routes messages through cellular core
   - Tracks success/failure rates

6. **Results Display**
   - Total messages processed
   - Voice vs. Data message breakdown
   - Devices utilized
   - Overhead incurred
   - Channel statistics

## 📄 CSV Device Input File

Place `users.csv` in the project root folder (same directory as Makefile).

### File Format
```csv
5001,D
5002,V
5003,D
5004,V
5005,D
```

### Format Rules
- **No header row**
- **Column 1:** Device ID (positive integer)
- **Column 2:** Connection type
  - `D` or `d` = Data connection
  - `V` or `v` = Voice connection
- One device per line
- Comma-separated values

### Behavior
- ✅ **File exists & valid**: Devices loaded from file
- ⚠️ **File incomplete**: Loads available devices, warns about capacity
- ❌ **File missing/invalid**: Automatically generates synthetic devices


## 🧪 Assignment Requirements Checklist

| Requirement | Status | Implementation |
|-------------|--------|----------------|
| OOP Concepts (Inheritance, Polymorphism, Abstraction, Encapsulation) | ✅ Complete | Abstract base class, virtual methods, private members |
| Communication Protocol Classes | ✅ Complete | 2G/3G/4G/5G/Custom protocols |
| Device, Tower, and Core Classes | ✅ Complete | `UserDevice`, `CellTower`, `CellularCore` |
| Frequency Allocation | ✅ Complete | Dynamic channel assignment with capacity checks |
| Overhead Handling | ✅ Complete | Configurable overhead percentage (0-100%) |
| Spectrum/Capacity Calculations | ✅ Complete | Protocol-specific formulas |
| Makefile (Debug & Release) | ✅ Complete | Separate debug/release targets with optimization |
| README with Instructions | ✅ Complete | Comprehensive documentation |
| Load User Devices from File | ✅ Complete | CSV file parsing with fallback |
| No STL Containers | ✅ Complete | Raw arrays and pointers only |
| Custom I/O (basicIO + syscalls) | ✅ Complete | No standard library I/O |
| Template Usage | ✅ Complete | Generic utility functions |
| Scalability | ✅ Complete | Supports 100K devices & messages |
## 🔧 Technical Details

### Architecture Highlights
- **Maximum Devices per Tower:** 100,000
- **Maximum Frequency Range:** 0-100,000 kHz
- **Message Queue Capacity:** 100,000 messages
- **Memory Management:** Dynamic allocation for message queue, static arrays for devices
- **Protocol Message Ratios:**
  - 2G: 3:1 voice-to-data (voice-centric)
  - 3G/4G/5G: 1:3 voice-to-data (data-centric)

### Design Patterns
- **Strategy Pattern:** Interchangeable protocol implementations
- **Factory Pattern:** Dynamic protocol creation based on user selection
- **Composition over Inheritance:** Network hierarchy through object composition

### Constraints & Design Decisions
- ✅ All I/O uses custom `basicIO` wrapper (no `iostream`)
- ✅ No C++ STL containers (`vector`, `map`, `string`, etc.)
- ✅ Raw pointers and fixed-size arrays throughout
- ✅ C++17 standard compliance
- ✅ Low-level syscalls via assembly (`syscall.S`)
- ⚠️ Designed for Linux/WSL execution (not Windows native console)

## 📝 Usage Examples

### Example 1: 5G Protocol with 50,000 Messages
```
Choice: 4
Messages: 50000
Overhead: 15%
Load from file: No
Result: 42,500 messages processed (7,500 overhead)
```

### Example 2: Custom Protocol
```
Choice: 5
Users per channel: 1000
Channel bandwidth: 500 kHz
Total spectrum: 5000 kHz
Messages: 10000
Overhead: 20%
```

### Example 3: Loading Devices from CSV
```
Choice: 3 (4G)
Messages: 25000
Overhead: 10%
Load from file: Yes
Result: Loads devices from users.csv
```

## 🐛 Troubleshooting

### Build Issues
```bash
# If make fails, try cleaning first
make clean
make release

# Check g++ version (requires C++17)
g++ --version
```

### File Loading Issues
- Ensure `users.csv` is in the project root directory
- Verify CSV format (no spaces, proper comma separation)
- Check file permissions (must be readable)

### Runtime Errors
- If "Tower at capacity" appears, reduce device count or increase overhead
- If "Message queue full" appears, reduce total messages below 100,000
- For custom protocols, ensure bandwidth ≤ total spectrum

## 👨‍💻 Authors

**Sai Ram Aleti**  
**Aaditya Shinde**

IIIT-Delhi — Object-Oriented Programming and Design Course Project

---

### 📄 License
This project is part of academic coursework at IIIT-Delhi.

### 🔗 Repository
GitHub: `sairam-aleti/OOPD-Project`