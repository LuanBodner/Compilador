CC=g++ -std=c++11
DEBUG=-ggdb
CFLAGS=-Wall
LDFLAGS= -lboost_regex
OPT=-O0

all: lib main link_main

lib:
	#$(CC) Token.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	#$(CC) LexicalAnalyzer.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	#$(CC) SyntaxAnalysis.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) CompilerErrors.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	#$(CC) Tree.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) SemanticAnalysis.cpp -c $(OPT) $(CFLAGS) $(DEBUG)	

main:
	#$(CC) main.cpp -c  $(OPT) $(CFLAGS) $(DEBUG)

link_main:
	$(CC) main.o Token.o LexicalAnalyzer.o SyntaxAnalysis.o CompilerErrors.o Tree.o SemanticAnalysis.o -o compiler $(LDFLAGS)
	
clean:
	rm -f *.out
	rm -f *.o
	rm -f compiler