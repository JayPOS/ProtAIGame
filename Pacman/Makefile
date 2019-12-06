CCPP=g++
# SOURCES=sdl_functions.cpp main.cpp
CPPFLAGS= -lm -O2 -pedantic -Wall
SDLFLAGS =-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
FLAGS=$(CPPFLAGS) $(SDLFLAGS)


all: program clean

program: main.o sdl_functions.o editor.o jogo.o pacman.o ghost.o astar.o
	$(CCPP) -o game main.o sdl_functions.o editor.o jogo.o pacman.o ghost.o astar.o $(FLAGS)

main.o: ./src/main.cpp sdl_functions.o
	$(CCPP) -c ./src/main.cpp

sdl_functions.o: ./src/sdl_functions.cpp
	$(CCPP) -c ./src/sdl_functions.cpp

editor.o: ./src/editor.cpp
	$(CCPP) -c ./src/editor.cpp

jogo.o: ./src/jogo.cpp pacman.o
	$(CCPP) -c ./src/jogo.cpp

pacman.o: ./src/pacman.cpp
	$(CCPP) -c ./src/pacman.cpp

ghost.o: ./src/ghost.cpp
	$(CCPP) -c ./src/ghost.cpp

astar.o: ./src/astar.cpp
	$(CCPP) -c ./src/astar.cpp

clean:
	rm -r *.o 
