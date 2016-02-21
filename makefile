CC=g++
LD=g++

CFLAGS=-std=c++0x -Wall

srcdir=source
VPATH=source
matsrc=../OutSystem/source

all: Snake

Snake: Tail.o Snake.o LEDMatrixDraw.o LEDMatrix.o Color.o
	g++ $(CFLAGS) Color.o LEDMatrix.o LEDMatrixDraw.o Snake.o Tail.o -o Snake -lbcm2835 -lncurses

Tail.o: $(srcdir)/Tail.cpp $(srcdir)/Tail.hpp
	g++ $(CFLAGS) -c $(srcdir)/Tail.cpp

Snake.o: $(srcdir)/Snake.cpp $(srcdir)/Snake.hpp
	g++ $(CFLAGS) -c $(srcdir)/Snake.cpp

LEDMatrixDraw.o: $(matsrc)/LEDMatrixDraw.cpp $(matsrc)/LEDMatrix.hpp
	g++ $(CFLAGS) -c $(matsrc)/LEDMatrixDraw.cpp

LEDMatrix.o: $(matsrc)/LEDMatrix.cpp $(matsrc)/LEDMatrix.hpp
	g++ $(CFLAGS) -c $(matsrc)/LEDMatrix.cpp

Color.o: $(matsrc)/Color.cpp $(matsrc)/Color.hpp
	g++ $(CFLAGS) -c $(matsrc)/Color.cpp

clean:
	rm *.o
