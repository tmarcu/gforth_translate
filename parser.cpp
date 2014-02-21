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

struct node *Parser::BuildBinaryExpr(struct node **v)
{
	struct node *n = new struct node;
	n->data = new Token(MULTIPLY);
	n->left = v[0];
	n->right = v[1];
	return n;
}

struct node *Parser::ParseBinary(enum tokens type)
{
	struct node *values[2] = {NULL};
	std::vector<Token *>::iterator it = iter;

	if (Expected(INT) == 0) {
		--it;
		values[0] = BuildValueNode(*it);
		++it;
		if (Expected(INT) == 0) {
			--it;
			values[1] = BuildValueNode(*it);
			++it;
			return BuildBinaryExpr(values);
		} else if (Expected(LBRACKET) == 0) {
			values[1] = ParseProgram();
			return BuildBinaryExpr(values);
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
	auto it = iter;
	auto prevtok = tok; /* To pass the correct operator to ParseBinary */

	/* Check for inner statements and recurse if any are found */
	if (Expected(LBRACKET) == 0) {
		return_val = ParseProgram();
	} else if (Expected(MULTIPLY) == 0 || Expected(PLUS) == 0 ||
			Expected(MINUS) == 0|| Expected(DIVIDE) == 0 ||
			Expected(COMPARE) == 0 || Expected(POWER) == 0 ||
			Expected(EQUAL) == 0 || Expected(GREATERTHAN) == 0
			|| Expected(LESSTHAN) == 0) {
		--it;
		prevtok = *it;
		return_val =  ParseBinary(prevtok->GetTag());
	} /* Every statement MUST have an operator to start the
	   * expression. i.e [* 1 2] = valid, [3 5] = INVALID */

	return return_val;
}
