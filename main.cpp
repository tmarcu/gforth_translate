#include <iostream>
#include <list>
#include <algorithm>

#include "token.h"
#include "token_list.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

int main(int argc, char *argv[])
{
	string input;
	char c;
	char next;
	Token *tok;
	Lexer scanner = Lexer();
	Parser parser = Parser();

	c = scanner.readchar();

	while (c != -1) {
		tok = scanner.ScanToken(c, next);
		scanner.CheckError(tok);
		parser.AddToken(tok);
		cout << c << " " << tok->GetTag() << endl;
		c = next;
	}

	if (parser.ParseProgram() == 0)
		cout << "Done: Parsed tokens!" << endl;

	return 0;
}