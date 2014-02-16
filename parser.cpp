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

void Parser::ParseBinary(void)
{
	if (Expected(INT) == 0) {
		if (Expected(INT) == 0)
			std::cout << "addition" << std::endl;
	}
}

bool Parser::ParseProgram(void)
{
	if (Expected(LBRACKET)) {
		std::cerr << "Error: Unexpected character, missing '['" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (Expected(LBRACKET) == 0) {
		ParseProgram();
	}

	if (Expected(MULTIPLY) == 0) {
		ParseBinary();
	}

	if (Expected(RBRACKET)) {
		std::cerr << "Error: Unexpected character, missing closing ']'" << std::endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}
