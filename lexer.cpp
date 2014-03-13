/*
 * lexer.cpp
 * Copyright (C) 2014 Tudor Marcu. All rights reserved.
 */

#include <iostream>
#include <istream>
#include <ostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <unordered_map>

#include "lexer.h"
#include "token.h"
#include "token_list.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

std::unordered_map<string, enum tokens> idhashtable;
int line = 1;

Lexer::Lexer(void)
{
	CreateTable();
}

char Lexer::readchar(void)
{
	return cin.get();
}

Token *Lexer::CheckUnaryOp(const char &c)
{
	switch(c) {
		case '&':
			return new Operator(BITWISEAND);
		case '=':
			return new Operator(EQUAL);
		case '!':
			return new Operator(NOT);
		case '|':
			return new Operator(PIPE);
		case '*':
			return new Operator(MULTIPLY);
		case '^':
			return new Operator(POWER);
		case '+':
			return new Operator(PLUS);
		case '-':
			return new Operator(MINUS);
		case '>':
			return new Operator(GREATERTHAN);
		case '<':
			return new Operator(LESSTHAN);
		case '/':
			return new Operator(DIVIDE);
		default:
			return new Token(ERROR);
	}
}

Token *Lexer::check_binary_ops(const char &c, const char &next)
{
	/* Handle unequal binary compares or return token if valid */
	if (next != c) {
		switch(next) {
			case '=':
				if (c == '<') {
					return new Operator(LESSEQUAL);
				}else if (c == '>')
					return new Operator(GREATEREQUAL);
				else if (c == '!')
					return new Operator(NOTEQUAL);
				else if (c == ':') {
					return new Operator(EQUAL);
				}
			break;
			default:
				return CheckUnaryOp(c);
		}
	}

	/* Check for equal binary tokens - i.e &&, || */
	if (next == c) {
		switch(next) {
			case '&':
				return new Operator(AND);
			break;
			case '|':
				return new Operator(OR);
			break;
			case '=':
				return new Operator(COMPARE);
			break;
			case '<':
				return new Operator(LEFTSHIFT);
			break;
			case '>':
				return new Operator(RIGHTSHIFT);
			break;
			default:
				return new Token(ERROR);
		}
	}
	return new Token(ERROR);
}

Token *Lexer::GetNum(const char &c, char &next)
{
	string num;
	string power;
	bool isfloat = false;
	int neg = 1;

	num += c;
	while(isdigit(next)) {
		num += next;
		next = readchar();
	}

	if (next == '.') {
		isfloat = true;
		num += next;
		next = readchar();

		while(next != 'e' && isdigit(next)) {
			num += next;
			next = readchar();
		}
	}

	if (next == 'e') {
		isfloat = true;
		next = readchar();
		if (next == '-') {
			neg = -1;
			next = readchar();
		}

		while(isdigit(next)) {
			power += next;
			next = readchar();
		}
	}
		
	if (isfloat == true)
		return new Constant((float) atof(num.c_str()) *(float) pow(10, neg * atoi(power.c_str())));

	return new Constant(atoi(num.c_str()));
}

Token *Lexer::CheckIdentifier(const char &c, char & next)
{
	string identifier;

	identifier += c;

	while (isalnum(next)) {
		identifier += next;
		next = readchar();
	}

	/* Check if exists otherwise add to table */
	if (idhashtable.find(identifier) == idhashtable.end()) {
		idhashtable.emplace(identifier, NAME);
		return new Name(identifier);
	} else {
		return new Name(idhashtable[identifier]);
	}

	return new Token(NAME);
}

Token *Lexer::CheckString(const char &c, char &next)
{
	string body;

	while(next != '"') {
		if (next == -1)
			return new Token(ERROR);
		body += next;
		next = readchar();
	}

	next = readchar();
	return new Constant(body);
}

Token *Lexer::ScanToken(char &c, char &next)
{
	for (;; c = readchar()) {
		if (c == ' ' || c == '\t')
			continue;
		else if (c == '\n')
			line++;
		else
			break;
	}

	next = readchar();

	/* Eat up the comments we don't need them */
	if (c == '/' && next == '*') {
		while (true) {
			c = readchar();
			next = readchar();
			if ((c == '*' && next == '/') || next == -1)
				return new Token(COMMENTS);
		}
	}

	switch(c) {
		case '[':
			return new Closure(LBRACKET);
		break;
		case ']':
			return new Closure(RBRACKET);
		break;
		case '&':
		case '|':
		case '=':
		case '>':
		case '<':
		case '!':
		case '^':
		case '*':
		case '+':
		case '-':
		case ':':
			return (check_binary_ops(c, next));
		break;
		case '.':
			return GetNum(c, next);
		default:
		break;
	}

	if (isdigit(c))
		return GetNum(c, next);

	if (isalpha(c))
		return CheckIdentifier(c, next);

	if (c == '"')
		return CheckString(c, next);

	if (c == -1)
		return new Token(END);

	/* Shouldn't ever reach this if all funcs return a token */
	return new Token(ERROR);	
}

void Lexer::CreateTable(void)
{
	idhashtable.emplace("if", IF);
	idhashtable.emplace("let", LET);
	idhashtable.emplace("or", OR);
	idhashtable.emplace("while", WHILE);
	idhashtable.emplace("and", AND);
	idhashtable.emplace("sin", SIN);
	idhashtable.emplace("cos", COS);
	idhashtable.emplace("int", INT);
	idhashtable.emplace("float", FLOAT);
	idhashtable.emplace("string", STRING);
	idhashtable.emplace("bool", BOOL);
	idhashtable.emplace("tan", TAN);
	idhashtable.emplace("print", PRINT);
	idhashtable.emplace("concat", CONCAT);
}

void Lexer::CheckError(Token *t)
{
	if (t->GetTag() == ERROR)
		std::cerr << "!\n**Error: line " << line << endl;
	else if (t->GetTag() == EMPTY) {
		cout << "EMPTY TOKEN! " << line << endl;
	}
}
