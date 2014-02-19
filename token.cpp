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