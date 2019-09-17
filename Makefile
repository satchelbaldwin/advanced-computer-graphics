CXX=clang++
CXXFLAGS=-I. -Wall -Werror
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
	rm $(OBJ)
