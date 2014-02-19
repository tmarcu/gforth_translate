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
		std::cout << "Unexpected token" << std::endl;
		return -1;
	}
}

void Parser::ParseProgram(void)
{
	NextToken();
	if (Expected(LBRACKET)) {
		std::cerr << "Illegal Program start, missing '['" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "success" << std::endl;
	NextToken();

	if (Expected(RBRACKET)) {
		std::cerr << "Error: Missing closing ']'" << std::endl;
		exit(EXIT_FAILURE);
	}
}
