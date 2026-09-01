CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g


SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
BIN = eventflow

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(BIN)

clean:
	rm -f $(OBJECTS) $(BIN)