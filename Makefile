CXX = g++
CXXFLAGS = -Wall -std=c++14 -O2 -Icommon

all: bss bbp qss qsp mss msp reference

bss: bubbleSort/bss.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

bbp: bubbleSort/bsp.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

qss: quickSort/qss.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

qsp: quickSort/qsp.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

mss: mergeSort/mss.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

msp: mergeSort/msp.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

reference: reference.cpp common/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f bss bbp qss qsp mss msp reference