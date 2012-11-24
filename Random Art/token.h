#ifndef __token_h
#define __token_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TYPE_RGB 0
#define TYPE_NUMBER 1

#define M_PI 3.1415926535
#define M_E 2.7183

#define TOKEN_CONST 0
#define TOKEN_X 1
#define TOKEN_Y 2
#define TOKEN_RGB 3
#define TOKEN_IF 4
//#define TOKEN_SIN 5
//#define TOKEN_COS 6
#define TOKEN_SINRGB 5
#define TOKEN_COSRGB 6
#define TOKEN_MOD 7
#define TOKEN_MULT 8
#define TOKEN_EXP 9
#define TOKEN_BLEND 10
#define TOKEN_PLUS 11
#define TOKEN_MOD2 12

#define NUM_MAX_DEPTH_TOKENS 3
#define NUM_TOKENS 13


struct ColorValue {
	double r,g,b;	
};

void setMaxDepth(int d);
double normalize(ColorValue* cv);

class Token;
Token* createToken(int depth);
Token* createTokenFromFile(FILE* file);

// ------------------------- TOKEN --------------------------

class Token
{
public:

	Token(int depth);
	~Token();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

protected:

	ColorValue myValue;
};


// ------------------------ TOKEN_CONST ------------------------------

class Token_Const : public Token
{
public:

	Token_Const(int depth);
	~Token_Const();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);
};


// ------------------------ TOKEN_X ------------------------------

class Token_X : public Token
{
public:

	Token_X(int depth);
	~Token_X();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);
};

// ------------------------ TOKEN_Y ------------------------------

class Token_Y : public Token
{
public:

	Token_Y(int depth);
	~Token_Y();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);
};

// ------------------------ TOKEN_RGB ------------------------------

class Token_RGB : public Token
{
public:

	Token_RGB(int depth);
	~Token_RGB();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* r;
	Token* g;
	Token* b;
};

// ------------------------ TOKEN_IF ------------------------------

class Token_IF : public Token
{
public:

	Token_IF(int depth);
	~Token_IF();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* pred_val;
	Token* then_val;
	Token* else_val;
};

// ------------------------ TOKEN_SIN ------------------------------

class Token_SIN : public Token
{
public:

	Token_SIN(int depth);
	~Token_SIN();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* val;	
};

// ------------------------ TOKEN_COS ------------------------------

class Token_COS : public Token
{
public:

	Token_COS(int depth);
	~Token_COS();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* val;	
};

// ------------------------ TOKEN_SINRGB ------------------------------

class Token_SINRGB : public Token
{
public:

	Token_SINRGB(int depth);
	~Token_SINRGB();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* val;	
};

// ------------------------ TOKEN_COSRGB ------------------------------

class Token_COSRGB : public Token
{
public:

	Token_COSRGB(int depth);
	~Token_COSRGB();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* val;	
};

// ------------------------ TOKEN_MOD ------------------------------

class Token_MOD : public Token
{
public:

	Token_MOD(int depth);
	~Token_MOD();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* val;	
	Token* mod;
};


// ------------------------ TOKEN_MOD2 ------------------------------

class Token_MOD2 : public Token
{
public:

	Token_MOD2(int depth);
	~Token_MOD2();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* val;	
	Token* mod;
};


// ------------------------ TOKEN_MULT ------------------------------

class Token_MULT : public Token
{
public:

	Token_MULT(int depth);
	~Token_MULT();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* v1;	
	Token* v2;
};

// ------------------------ TOKEN_EXP ------------------------------

class Token_EXP : public Token
{
public:

	Token_EXP(int depth);
	~Token_EXP();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* val;		
};

// ------------------------ TOKEN_BLEND ------------------------------

class Token_BLEND : public Token
{
public:

	Token_BLEND(int depth);
	~Token_BLEND();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* val1;
	Token* val2;
	Token* ratio;
};


// ------------------------ TOKEN_PLUS ------------------------------

class Token_PLUS : public Token
{
public:

	Token_PLUS(int depth);
	~Token_PLUS();

	virtual ColorValue* getValue(double x, double y);
	virtual void save(FILE* file);
	virtual void load(FILE* file);

	Token* v1;	
	Token* v2;
};


#endif


