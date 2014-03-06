CC=g++
CFLAGS = -Wall -std=c++11

translator: main.cpp token.o lexer.o parser.o
	$(CC) -o translator main.cpp token.o lexer.o parser.o

token.o: token.cpp token.h
	$(CC) -c token.cpp

lexer.o: lexer.cpp lexer.h
	$(CC) $(CFLAGS) -c lexer.cpp

parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp

stutest:
	./translator < test1.ts > stutest1.out 2>&1
	./translator < test2.ts > stutest2.out 2>&1
	./translator < test3.ts > stutest3.out 2>&1

proftest:
	./translator < $(PROFTEST)

clean:
	rm -rf *.o *.out translator
