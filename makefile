CC=g++
LIBS=-lSDL2 -lSDL2_image
CFLAGS=-Wall -Wextra -Werror -std=c++11 -Og
DEPS=langtonapp.h automata.h
OBJ=main.o langtonapp.o automata.o

all: langtonsant

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

langtonsant: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	-rm -f *.o
	-rm -f langtonsant
