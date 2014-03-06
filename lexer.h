/*
 * lexer.h
 * Copyright (C) 2014 Tudor Marcu. All rights reserved.
 */

#ifndef LEXER_H
#define LEXER_H

#include <iostream>

#include "token_list.h"
#include "token.h"

class Lexer {
public:
	Lexer(void);

	char readchar(void);
	void CreateTable(void);
	void CheckError(Token *t);

	Token *ScanToken(char &c, char &next);
	Token *CheckString(const char &c, char &next);
	Token *CheckIdentifier(const char &c, char &next);
	Token *GetNum(const char &c, char &next);
	Token *check_binary_ops(const char &c, const char &next);
	Token *CheckUnaryOp(const char &c);	
};

#endif