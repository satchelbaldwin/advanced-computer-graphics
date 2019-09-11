CXX=clang++
CXXFLAGS=-I. -I./math -Wall -Werror
DEPS=./math/math.hpp \
     ./math/v3.hpp \
     ./math/point.hpp \
     ./math/vector.hpp \
     ./math/ray.hpp \
     ./geometry/sphere.hpp
OBJ = ./math/vector.o \
      ./math/point.o \
      ./math/v3.o \
      ./math/ray.o \
      ./geometry/sphere.o \
      ./tests/tests.o 

%.o: %.c $(DEPS)
	$(CXX) -Wall -Werror -c -o $@ $< $(CXXFLAGS)

all: $(OBJ) 
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean: 
	rm $(OBJ)
