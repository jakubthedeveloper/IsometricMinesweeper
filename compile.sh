#!/bin/sh

rm bin/* obj/* -rf
mkdir -p bin
mkdir -p obj

g++ -Wall -fexceptions -O2 -Iinclude -c /home/jakub/programowanie/kuba-minesweeper/main.cpp -o obj/main.o
g++ -Wall -fexceptions -O2 -Iinclude -c /home/jakub/programowanie/kuba-minesweeper/src/Board.cpp -o obj/Board.o
g++ -Wall -fexceptions -O2 -Iinclude -c /home/jakub/programowanie/kuba-minesweeper/src/Field.cpp -o obj/Field.o
g++ -Wall -fexceptions -O2 -Iinclude -c /home/jakub/programowanie/kuba-minesweeper/src/Game.cpp -o obj/Game.o
g++ -Wall -fexceptions -O2 -Iinclude -c /home/jakub/programowanie/kuba-minesweeper/src/IsoConvert.cpp -o obj/IsoConvert.o
g++ -Wall -fexceptions -O2 -Iinclude -c /home/jakub/programowanie/kuba-minesweeper/src/Point.cpp -o obj/Point.o
g++  -o bin/isometric-minesweeper obj/main.o obj/Board.o obj/Field.o obj/Game.o obj/IsoConvert.o obj/Point.o  -s  -lSDL2 -lSDL2_image

