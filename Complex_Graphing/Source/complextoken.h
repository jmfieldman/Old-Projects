#ifndef __complextoken_h
#define __complextoken_h

#include "token.h"
#include "ComplexValue.h"

// --------------------------------


class ComplexToken
{
private:

	int type;

	ComplexValue* value;

	ComplexToken* op1;
	ComplexToken* op2;

public:

	ComplexToken();
	~ComplexToken();
	
	void setValue(ComplexValue* v);
	void setType(int t);

	void setOperands(ComplexToken* o1, ComplexToken* o2);

	int getType();
	ComplexValue* getValue();

	ComplexValue* evaluate(ComplexValue* value);
	int checkFunction(ComplexValue* value);
		

};


ComplexToken* buildComplexTokenFromString(char* str);

#endif