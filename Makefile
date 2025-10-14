CXX = g++
CXXFLAGS = -Wall -std=c++14 -O3 -Icommon
OMPFLAGS = -fopenmp

COMMON_SRCS = common/common.cpp

all: bsp bss msp mss qsp qss reference

serial: bss mss qss

parallel: bsp msp qsp

# Bubble Sort Executables
bsp: bubbleSort/bsp.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

bss: bubbleSort/bss.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Merge Sort Executables
msp: mergeSort/msp.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

mss: mergeSort/mss.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Quick Sort Executables
qsp: quickSort/qsp.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

qss: quickSort/qss.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

reference: reference.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test:
	./bsp 100 42
	./bss 100 42
	./msp 100 42
	./mss 100 42
	./qsp 100 42
	./qss 100 42
	./reference 100 42

clean:
	rm -f bsp bss msp mss qsp qss reference

.PHONY: all test clean