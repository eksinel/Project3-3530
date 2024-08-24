# Compiler
CXX = g++

# Executable name
CXXFLAGS = -std=c++11 -Wall -Wextra

.PHONY: clean

main: main.o sort.o fitCheck.o
	$(CXX) $(CXXFLAGS) main.o sort.o fitCheck.o -o main

main.o: main.cpp sort.hpp fitCheck.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

sort.o: sort.cpp sort.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

fitCheck.o: fitCheck.cpp fitCheck.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o main
