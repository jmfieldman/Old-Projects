#ifndef __equation_h
#define __equation_h


#define CHAR_XVAR 'x'
#define CHAR_YVAR 'y'
#define CHAR_ADDITION '+'
#define CHAR_SUBTRACTION '-'
#define CHAR_MULTIPLICATION '*'
#define CHAR_DIVISION '/'
#define CHAR_POWER '^'
#define CHAR_LOG 'L'
#define CHAR_LN 'l'
#define CHAR_SIN 's'
#define CHAR_COS 'c'
#define CHAR_TAN 'a'
#define CHAR_ASIN 'S'
#define CHAR_ACOS 'C'
#define CHAR_ATAN 'A'
#define CHAR_ABS 'b'
#define CHAR_NEG '!'

#define CONST_I 'i'

#define CONST_E 'e'
#define CONST_E_VALUE 2.71828182846

#define CONST_PI 'p'
#define CONST_PI_VALUE 3.14159265359

int isValue(char ch);
int isOperator(char ch);
int isFunction(char ch);

void killWhiteSpace(char* str);
void condenseFunctionNames(char* str);
void expandConstants(char* str);
void findNegates(char* str);
void fixDecimals(char* str);
void fixImplicitMultiplication(char* str);

void cleanEquation(char* str);

int checkParens(char* str);
int checkValidOps(char* str);
int checkDecimalPoints(char* str);
int checkInvalidSymbols(char* str);


int nextToken(char* str, int currentIndex);
int prevToken(char* str, int currentIndex);
void infuseOrderOfOperations(char* str, int startpos, int endpos);

#endif