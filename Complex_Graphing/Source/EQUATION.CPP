#include "equation.h" 
#include "token.h"
#include <stdlib.h>
#include <stdio.h>


int isValue(char ch)
{
	switch (ch)
	{
	case CHAR_XVAR:
	case CHAR_YVAR:
	case ')':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case CONST_I:

		return 1;
	}
	return 0;
}

int isOperator(char ch)
{
	switch (ch)
	{
	case CHAR_ADDITION:
	case CHAR_SUBTRACTION:
	case CHAR_MULTIPLICATION:
	case CHAR_DIVISION:
	case CHAR_POWER:

		return 1;
	}
	return 0;
}

int isFunction(char ch)
{
	switch (ch)
	{
	case CHAR_SIN:
	case CHAR_COS:
	case CHAR_TAN:
	case CHAR_ASIN:
	case CHAR_ACOS:
	case CHAR_ATAN:
	case CHAR_LN:
	case CHAR_LOG:
	case CHAR_ABS:
	case CHAR_NEG:
	case '(':

		return 1;
	}
	return 0;
}


int strequal(char* str1, char* str2)
{
	int pos = 0;

	while (str2[pos] != 0)
	{
		if (str1[pos] != str2[pos]) return 0;
		pos++;
	}

	return 1;
}

void condenseFunc(char* str, char val, int spaces)
{
	str[0] = val;

	for (int x = 1; x < spaces; x++) str[x] = ' ';
}

void injectChar(char* str, char ch)
{
	char temp[10000];
	sprintf(temp,"%s",str);
	sprintf(str,"%c%s",ch,temp);
}

void killWhiteSpace(char* str)
{
	int pos = 0;

	while (str[pos] != 0)
	{
		if (str[pos] == ' ')
		{
			int pos2 = pos;
			while (str[pos2] != 0)
			{
				str[pos2] = str[pos2+1];
				pos2++;
			}
		}
		if (str[pos] != ' ') pos++;
	}
}

void condenseFunctionNames(char* str)
{
	int pos = 0;

	while (str[pos] != 0)
	{
		if (strequal( &(str[pos]), "log" )) condenseFunc( &(str[pos]), CHAR_LOG, 3);
		if (strequal( &(str[pos]), "ln" )) condenseFunc( &(str[pos]), CHAR_LN, 2);

		if (strequal( &(str[pos]), "sin" )) condenseFunc( &(str[pos]), CHAR_SIN, 3);
		if (strequal( &(str[pos]), "cos" )) condenseFunc( &(str[pos]), CHAR_COS, 3);
		if (strequal( &(str[pos]), "tan" )) condenseFunc( &(str[pos]), CHAR_TAN, 3);

		if (strequal( &(str[pos]), "asin" )) condenseFunc( &(str[pos]), CHAR_ASIN, 4);
		if (strequal( &(str[pos]), "acos" )) condenseFunc( &(str[pos]), CHAR_ACOS, 4);
		if (strequal( &(str[pos]), "atan" )) condenseFunc( &(str[pos]), CHAR_ATAN, 4);

		if (strequal( &(str[pos]), "abs" )) condenseFunc( &(str[pos]), CHAR_ABS, 3);

		if (strequal( &(str[pos]), "pi" )) condenseFunc( &(str[pos]), CONST_PI, 2);


		pos++;
	}
}


void expandConstants(char* str)
{
	int pos = 0;

	double value = 0;

	while (str[pos] != 0)
	{
		switch (str[pos])
		{
		case CONST_E: value = CONST_E_VALUE; break;
		case CONST_PI: value = CONST_PI_VALUE; break;		
		}

		if (value != 0)
		{
			
			str[pos] = ' ';	
			char temp[10000];
			sprintf(temp,"%s", &(str[pos+1]));
			
			if (str[pos+1] >= '0' && str[pos+1] <= '9') injectChar( &(str[pos+1]), CHAR_MULTIPLICATION);

			if (pos > 0 && str[pos-1] > '0' && str[pos-1] < '9') 
				sprintf( &(str[pos]), "%c%f%s", CHAR_MULTIPLICATION, value, temp );
			else
				sprintf( &(str[pos]), "%f%s", value, temp );
			
			value = 0;
		}
	
		pos++;
	}
}

void findNegates(char* str)
{
	int pos = 1;

	if (str[0] == CHAR_SUBTRACTION) str[0] = CHAR_NEG;

	while (str[pos] != 0)
	{
		if (str[pos] == CHAR_SUBTRACTION)
		{
			int neg = 1;

			if ( !isValue(str[pos-1]) ) str[pos] = CHAR_NEG;
		}
		pos++;
	}
}


void fixDecimals(char* str)
{
	int pos = 0;

	while (str[pos] != 0)
	{
		if (str[pos] == '.')
		{
			if (pos == 0 || ((str[pos-1] >= '9' || str[pos-1] <= '0') && str[pos-1] != '.'))
			{
				char temp[10000];
				sprintf(temp,"%s", &(str[pos]));
				sprintf(&(str[pos]), "0%s", temp);
				pos++;
			}
		}
		pos++;
	}
}

void fixImplicitMultiplication(char* str)
{
	int pos = 0;
	
	while (str[pos] != 0)
	{
		char ch = str[pos];
		char ch2 = str[pos+1];

		if (ch == ')' || ch == CHAR_XVAR || ch == CHAR_YVAR || (ch >= '0' && ch <= '9') || ch == CONST_I )
			switch (ch2)
			{

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			
				if (ch >= '0' && ch <= '9') break;
				
			case '(':
			case CHAR_LOG:
			case CHAR_LN:
			case CHAR_SIN:
			case CHAR_COS:
			case CHAR_TAN:
			case CHAR_ATAN:
			case CHAR_ASIN:
			case CHAR_ACOS:
			case CHAR_ABS:
			case CHAR_NEG:
			case CHAR_XVAR:
			case CHAR_YVAR:

				injectChar( &(str[pos+1]), CHAR_MULTIPLICATION );
			
			}
		
		pos++;
	}
}

void expandIConstant(char* str)
{
	int pos = 0;
	
	while (str[pos] != 0)
	{
		char ch = str[pos];

		if (ch == CONST_I)
		{
			if (pos > 0)
			{
				char chb = str[pos-1];
				if (isValue(chb)) 
				{
					injectChar(&(str[pos]), CHAR_MULTIPLICATION);
					pos++;
				}
			}

			char cha = str[pos+1];
	
			if (isValue(cha) && cha != ')') 
			{
				injectChar(&(str[pos+1]), CHAR_MULTIPLICATION);
			}
		
		}

		pos++;
	}
}

void cleanEquation(char* str)
{
	condenseFunctionNames(str);	
	killWhiteSpace(str);
	expandConstants(str);
	fixDecimals(str);
	findNegates(str);
	fixImplicitMultiplication(str);
	expandIConstant(str);
}

int checkParens(char* str)
{
	int total = 0;

	int pos = 0;

	while (str[pos] != 0)
	{
		if (str[pos] == '(') total++;
		if (str[pos] == ')') 
		{
			total--;
			if (pos == 0 || str[pos-1] == '(') return 0;
		}

		if (total < 0) return 0;
		
		pos++;
	}

	if (total != 0) return 0;
	return 1;
}

int checkValidOps(char* str)
{
	int pos = 0;

	while (str[pos] != 0)
	{
		if ( isOperator(str[pos]) )
		{
			if (pos == 0) return 0;
			if ( isOperator(str[pos-1]) || isFunction(str[pos-1]) ) return 0;
		}

		if ( isFunction(str[pos]) && str[pos] != '(' )
		{
			if ( (!(isValue(str[pos+1]) || isFunction(str[pos+1])) || str[pos+1] == ')') && str[pos+1] != '(' ) return 0;
		}

		pos++;
	}

	if ( isOperator(str[pos-1]) || isFunction(str[pos-1]) ) return 0;

	return 1;
}

int checkDecimalPoints(char* str)
{
	int pos = 0;

	while (str[pos] != 0)
	{	
		if (str[pos] == '.')
		{
			if (pos == 0) return 0;

			if (str[pos-1] == '.') return 0;
			if (str[pos-1] < '0' || str[pos-1] > '9') return 0;
			if (str[pos+1] < '0' || str[pos+1] > '9') return 0;
		}
		pos++;
	}	

	pos = 0;

	while (str[pos] != 0)
	{
		if (str[pos] == '.')
		{
			int pos2 = pos+1;
			while (str[pos2] >= '0' && str[pos2] <= '9') pos2++;
			if (str[pos2] == '.') return 0;
		}
		pos++;
	}

	return 1;
}

int checkInvalidSymbols(char* str)
{
	int pos = 0;

	while (str[pos] != 0)
	{
		if (!(str[pos] == '.' || isValue(str[pos]) || isOperator(str[pos]) || isFunction(str[pos]))) return 0;

		pos++;
	}

	return 1;
}


int nextToken(char* str, int pos)
{
	if (pos < 0) return -1;

	if ((str[pos] == 'x' || str[pos] == 'y' || str[pos] == CONST_I || isOperator(str[pos]) || isFunction(str[pos])) && str[pos] != '(')
		return pos+1;
	
	if (str[pos] >= '0' && str[pos] <= '9')
	{
		while ((str[pos] >= '0' && str[pos] <= '9') || str[pos] == '.') pos++;
		return pos;
	}

	if (str[pos] == '(')
	{
		pos++;
		int total = 0;
		while (str[pos] != 0)
		{
			if (str[pos] == '(') total++;
			if (str[pos] == ')') total--;
			if (total < 0) return pos+1; 
			pos++;
		}
		return -1;
	}
	return -1;
}

int prevToken(char* str, int pos)
{
	if (pos == 0) return -1;

	pos--;

	if ((str[pos] == 'x' || str[pos] == 'y' || str[pos] == CONST_I || isOperator(str[pos]) || isFunction(str[pos])) && str[pos] != ')') return pos;

	if (str[pos] >= '0' && str[pos] <= '9')
	{
		while (pos >= 0 && (str[pos] >= '0' && str[pos] <= '9') || str[pos] == '.') pos--;
		if (str[pos] < 0) return 0; else return pos+1;
	}

	if (str[pos] == ')')
	{
		pos--;
		int total = 0;
		while (pos >= 0)
		{
			if (str[pos] == ')') total++;
			if (str[pos] == '(') total--;
			if (total < 0) return pos;
			pos--;
		}
		return -1;
	}

	return -1;
}

int recalcEndpos(char* str, int start)
{
	int total = 0;

	while ( str[start] != 0 )
	{
		if (str[start] == '(') total++;
		if (str[start] == ')') total--;

		if (total < 0) return start;

		start++;
	}
	return start;
}

void infuseOrderOfOperations(char* str, int startpos, int endpos)
{
	if (endpos <= startpos) return;

	//printf("%d %d ",startpos,endpos); for (int x = startpos; x < endpos; x++) printf("%c",str[x]); printf("\n");

	int pos = endpos;

	while (pos >= startpos)
	{
		int newpos = prevToken(str,pos);
		if (str[newpos] == '(')	infuseOrderOfOperations(str,newpos+1,pos-1);
		pos = newpos;
	}

	//----------- FUNCTIONS ------------

	endpos = recalcEndpos(str,startpos);

	pos = endpos;

	while (pos >= startpos)
	{
		int prevpos = prevToken(str,pos);
		int nextpos = nextToken(str,pos);

		if ( isFunction(str[prevpos]) && str[prevpos] != '(' )
		{
			injectChar( &(str[nextpos]), ')' );
			injectChar( &(str[prevpos]), '(' );
		}

		pos = prevpos;
	}

	//----------- POWER --------------

	endpos = recalcEndpos(str,startpos);

	pos = startpos;

	while (pos < endpos)
	{
		int prevpos = prevToken(str,pos);
		int nextpos = nextToken(str,pos);

		if ( str[pos] == CHAR_POWER )
		{
			nextpos = nextToken(str,nextpos);
			if ( prevpos == startpos && nextpos == endpos ) return;
			injectChar( &(str[nextpos]), ')' ); 
			injectChar( &(str[prevpos]), '(' );
			endpos += 2;
			nextpos += 2;
		}

		pos = nextpos;
	}

	//----------- MULT/DIV --------------

	endpos = recalcEndpos(str,startpos);

	pos = startpos;

	while (pos < endpos)
	{
		int prevpos = prevToken(str,pos);
		int nextpos = nextToken(str,pos);

		if ( str[pos] == CHAR_MULTIPLICATION || str[pos] == CHAR_DIVISION )
		{
			nextpos = nextToken(str,nextpos);
			if ( prevpos == startpos && nextpos == endpos ) return;
			injectChar( &(str[nextpos]), ')' ); 
			injectChar( &(str[prevpos]), '(' );
			endpos += 2;
			nextpos += 2;
		}

		pos = nextpos;
	}

	//------------- ADD/SUB --------------

	endpos = recalcEndpos(str,startpos);

	pos = startpos;

	while (pos < endpos)
	{
		int prevpos = prevToken(str,pos);
		int nextpos = nextToken(str,pos);

		if ( str[pos] == CHAR_ADDITION || str[pos] == CHAR_SUBTRACTION )
		{
			nextpos = nextToken(str,nextpos);
			if ( prevpos == startpos && nextpos == endpos ) return;
			injectChar( &(str[nextpos]), ')' ); 
			injectChar( &(str[prevpos]), '(' );
			endpos += 2;
			nextpos += 2;
		}

		pos = nextpos;
	}
}