CC=g++ -std=c++11
DEBUG=-ggdb
CFLAGS=-Wall
LDFLAGS=
OPT=-O0

all: lib main link_main

lib:
	$(CC) Token.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) LexicalAnalyzer.cpp -c $(OPT) $(CFLAGS) $(DEBUG)

main:
	$(CC) main.cpp -c $(OPT) $(CFLAGS) $(DEBUG)

link_main:
	$(CC) main.o Token.o LexicalAnalyzer.o $(LDFLAGS)
	
clean:
	rm -f *.out
	rm -f *.exe
	rm -f *.o