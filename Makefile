CXX := g++
AS := as

ifeq ($(OS),Windows_NT)
EXE := .exe
MKDIR_P := powershell -Command "New-Item -ItemType Directory -Force -Path"
RM := powershell -Command "Remove-Item -Recurse -Force"
else
EXE :=
MKDIR_P := mkdir -p
RM := rm -rf
endif

CXXFLAGS_DEBUG := -std=c++17 -g -O0 -Wall -Wextra -Iinclude
CXXFLAGS_RELEASE := -std=c++17 -O3 -Wall -Wextra -Iinclude
ASFLAGS := 

SRCS := $(wildcard src/*.cpp)
ASMS := $(wildcard src/*.S)
OBJS_DEBUG := $(ASMS:.S=.o)
OBJS_RELEASE := $(ASMS:.S=.o)

OBJDIR_DEBUG := build/debug
OBJDIR_RELEASE := build/release

DEBUG_BIN := $(OBJDIR_DEBUG)/simulator_debug$(EXE)
RELEASE_BIN := $(OBJDIR_RELEASE)/simulator$(EXE)

.PHONY: all debug release run run-debug clean

all: debug release

debug: $(OBJS_DEBUG)
	$(MKDIR_P) $(OBJDIR_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) $(SRCS) $(OBJS_DEBUG) -o $(DEBUG_BIN)

release: $(OBJS_RELEASE)
	$(MKDIR_P) $(OBJDIR_RELEASE)
	$(CXX) $(CXXFLAGS_RELEASE) $(SRCS) $(OBJS_RELEASE) -o $(RELEASE_BIN)

src/%.o: src/%.S
	$(AS) $(ASFLAGS) $< -o $@

run: release
	./$(RELEASE_BIN)

run-debug: debug
	./$(DEBUG_BIN)

clean:
	$(RM) build
	rm -f src/*.o
