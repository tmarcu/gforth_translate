/*
 * token.cpp
 * Copyright (C) 2014 Tudor Marcu. All rights reserved.
 */

#include "token.h"

Token::Token(enum tokens tag)
{
	this->tag = tag;
}

void Token::SetTag(enum tokens tag)
{
	this->tag = tag;
}

/* Get num values only from constants */
float Constant::GetValue(void)
{
	if (this->GetTag() == INT)
			return inum;
		else if (this->GetTag() == FLOAT)
			return fnum;
	return 0;
}

std::string Token::GetName(void)
{
	switch(this->GetTag()) {
	case EMPTY:
		return "Empty";
	case IF:
		return "if";
	case ELSE:
		return "else";
	case WHILE:
		return "while";
	case LET:
		return "let";
	case PRINT:
		return "print";
	case EQUAL:
		return "=";
	case NOT:
		return "!";
	case COMPARE:
		return "==";
	case PIPE:
		return "|";
	case MULTIPLY:
		return "*";
	case DIVIDE:
		return "\\";
	case BITWISEAND:
		return "&";
	case AND:
		return "&&";
	case OR:
		return "||";
 	case PLUS:
		return "+";
	case MINUS:
		return "-";
	case POWER:
		return "^";
	case GREATERTHAN:
		return ">";
	case LESSTHAN:
		return "<";
	case LESSEQUAL:
		return "<=";
	case GREATEREQUAL:
		return ">=";
	case NOTEQUAL:
		return "!=";
	case LEFTSHIFT:
		return "<<";
	case RIGHTSHIFT:
		return ">>";
	case INT:
		return "int";
	case FLOAT:
		return "float";
	case STRING:
		return "string";
	case BOOL:
		return "bool";
	case NAME:
		return this->GetString();
	case LBRACKET:
		return "[";
	case RBRACKET:
		return "]";
	case LBRACE:
		return "{";
	case RBRACE:
		return "}";
	case LPAREN:
		return "(";
	case RPAREN:
		return ")";
	case SIN:
		return "sin";
	case COS:
		return "cos";
	case TAN:
		return "tan";
	case ERROR:
		return "error"; 
	default:
		return "NODE";
	}
}
