RESEARCH_DIR=/home/kate/research

SRC_DIR = ${RESEARCH_DIR}/NetworkMapping/EA/src

CPP=g++

CFLAGS=-I/$(SRC_DIR) -g

LDFLAGS=-lpthread -ldl -rdynamic

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

$(OBJECTS):$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

all: Solver

Solver: Solver.cpp $(OBJECTS)
	echo $(OBJECTS)
	$(CPP) Solver.cpp $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJECTS) Solver
