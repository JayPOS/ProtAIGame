CCPP=g++
# SOURCES=sdl_functions.cpp main.cpp
CPPFLAGS=-O2 -pedantic -Wall
SDLFLAGS =-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
FLAGS=$(CPPFLAGS) $(SDLFLAGS)


all: program clean

program: main.o sdl_functions.o editor.o pacman.o
	$(CCPP) -o game main.o sdl_functions.o editor.o pacman.o $(FLAGS)

main.o: ./files/main.cpp sdl_functions.o
	$(CCPP) -c ./files/main.cpp

sdl_functions.o: ./files/sdl_functions.cpp
	$(CCPP) -c ./files/sdl_functions.cpp

editor.o: ./files/editor.cpp
	$(CCPP) -c ./files/editor.cpp

pacman.o: ./files/pacman.cpp
	$(CCPP) -c ./files/pacman.cpp

clean:
	rm -r *.o 
