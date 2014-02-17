#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>

#include "token.h"
#include "token_list.h"
#include "lexer.h"

struct node {
	struct Token *data;
	struct node *left;
	struct node *right;
};

class Parser {
public:
	Parser(void) {};

	void NextToken(void);
	void PrintTokens(void);
	void Print(void);
	void AddToken(Token *t);
	struct node *ProgramStart(void);
	struct node *ParseProgram(void);
	struct node *ParseBinary(void);
	bool Expected(enum tokens t);

	struct node *BuildValueNode(Token *t);
	struct node *BuildPlusExpr(Token **v);
private:
	Token *tok;
	std::vector<Token *> tokstream;
	std::vector<Token *>::iterator iter;	
};

#endif
