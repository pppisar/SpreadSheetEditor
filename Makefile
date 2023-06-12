CXX = g++
LD = g++
CXXFLAGS = -std=c++17 -Wall -pedantic
LIBS = -lncurses

HDRS = $(wildcard src/*.h ) $(wildcard src/CInterface*.h ) $(wildcard src/CParser*.h ) $(wildcard src/CState*.h )
SRC = $(wildcard src/*.cpp ) $(wildcard src/**/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRC))

all: compile doc

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


run: compile
	./pysarole

clean:
	rm -rf build/
	rm -rf doc/

doc:
	doxygen Doxyfile

-include build/*.d