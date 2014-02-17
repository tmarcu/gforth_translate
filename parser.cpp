#include <iostream>
#include <vector>
#include <algorithm>

#include "token.h"
#include "token_list.h"
#include "parser.h"

void Parser::NextToken(void)
{
	tok = *iter;
	++iter;
}

void Parser::AddToken(Token *t)
{
	tokstream.push_back(t);
	iter = tokstream.begin();
	tok = *iter;
}

void Parser::PrintTokens(void)
{
	for (std::vector<Token *>::iterator it = tokstream.begin(); it != tokstream.end(); ++it) {
		tok = *it;
		std::cout << "ID: " << tok->GetTag() << std::endl;
	}
}

void Parser::Print(void)
{
	std::cout << "ID:" << tok->GetTag() << std::endl;
}

bool Parser::Expected(enum tokens t)
{
	if (tok->GetTag() == t) {
		NextToken();
		return 0;
	} else {
		return -1;
	}
}

struct node *Parser::BuildValueNode(Token *t)
{
	struct node *n = new struct node;
	n->data = t;
	n->left = NULL;
	n->right = NULL;

	return n;
}

struct node *Parser::BuildPlusExpr(Token **v)
{
	struct node *n = new struct node;
	n->data = new Token(MULTIPLY);
	n->left = BuildValueNode(v[0]);
	n->right = BuildValueNode(v[1]);

	return n;
}

struct node *Parser::ParseBinary(void)
{
	Token *values[2] = {NULL};
	std::vector<Token *>::iterator it = iter;
	std::cout <<" in binary" << std::endl;
	if (Expected(INT) == 0) {
		--it;
		values[0] = *it;
		++it;
		if (Expected(INT) == 0) {
			--it;
			values[1] = *it;
			++it;
			std::cout << "returning plus expr " << values[1]->GetTag() << std::endl;
			return BuildPlusExpr(values);
		}
	}

	return NULL;
}

struct node *Parser::ProgramStart(void)
{
	struct node *return_val;

	if (Expected(LBRACKET)) {
		std::cerr << "Error: Unexpected character, missing '['" << std::endl;
		exit(EXIT_FAILURE);
	}

	return_val = ParseProgram();

	if (Expected(RBRACKET)) {
		std::cerr << "Error: Unexpected character, missing closing ']'" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "DONE!" << std::endl;

	return return_val;
}

struct node *Parser::ParseProgram(void)
{
	struct node *return_val = new struct node;

	std::cout << "in parseprog" << std::endl;
	/* Check for inner statements and recurse if any are found */
	if (Expected(LBRACKET) == 0) {
		return_val = ParseProgram();
	} else if (Expected(MULTIPLY) == 0 || Expected(PLUS) == 0) {
		return_val =  ParseBinary();
	} /* Every statement MUST have an operator to start the
	   * expression. i.e [* 1 2] = valid, [3 5] = INVALID */
	std::cout <<" lol" << std::endl;

	return return_val;
}
