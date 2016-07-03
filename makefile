CC=x86_64-w64-mingw32-g++
LIBS=-lSDL2 -static-libgcc -static-libstdc++ -static -lpthread -lmingw32 -mwindows 
CFLAGS=-Wextra -Werror -std=c++11 -Og -I/home/petra/Downloads/SDL2-2.0.4/include -L/home/petra/Downloads/SDL2-2.0.4/lib/x64
DEPS=langtonapp.h automata.h
OBJ=main.o langtonapp.o automata.o

all: langtonsant.exe

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

langtonsant.exe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	-rm -f *.o
	-rm -f langtonsant.exe
