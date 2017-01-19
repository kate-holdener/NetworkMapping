RESEARCH_DIR=/home/kate/research

SRC_DIR = ${RESEARCH_DIR}/NetworkMapping/EA/src

CPP=g++

CFLAGS=-I/$(SRC_DIR)

LDFLAGS=-lgtest -lgtest_main -lpthread

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

$(OBJECTS):$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

TESTS=TestNetwork TestNetworkMapping TestEA
all: $(TESTS)


TestNetwork: TestNetwork.cpp $(OBJECTS)
	$(CPP) TestNetwork.cpp $(SRC_DIR)/Network.o $(CFLAGS) $(LDFLAGS) -o $@

TestNetworkMapping: TestNetworkMapping.cpp $(OBJECTS)
	$(CPP) TestNetworkMapping.cpp $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

TestEA: TestEA.cpp $(OBJECTS)
	$(CPP) TestEA.cpp $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@


clean:
	rm -rf $(OBJECTS) $(TESTS)
