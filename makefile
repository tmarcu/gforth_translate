all:
	g++ -Wall -c token.cpp
	g++ -Wall -c -std=c++11 lexer.cpp
	g++ -Wall -c -std=c++11 parser.cpp
	g++ -Wall -std=c++11 main.cpp token.o lexer.o parser.o -o translator
stutest:
	./translator < test.ts > stutest.out 2>&1
	cat stutest.out
clean:
	rm -rf *.o *.out translator
