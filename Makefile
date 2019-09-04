CC=clang++
CFLAGS=-I.
DEPS=./math/math.hpp
OBJ = ./math/vector.o \
      ./math/point.o \
      ./tests/tests.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


