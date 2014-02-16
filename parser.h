#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>

#include "token.h"
#include "token_list.h"
#include "lexer.h"

class Parser {
public:
	Parser(void) {};

	void NextToken(void);
	void PrintTokens(void);
	void Print(void);
	void AddToken(Token *t);
	bool ParseProgram(void);
	void ParseBinary(void);
	bool Expected(enum tokens t);
private:
	Token *tok;
	std::vector<Token *> tokstream;
	std::vector<Token *>::iterator iter;	
};

#endif
