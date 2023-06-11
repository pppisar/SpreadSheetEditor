CXX = g++
LD = g++
CXXFLAGS = -std=c++17 -Wall -pedantic
LIBS = -lncurses

SRC = $(wildcard src/*.cpp ) $(wildcard src/**/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRC))

all: compile run

compile: $(OBJS)
	@mkdir -p build
	@mkdir -p build/CInterface
	@mkdir -p build/CParser
	@mkdir -p build/CState
	$(LD) $(CXXFLAGS) -o pysarole $(OBJS) $(LIBS)

build/%.o: src/%.cpp
	@mkdir -p build
	@mkdir -p build/CInterface
	@mkdir -p build/CParser
	@mkdir -p build/CState
	$(CXX) $(CXXFLAGS) -MMD -c -o $@ $<


run:
	./pysarole

clean:
	rm -rf build

fsanitize:
# Compile and run project using fsanitize

valgrind:
# Compile and run project using valgrind

doc:
# Automatically generate documentation in the pysarole/doc directory with doxygen.

-include build/*.d