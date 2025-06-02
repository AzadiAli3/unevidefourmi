CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Source files
SOURCES = fourmiliere_0.cpp fourmiliere_1.cpp fourmiliere_2.cpp fourmiliere_3.cpp fourmiliere_4.cpp fourmiliere_5.cpp

# Executable names
EXECUTABLES = fourmiliere_0 fourmiliere_1 fourmiliere_2 fourmiliere_3 fourmiliere_4 fourmiliere_5

# Default target
all: $(EXECUTABLES)

# Individual targets
fourmiliere_0: fourmiliere_0.cpp fourmiliere.h
	$(CXX) $(CXXFLAGS) -o $@ $<

fourmiliere_1: fourmiliere_1.cpp fourmiliere.h
	$(CXX) $(CXXFLAGS) -o $@ $<

fourmiliere_2: fourmiliere_2.cpp fourmiliere.h
	$(CXX) $(CXXFLAGS) -o $@ $<

fourmiliere_3: fourmiliere_3.cpp fourmiliere.h
	$(CXX) $(CXXFLAGS) -o $@ $<

fourmiliere_4: fourmiliere_4.cpp fourmiliere.h
	$(CXX) $(CXXFLAGS) -o $@ $<

fourmiliere_5: fourmiliere_5.cpp fourmiliere.h
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run all tests
test: all
	@echo "Running all fourmiliere algorithms..."
	@echo "=================================="
	./fourmiliere_0
	@echo ""
	./fourmiliere_1
	@echo ""
	./fourmiliere_2
	@echo ""
	./fourmiliere_3
	@echo ""
	./fourmiliere_4
	@echo ""
	./fourmiliere_5

# Clean up
clean:
	rm -f $(EXECUTABLES)

.PHONY: all test clean