RESEARCH_DIR=/home/kate/research

SRC_DIR = ${RESEARCH_DIR}/NetworkMapping/EA/src

CPP=g++

CFLAGS=-I/$(SRC_DIR) -g

LDFLAGS=-lgtest -lgtest_main -lpthread -ldl -rdynamic

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))


$(OBJECTS):$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

TESTS=TestNetwork TestNetworkMapping TestEA TestParse TestEAParameters
all: $(TESTS)
	$(foreach f,$^,./$(f);)


TestNetwork: TestNetwork.cpp $(OBJECTS)
	echo $(OBJECTS)
	$(CPP) TestNetwork.cpp $(SRC_DIR)/Network.o $(SRC_DIR)/parse.o $(CFLAGS) $(LDFLAGS) -o $@

TestNetworkMapping: TestNetworkMapping.cpp $(OBJECTS)
	$(CPP) TestNetworkMapping.cpp $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

TestEA: TestEA.cpp $(OBJECTS)
	$(CPP) TestEA.cpp $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

TestParse: TestParse.cpp $(OBJECTS)
	$(CPP) TestParse.cpp $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

TestEAParameters: TestEAParameters.cpp $(OBJECTS)
	$(CPP) TestEAParameters.cpp $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJECTS) $(TESTS)
