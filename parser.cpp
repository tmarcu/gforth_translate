#include <iostream>
#include <vector>
#include <algorithm>

#include "token.h"
#include "token_list.h"
#include "parser.h"

void Parser::NextToken(void)
{
	prevtoken = tok;
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

struct node *Parser::BuildBinaryExpr(struct node **v, enum tokens type)
{
	struct node *n = new struct node;
	n->data = new Token(type);
	n->left = v[0];
	n->right = v[1];
	return n;
}

struct node *Parser::ParseBinary(enum tokens type)
{
	struct node *values[2] = {NULL};

	/* Handle binary math expressions */
	if (Expected(INT) == 0) {
		values[0] = BuildValueNode(prevtoken);
		if (Expected(INT) == 0) {
			values[1] = BuildValueNode(prevtoken);
			return BuildBinaryExpr(values, type);
		} else if (Expected(LBRACKET) == 0) {
			values[1] = ParseProgram();
			return BuildBinaryExpr(values, type);
		}
	}

	/* Handle assignment */
	if (type == EQUAL) {
		if (Expected(NAME) == 0) {
			values[0] = BuildValueNode(prevtoken);
			if (Expected(INT) == 0 || Expected(FLOAT) == 0 ||
			    Expected(STRING) == 0) {
				values[1] = BuildValueNode(prevtoken);
				return BuildBinaryExpr(values, type);
			} else if (Expected(LBRACKET) == 0) {
				values[1] = ParseProgram();
				return BuildBinaryExpr(values, type);
			}
		}
	}

	return NULL;
}

struct node *Parser::ParseStmnt(enum tokens type)
{
	std::cout << "caught statement" << std::endl;
	struct node *values[2] = {NULL};

	if (Expected(LBRACKET) == 0) {
		values[0] = ParseProgram();

		/* Expression should be closed, end w/error otherwise */
		if (Expected(RBRACKET)) {
			std::cerr << "Error: Missing closing ']' in expr" << std::endl;
			return NULL;
		}
	}
	
	/* Handle second expression */
	if (Expected(LBRACKET) == 0) {
		values[1] = ParseProgram();
		return BuildBinaryExpr(values, type);
	}

	if (Expected(INT) == 0 || Expected(FLOAT) == 0 || Expected(NAME) == 0) {
		values[0] = BuildValueNode(prevtoken);
		if (Expected(INT) == 0 || Expected(FLOAT) == 0 || Expected(NAME) == 0) {
			values[1] = BuildValueNode(prevtoken);
			return BuildBinaryExpr(values, type);
		}
	}

	return NULL;
}

struct node *Parser::ParseUnary(enum tokens type)
{
	struct node *values[2] = {NULL};

	if (Expected(INT) == 0) {
		values[1] = BuildValueNode(prevtoken);
	} else if (Expected(LBRACKET) == 0) {
			values[1] = ParseProgram();
			return BuildBinaryExpr(values, type);
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

	std::cout << "DONE PARSING!" << std::endl;

	return return_val;
}

struct node *Parser::ParseProgram(void)
{
	struct node *return_val = new struct node;

	/* Check for inner statements and recurse if any are found */
	if (Expected(LBRACKET) == 0) {
		return_val = ParseProgram();
	} else if (Expected(MULTIPLY) == 0 || Expected(PLUS) == 0 ||
			Expected(MINUS) == 0|| Expected(DIVIDE) == 0 ||
			Expected(COMPARE) == 0 || Expected(POWER) == 0 ||
			Expected(EQUAL) == 0 || Expected(GREATERTHAN) == 0
			|| Expected(LESSTHAN) == 0) {
		return_val =  ParseBinary(prevtoken->GetTag());
	} else if (Expected(NOT) == 0 || Expected(SIN) == 0 ||
			Expected(COS) == 0 || Expected(TAN) == 0) {
		return_val = ParseUnary(prevtoken->GetTag());
	} else if (Expected(IF) == 0 || Expected(WHILE) == 0 ||
			Expected(LET) == 0 || Expected(PRINT) == 0) {
		return_val = ParseStmnt(prevtoken->GetTag());
	}

	return return_val;
}
