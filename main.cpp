/*
 * main.cpp
 * Copyright (C) 2014 Tudor Marcu. All rights reserved.
 */

#include <iostream>

#include "token.h"
#include "token_list.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

bool tofloat = false;
bool ifflag = false;

static void CheckTypes(struct node *n)
{
	if (n == NULL)
		return;

	CheckTypes(n->left);
	CheckTypes(n->right);

	switch (n->data->GetTag()) {
	case FLOAT:
		tofloat = true;
	break;
	case IF:
		ifflag = true;
	break;
	default:
	break;			
	}
}


static void postorder(struct node *n)
{
	float numsize = 0;

	if (n == NULL)
		return;

	postorder(n->left);
	postorder(n->right);

	switch (n->data->GetTag()) {
	case INT:
		numsize = n->data->GetValue();
		cout << numsize << " ";
		if (tofloat == true)
			cout << "s>f ";
	break;
	case FLOAT:
		numsize = n->data->GetValue();

		cout << numsize;
		if (numsize > 999999)
			cout << " ";
		if (tofloat != false && numsize < 999999)
			cout << "e ";
		else
			cout << " ";
	break;
	case PLUS:
	case MINUS:
	case MULTIPLY:
	case DIVIDE:
		if (tofloat == true)
			cout << "f";
		cout << n->data->GetName() << " ";
	break;
	case POWER:
		if (tofloat == true)
			cout << "f** ";
		else
			cout << "ERROR: Cannot do '^' on integer values" << endl;
	break;
	case STRING:
		cout << "s\" " << n->data->GetString() << "\" ";
	break;
	case CONCAT:
		cout << "append";
	break;
	case COS:
		cout << "fcos ";
	break;
	case SIN:
		cout << "fsin ";
	break;
	case TAN:
		cout << "ftan ";
	break;
	case EQUAL:
		cout << "! ";
	break;
	default:
		cout << n->data->GetName() << " ";
	break;			
	}
}

static void TraverseIf(struct node *n)
{
	if (n == NULL)
		return;

	if (n->data->GetTag() == IF) {
		postorder(n->left);
		cout << "if ";
		postorder(n->right); cout << "else ";
		postorder(n->mid); cout << "endif ;" << endl;
	}
}

static void preorder(struct node *n, char pos)
{
	if (n == NULL)
		return;

	if (pos == 'l') {
		if (n->data->GetTag() == INT || n->data->GetTag() == FLOAT)
			cout << "[" << n->data->GetValue() << "]";

		cout << "[" << n->data->GetName() << "]";
	} else if (pos == 'r') {
		if (n->data->GetTag() == INT || n->data->GetTag() == FLOAT)
			cout << "[" << n->data->GetValue() << "]";

		cout << "\t\t[" << n->data->GetName() << "]" << endl;
	} else {
		if (n->data->GetTag() == INT || n->data->GetTag() == FLOAT)
			cout << "[" << n->data->GetValue() << "]";

		cout << "\t[" << n->data->GetName() << "]" << endl;
	}

	if (n->right != NULL && (n->right->left != NULL || n->right->right != NULL)) {
		preorder(n->left, 'l');
		preorder(n->right, 'b');
	} else if (n->left != NULL && (n->left->left != NULL || n->left->right != NULL)) {
		preorder(n->left, 'b');
		preorder(n->right, 'r');
	} else {
		preorder(n->left, 'l');
		preorder(n->right, 'r');
	}
}


int main(int argc, char *argv[])
{
	string input;
	char c;
	char next;
	Token *tok;
	Lexer scanner = Lexer();
	Parser parser = Parser();

	c = scanner.readchar();

	while (c != -1) {
		tok = scanner.ScanToken(c, next);
		scanner.CheckError(tok);
		parser.AddToken(tok);
		cout << c << " " << tok->GetTag() << endl;
		c = next;
	}

	struct node *list = parser.ProgramStart();

	cout << "Postorder (GForth Code): " << endl;

	/* First pass checks types and sets appropriate flags */
	CheckTypes(list);

	/* Second pass formats and translates according to flags set */
	if (ifflag == true)
		TraverseIf(list);

	else
		postorder(list);
		
	cout << endl;

	cout << "Preorder (Tree Diagram): " << endl;

	preorder(list, 'b');

	return 0;
}
