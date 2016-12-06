CXX=g++
CXXFLAGS=-Werror -Wall
SRC=0310122_hw2.cpp
EXE=0310122_hw2.exe
INPUT=inputfile
OUTPUT=outputfile
METHOD=0

all: $(SRC)
	$(CXX) $< -o $(EXE) $(CXXFLAGS)

.PHONY: run clean

run: $(EXE)
	./$(EXE) $(METHOD) $(INPUT) $(OUTPUT)

clean:
	rm -f $(EXE)
