main: main.o sudoku.o game.o
	g++ -o main -std=c++11 main.o sudoku.o game.o

main.o: main.cpp
	g++ -c -std=c++11 main.cpp
	
sudoku.o: sudoku.cpp sudoku.h 
	g++ -c -std=c++11 sudoku.cpp

game.o: game.cpp game.h 
	g++ -c -std=c++11 game.cpp

clean: 
	-rm *.o 
