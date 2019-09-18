CXX=g++
CXXFLAGS=-I. -Wall -Werror -g -ggdb

# https://stackoverflow.com/questions/714100/os-detecting-makefile
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
     CXXFLAGS += -no-pie
endif
ifeq ($(UNAME), Darwin)
     CXXFLAGS += -std=c++11
endif

DEPS=./math/math.hpp \
     ./math/v3.hpp \
     ./math/point.hpp \
     ./math/vector.hpp \
     ./math/ray.hpp \
     ./geometry/sphere.hpp \
     ./canvas/canvas.hpp

OBJ = ./math/vector.o \
      ./math/point.o \
      ./math/v3.o \
      ./math/ray.o \
      ./geometry/sphere.o \
      ./canvas/canvas.o

%.o: %.c $(DEPS)
	$(CXX) -Wall -Werror -c -o $@ $< $(CXXFLAGS)

.PHONY: lib
lib: $(OBJ)

test: ./tests/tests.o $(OBJ) 
	$(CXX) -o $@ $^ $(CXXFLAGS)

first-image: ./tests/first-image.o $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJ)
	rm -f ./tests/first-image.o
	rm -f ./tests/tests.o
