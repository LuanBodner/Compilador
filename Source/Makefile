CC=clang++ -std=c++11
DEBUG=-ggdb 
CFLAGS=-Wall
LDFLAGS=-lboost_regex `llvm-config --cxxflags --ldflags --libs core executionengine mcjit interpreter analysis native bitwriter --system-libs`
OPT=-O0

all: lib main link_main

lib:
	$(CC) Token.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) LexicalAnalyzer.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) SyntaxAnalysis.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) CompilerErrors.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) Tree.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) SemanticAnalysis.cpp -c $(OPT) $(CFLAGS) $(DEBUG)
	$(CC) llvmCodeGeneration.cpp -c $(OPT) `llvm-config --cflags` $(CFLAGS) $(DEBUG)
main:
	$(CC) main.cpp -c $(OPT) $(CFLAGS) $(DEBUG) -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS
 
link_main:
	$(CC) main.o Token.o LexicalAnalyzer.o SyntaxAnalysis.o CompilerErrors.o Tree.o SemanticAnalysis.o llvmCodeGeneration.o $(LDFLAGS) -o compiler
	
clean:
	rm -f *.out
	rm -f *.o
	rm -f compiler
	rm -f tree.txt token.txt symbols.txt tiny.bc tiny.ll

cleanf:
	rm -f tree.txt  token.txt  symbol.txt tiny.bc tiny.ll referenceTable.txt 
	rm -f tree2.txt token2.txt symbol2.txt tiny.bc tiny.ll referenceTable.txt 
