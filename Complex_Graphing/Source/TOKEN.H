#ifndef __token_h
#define __token_h


// ------ Types of functions --------

#define CONSTANT 0

#define XVAR 1
#define YVAR 2

#define ADDITION 3
#define SUBTRACTION 4
#define MULTIPLICATION 5
#define DIVISION 6

#define POWER 7

#define LOG 8
#define LN 9

#define SIN 10
#define COS 11
#define TAN 12
#define ASIN 13
#define ACOS 14
#define ATAN 15

#define ABS 16
#define NEG 17

#define PASS_THROUGH 100


// --------------------------------


class Token
{
private:

	int type;

	double value;

	Token* op1;
	Token* op2;

public:

	Token();
	~Token();
	
	void setValue(double v);
	void setType(int t);

	void setOperands(Token* o1, Token* o2);

	int getType();
	double getValue();

	double evaluate(double xval, double yval);
	int checkFunction(double xval, double yval);
		

};


Token* buildTokenFromString(char* str);

#endif