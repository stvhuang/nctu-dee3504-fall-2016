CXX=g++
CXXFLAGS=-Werror -Wall
SRC=0310122_fp.cpp
EXE=0310122_fp.exe
INPUT=inputfile
OUTPUT=outputfile

all: $(SRC)
	$(CXX) $< -o $(EXE) $(CXXFLAGS)

.PHONY: run clean

run: $(EXE)
	./$(EXE) $(INPUT) $(OUTPUT)

clean:
	rm -rf $(OBJ) $(EXE)
