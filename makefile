all:
	g++ -Wall -c token.cpp
	g++ -Wall -c -std=c++11 lexer.cpp
	g++ -Wall -c -std=c++11 parser.cpp
	g++ -Wall -std=c++11 main.cpp token.o lexer.o parser.o -o translator
stutest:
	./translator < test1.ts > stutest1.out 2>&1
	./translator < test2.ts > stutest2.out 2>&1
	./translator < test3.ts > stutest3.out 2>&1

proftest:
	./translator < $(PROFTEST)

clean:
	rm -rf *.o *.out translator
