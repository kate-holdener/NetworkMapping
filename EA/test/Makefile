RESEARCH_DIR=/home/kate/research

SRC_DIR = ${RESEARCH_DIR}/NetworkMapping/EA/src

CPP=g++

CFLAGS=-I/$(SRC_DIR) -g

LDFLAGS=-lgtest -lgtest_main -lpthread

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

$(OBJECTS):$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

all: TestNetwork TestNetworkMapping

TestNetwork: TestNetwork.cpp $(OBJECTS)
	echo $(OBJECTS)
	$(CPP) TestNetwork.cpp $(SRC_DIR)/Network.o $(CFLAGS) $(LDFLAGS) -o $@

TestNetworkMapping: TestNetworkMapping.cpp $(OBJECTS)
	echo $(OBJECTS)
	$(CPP) TestNetworkMapping.cpp $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJECTS) TestNetwork TestNetworkMapping
