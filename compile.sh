#!/bin/sh

rm bin/* obj/* -rf
mkdir -p bin
mkdir -p obj

g++ -Wall -fexceptions -O2 -Iinclude -c ./main.cpp -o obj/main.o
g++ -Wall -Wno-write-strings -fexceptions -O2 -Iinclude -c ./src/Board.cpp -o obj/Board.o
g++ -Wall -fexceptions -O2 -Iinclude -c ./src/Field.cpp -o obj/Field.o
g++ -Wall -fexceptions -O2 -Iinclude -c ./src/Game.cpp -o obj/Game.o
g++ -Wall -fexceptions -O2 -Iinclude -c ./src/IsoConvert.cpp -o obj/IsoConvert.o
g++ -Wall -fexceptions -O2 -Iinclude -c ./src/Point.cpp -o obj/Point.o
g++ -Wall -Wno-write-strings -fexceptions -O2 -Iinclude -c ./src/Gui.cpp -o obj/Gui.o
g++ -Wall -fexceptions -O2 -Iinclude -c ./src/TextureLoader.cpp -o obj/TextureLoader.o

g++ -o bin/isometric-minesweeper \
  obj/main.o \
  obj/Board.o \
  obj/Field.o \
  obj/Game.o \
  obj/IsoConvert.o \
  obj/Point.o \
  obj/Gui.o \
  obj/TextureLoader.o \
  -s -lSDL2 -lSDL2_image

