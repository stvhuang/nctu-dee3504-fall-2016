CXX=g++
CXXFLAGS=-Werror -Wall
SRC=0310122_fp.cpp
EXE=0310122_fp.exe
INPUT=map.txt
OUTPUT=sol.txt

all: $(SRC)
	$(CXX) $< -o $(EXE) $(CXXFLAGS)

.PHONY: run clean

run: $(EXE)
	./$(EXE) $(INPUT) $(OUTPUT)

clean:
	rm -rf $(OBJ) $(EXE)

