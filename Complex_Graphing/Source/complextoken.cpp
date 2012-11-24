#include "complextoken.h"
#include "equation.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


ComplexToken::ComplexToken()
{
	type = 0;
	value = 0;
	op1 = NULL;
	op2 = NULL;
	value = NULL;
}

ComplexToken::~ComplexToken()
{
	if (op1 != NULL) delete op1;
	if (op2 != NULL) delete op2;
	if (value != NULL) delete value;
}

void ComplexToken::setValue(ComplexValue* v)
{
	value = v;
}

void ComplexToken::setType(int t)
{
	type = t;
}

void ComplexToken::setOperands(ComplexToken* o1, ComplexToken* o2)
{
	op1 = o1;
	op2 = o2;
}

int ComplexToken::getType()
{
	return type;
}

ComplexValue* ComplexToken::getValue()
{
	return value;
}

ComplexValue* ComplexToken::evaluate(ComplexValue* cv)
{

	switch (type)
	{
	case CONSTANT:

		return new ComplexValue(value);

	case XVAR:

		return new ComplexValue(cv);

	case YVAR:

		return new ComplexValue(cv);

	case ADDITION:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			ComplexValue* o2 = op2->evaluate(cv);

			ComplexValue* final = o1->Cadd(o2);

			delete o1;
			delete o2;

			return final;
		}		

	case SUBTRACTION:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			ComplexValue* o2 = op2->evaluate(cv);

			ComplexValue* final = o1->Csub(o2);

			delete o1;
			delete o2;

			return final;
		}

	case MULTIPLICATION:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			ComplexValue* o2 = op2->evaluate(cv);

			ComplexValue* final = o1->Cmult(o2);

			delete o1;
			delete o2;

			return final;
		}

	case DIVISION:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			ComplexValue* o2 = op2->evaluate(cv);

			ComplexValue* final = o1->Cdiv(o2);

			delete o1;
			delete o2;

			return final;
		}

	case POWER:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			ComplexValue* o2 = op2->evaluate(cv);

			ComplexValue* final = o1->Cpow(o2);

			delete o1;
			delete o2;

			return final;
		}

	case LOG:
	case LN:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			
			ComplexValue* final = o1->Clog();

			delete o1;
			
			return final;
		}

	
	case SIN:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			
			ComplexValue* final = o1->Csin();

			delete o1;
			
			return final;
		}


	case COS:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			
			ComplexValue* final = o1->Ccos();

			delete o1;
			
			return final;
		}


	case TAN:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			
			ComplexValue* final = o1->Ctan();

			delete o1;
			
			return final;
		}

	case ASIN:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			
			ComplexValue* final = o1->Casin();

			delete o1;
			
			return final;
		}


	case ACOS:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			
			ComplexValue* final = o1->Cacos();

			delete o1;
			
			return final;
		}


	case ATAN:

		{
			ComplexValue* o1 = op1->evaluate(cv);
			
			ComplexValue* final = o1->Catan();

			delete o1;
			
			return final;
		}


	case ABS:

		return cv;

	case NEG:

		{
			ComplexValue negone(-1,0);
			ComplexValue* o1 = op1->evaluate(cv);
			
			ComplexValue* final = o1->Cmult(&negone);

			delete o1;
			
			return final;
		}



	case PASS_THROUGH:

		return op1->evaluate(cv);
	}
	
	return value;
}

int ComplexToken::checkFunction(ComplexValue* cv)
{
	switch (type)
	{
	case DIVISION:

		if ( !op1->checkFunction(cv) || !op2->checkFunction(cv) )
			return 0;
		else
		{
			ComplexValue* mycv = op2->evaluate(cv);
			if (mycv->getI() == 0 && mycv->getR() == 0) 
			{
				delete mycv;
				return 0;
			}
			delete mycv;
		}

	case POWER:

		
		break;

	}

	return 1;
}



ComplexToken* buildComplexTokenFromString(char* str)
{
	ComplexToken* token = new ComplexToken();

	// ------------ () xxxxxx -----------

	if (str[0] == '(')
	{
		int next = nextToken(str,0);
		// ------- () ---------
		if ( str[next] == 0 || str[next] == ')' ) return buildComplexTokenFromString( &(str[1]) ); 
		else
		// -------- () op xxxx ---------
		{
			token = buildComplexTokenFromString( &(str[1]) );

			int third = nextToken(str,next);
			ComplexToken* mastertoken = new ComplexToken();
			ComplexToken* secondtoken = new ComplexToken();

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
				else if (str[third] == CONST_I) { secondtoken->setType(CONSTANT); secondtoken->setValue(new ComplexValue(0,1)); }
				else
				{
					secondtoken->setType(CONSTANT);
					float val2;  sscanf(&(str[third]),"%f",&val2);
					secondtoken->setValue(new ComplexValue(val2,0));
				}

				mastertoken->setOperands(token,secondtoken);
				return mastertoken;
			}
			else // ------ () op () ------------
			{
				secondtoken = buildComplexTokenFromString( &(str[third]) );
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
		else if (str[0] == CONST_I) { token->setType(CONSTANT); token->setValue(new ComplexValue(0,1)); }
		else
		{
			token->setType(CONSTANT);
			float val;  sscanf(str,"%f",&val);
			token->setValue(new ComplexValue(val,0));
		}

		if ( str[next] == ')' || str[next] == 0)
		{
			return token;			
		}
		else  // ------------ [value op value] or [value op ()] ---------
		{
			int third = nextToken(str,next);
			ComplexToken* mastertoken = new ComplexToken();
			ComplexToken* secondtoken = new ComplexToken();

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
				else if (str[third] == CONST_I) { secondtoken->setType(CONSTANT); secondtoken->setValue(new ComplexValue(0,1)); }
				else
				{
					secondtoken->setType(CONSTANT);
					float val2;  sscanf(&(str[third]),"%f",&val2);
					secondtoken->setValue(new ComplexValue(val2,0));
				}

				mastertoken->setOperands(token,secondtoken);
				return mastertoken;
			}
			else // ------ value op () ------------
			{
				secondtoken = buildComplexTokenFromString( &(str[third]) );
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

		ComplexToken* arg = buildComplexTokenFromString( &(str[nextToken(str,0)]) );
		token->setOperands(arg,NULL);
	}

	return token;
}