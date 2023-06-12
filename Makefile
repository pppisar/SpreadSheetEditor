CXX = g++
LD = g++
CXXFLAGS = -std=c++17 -Wall -pedantic
LIBS = -lncurses

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
	rm -rf build/ 2>/dev/null
	rm -rf doc/ 2>/dev/null
	rm pysarole 2>/dev/null

doc:
	doxygen Doxyfile

fsanitize: $(OBJS)
	@mkdir -p build
	@mkdir -p build/CInterface
	@mkdir -p build/CParser
	@mkdir -p build/CState
	$(LD) $(CXXFLAGS) -fsanitize=address -o pysarole $(OBJS) $(LIBS)
	./pysarole

valgrind: $(OBJS)
	@mkdir -p build
	@mkdir -p build/CInterface
	@mkdir -p build/CParser
	@mkdir -p build/CState
	$(LD) $(CXXFLAGS) -g -o pysarole $(OBJS) $(LIBS)
	valgrind --leak-check=full ./pysarole

-include build/*.d