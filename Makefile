# Compiler
CXX = g++

# Compiler flags - Icommon is needed if your common files are in a 'common' directory
# The -O3 flag is a stronger optimization than -O2, good for performance tests
CXXFLAGS = -Wall -std=c++14 -O3 -Icommon

# OpenMP flag
OMPFLAGS = -fopenmp

# The default target builds ALL executables [cite: 48]
all: bss bbp qss qsp mss msp reference

# --- Bubble Sort Targets ---
bss: bubbleSort/bss.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

bbp: bubbleSort/bsp.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -o $@ $^

# --- Quick Sort Targets ---
qss: quickSort/qss.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

qsp: quickSort/qsp.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -o $@ $^

# --- Merge Sort Targets ---
mss: mergeSort/mss.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

msp: mergeSort/msp.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -o $@ $^

# --- Reference Target ---
reference: reference.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# --- Clean Target ---
clean:
	rm -f bss bbp qss qsp mss msp reference