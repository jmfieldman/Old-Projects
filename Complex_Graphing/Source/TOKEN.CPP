#include "token.h"
#include "equation.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


Token::Token()
{
	type = 0;
	value = 0;
	op1 = NULL;
	op2 = NULL;
}

Token::~Token()
{
	if (op1 != NULL) delete op1;
	if (op2 != NULL) delete op2;
}

void Token::setValue(double v)
{
	value = v;
}

void Token::setType(int t)
{
	type = t;
}

void Token::setOperands(Token* o1, Token* o2)
{
	op1 = o1;
	op2 = o2;
}

int Token::getType()
{
	return type;
}

double Token::getValue()
{
	return value;
}

double Token::evaluate(double xval, double yval)
{
	double val;

	switch (type)
	{
	case CONSTANT:

		return value;

	case XVAR:

		return xval;

	case YVAR:

		return yval;

	case ADDITION:

		return (op1->evaluate(xval,yval) + op2->evaluate(xval,yval));

	case SUBTRACTION:

		return (op1->evaluate(xval,yval) - op2->evaluate(xval,yval));

	case MULTIPLICATION:

		return (op1->evaluate(xval,yval) * op2->evaluate(xval,yval));

	case DIVISION:

		return (op1->evaluate(xval,yval) / op2->evaluate(xval,yval));

	case POWER:

		return pow(op1->evaluate(xval,yval),op2->evaluate(xval,yval));

	case LOG:

		return (log(op1->evaluate(xval,yval)) / log(10));

	case LN:

		return log(op1->evaluate(xval,yval));

	case SIN:

		return sin(op1->evaluate(xval,yval));

	case COS:

		return cos(op1->evaluate(xval,yval));

	case TAN:

		return (sin(op1->evaluate(xval,yval)) / cos(op1->evaluate(xval,yval)));

	case ASIN:

		return asin(op1->evaluate(xval,yval));

	case ACOS:

		return acos(op1->evaluate(xval,yval));

	case ATAN:

		return atan(op1->evaluate(xval,yval));

	case ABS:

		val = op1->evaluate(xval,yval);
		if (val < 0) return (val * -1);
		return val;

	case NEG:

		return ( -1 * op1->evaluate(xval,yval) );


	case PASS_THROUGH:

		return op1->evaluate(xval,yval);
	}
	
	return value;
}

int Token::checkFunction(double xval, double yval)
{
	switch (type)
	{
	case DIVISION:

		if ( !op1->checkFunction(xval,yval) || !op2->checkFunction(xval,yval) )
			return 0;
		else
			if (op2->evaluate(xval,yval) == 0.0) return 0;

	case POWER:

		
		break;

	}

	return 1;
}



Token* buildTokenFromString(char* str)
{
	Token* token = new Token();

	// ------------ () xxxxxx -----------

	if (str[0] == '(')
	{
		int next = nextToken(str,0);
		// ------- () ---------
		if ( str[next] == 0 || str[next] == ')' ) return buildTokenFromString( &(str[1]) ); 
		else
		// -------- () op xxxx ---------
		{
			token = buildTokenFromString( &(str[1]) );

			int third = nextToken(str,next);
			Token* mastertoken = new Token();
			Token* secondtoken = new Token();

			switch (str[next])
			{
			case CHAR_ADDITION:			mastertoken->setType(ADDITION); break;
			case CHAR_SUBTRACTION:		mastertoken->setType(SUBTRACTION); break;
			case CHAR_MULTIPLICATION:	mastertoken->setType(MULTIPLICATION); break;
			case CHAR_DIVISION:			mastertoken->setType(DIVISION); break;
			case CHAR_POWER:			mastertoken->setType(POWER); break;
			}
			
			if ( isValue(str[third]) )
			{				
				if      (str[third] == 'x') secondtoken->setType(XVAR);
				else if (str[third] == 'y') secondtoken->setType(YVAR);
				else if (str[0] == CONST_I) { secondtoken->setType(CONSTANT); secondtoken->setValue(1); }
				else
				{
					secondtoken->setType(CONSTANT);
					float val2;  sscanf(&(str[third]),"%f",&val2);
					secondtoken->setValue((double)val2);
				}

				mastertoken->setOperands(token,secondtoken);
				return mastertoken;
			}
			else // ------ () op () ------------
			{
				secondtoken = buildTokenFromString( &(str[third]) );
				mastertoken->setOperands(token,secondtoken);
				return mastertoken;
			}
 
		}
	}
	


	// ------ value xxxx --------

	
	if ( isValue(str[0]) )
	{
		int next = nextToken(str,0);

		// ----------- value ------------
	
		if      (str[0] == 'x') token->setType(XVAR);
		else if (str[0] == 'y') token->setType(YVAR);
		else if (str[0] == CONST_I) { token->setType(CONSTANT); token->setValue(1); }
		else
		{
			token->setType(CONSTANT);
			float val;  sscanf(str,"%f",&val);
			token->setValue((double)val);
		}

		if ( str[next] == ')' || str[next] == 0)
		{
			return token;			
		}
		else  // ------------ [value op value] or [value op ()] ---------
		{
			int third = nextToken(str,next);
			Token* mastertoken = new Token();
			Token* secondtoken = new Token();

			switch (str[next])
			{
			case CHAR_ADDITION:			mastertoken->setType(ADDITION); break;
			case CHAR_SUBTRACTION:		mastertoken->setType(SUBTRACTION); break;
			case CHAR_MULTIPLICATION:	mastertoken->setType(MULTIPLICATION); break;
			case CHAR_DIVISION:			mastertoken->setType(DIVISION); break;
			case CHAR_POWER:			mastertoken->setType(POWER); break;
			}

			

			// ------------- value op value ------------
			if ( isValue(str[third]) )
			{
				if      (str[third] == 'x') secondtoken->setType(XVAR);
				else if (str[third] == 'y') secondtoken->setType(YVAR);
				else if (str[third] == CONST_I) { secondtoken->setType(CONSTANT); secondtoken->setValue(1); }
				else
				{
					secondtoken->setType(CONSTANT);
					float val2;  sscanf(&(str[third]),"%f",&val2);
					secondtoken->setValue((double)val2);
				}

				mastertoken->setOperands(token,secondtoken);
				return mastertoken;
			}
			else // ------ value op () ------------
			{
				secondtoken = buildTokenFromString( &(str[third]) );
				mastertoken->setOperands(token,secondtoken);
				return mastertoken;
			}

		}
	}

 	if ( isFunction(str[0]) && str[0] != '(' )
	{
		switch (str[0])
		{
		case CHAR_SIN:			token->setType(SIN); break;
		case CHAR_COS:			token->setType(COS); break;
		case CHAR_TAN:			token->setType(TAN); break;
		case CHAR_ASIN:			token->setType(ASIN); break;
		case CHAR_ACOS:			token->setType(ACOS); break;
		case CHAR_ATAN:			token->setType(ATAN); break;
		case CHAR_LN:			token->setType(LN); break;
		case CHAR_LOG:			token->setType(LOG); break;
		case CHAR_NEG:			token->setType(NEG); break;
		case CHAR_ABS:			token->setType(ABS); break;
		}

		Token* arg = buildTokenFromString( &(str[nextToken(str,0)]) );
		token->setOperands(arg,NULL);
	}

	return token;
}