/*
 * token.h
 * Copyright (C) 2014 Tudor Marcu. All rights reserved.
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

#include "token_list.h"

class Token
{
public:
	Token(enum tokens tag);
	void SetTag(enum tokens tag);
	enum tokens GetTag(void) { return tag;};
	virtual float GetValue(void) { return 0;};
	virtual std::string GetString(void) { return NULL;};
	std::string GetName(void);

private:
	enum tokens tag;
};

class Constant : public Token
{
public:

	Constant(int value) : Token(INT)
	{
		inum = value;
	}

	Constant(float value) : Token(FLOAT)
	{
		fnum = value;
	}

	Constant(std::string str) : Token(STRING)
	{
		strvalue = str;
	}

	float GetValue(void);
	std::string GetString(void) {return strvalue;};

private:
	int inum;
	float fnum;
	double dnum;
	std::string strvalue;
};

class Statement : public Token
{
public:
	Statement(enum tokens stmnt) : Token(stmnt) {};
};

class Operator : public Token
{
public:
	Operator(enum tokens op) : Token(op) {};
};

class Name : public Token
{
public:
	Name(enum tokens t) : Token(t) {};
	Name(std::string identifier) : Token(NAME)
	{
		name  = identifier;
	}

	std::string GetString(void) { return name;};

private:
	std::string name;
};

class Closure : public Token
{
public:
	Closure(enum tokens op) : Token(op) {};
};

#endif
