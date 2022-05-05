SOURCES := src/*.cpp main.cpp sphere.cpp
OBJECTS := $(foreach file, $(SOURCES), $(file:.cpp=.o))

default: test

test: $(SOURCES)
	clang -std=c++20 -Weverything -Werror -Wno-c++98-compat-pedantic \
	-Wno-global-constructors -Wno-padded -Wno-weak-vtables \
	-Wno-exit-time-destructors -g -o test $(SOURCES) -lncurses -lstdc++ -lm -ldl