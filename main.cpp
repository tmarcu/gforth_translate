#include <iostream>
#include <list>
#include <algorithm>

#include "token.h"
#include "token_list.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

static void postorder(struct node *n)
{
	if (n != NULL) {
		postorder(n->left);
		postorder(n->right);
		switch (n->data->GetTag()) {
		case INT:
		case FLOAT:
			cout << n->data->GetValue() << " ";
		break;
		default:
			cout << n->data->GetName() << " ";
		break;			
		}
	}
}

static void preorder(struct node *n, char pos)
{
	if (n != NULL) {
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

	cout << "Postorder: " << endl;

	postorder(list);

	cout << endl;

	cout << "Preorder (Tree Diagram): " << endl;

	preorder(list, 'b');

	return 0;
}
