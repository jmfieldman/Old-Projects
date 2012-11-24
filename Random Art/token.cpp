#include "token.h"

int maxDepth = 0;

void setMaxDepth(int d)
{
	maxDepth = d;
}

double normalize(ColorValue* cv)
{
	double total = cv->r;
	total += cv->g;
	total += cv->b;

	return (total / (double)3.0);
}

int match(char * st1, char * st2)
{
	int pos = 0;
	while (st1[pos] != 0)
	{
		if (st1[pos] != st2[pos]) return 0;
		pos++;
	}
	if (st2[pos] != 0) return 0;
	return 1;
}

Token* createToken(int depth)
{
	Token* token = NULL;

	int choice = 0;
	if (depth >= maxDepth) 
		choice = rand() % NUM_MAX_DEPTH_TOKENS;
	else
		choice = rand() % NUM_TOKENS;

	if (depth == 0) while (choice < NUM_MAX_DEPTH_TOKENS) { choice = rand() % NUM_TOKENS; }
		
	switch (choice)
	{
	case TOKEN_CONST:       token = new Token_Const(depth); break;
	case TOKEN_X:           token = new Token_X(depth); break;
	case TOKEN_Y:           token = new Token_Y(depth); break;
	case TOKEN_RGB:         token = new Token_RGB(depth); break;
	case TOKEN_IF:          token = new Token_IF(depth); break;
	//case TOKEN_SIN:         token = new Token_SIN(depth); break;
	//case TOKEN_COS:         token = new Token_COS(depth); break;
	case TOKEN_SINRGB:      token = new Token_SINRGB(depth); break;
	case TOKEN_COSRGB:      token = new Token_COSRGB(depth); break;
	case TOKEN_MOD:         token = new Token_MOD(depth); break;
	case TOKEN_MOD2:        token = new Token_MOD2(depth); break;
	case TOKEN_MULT:        token = new Token_MULT(depth); break;
	case TOKEN_EXP:         token = new Token_EXP(depth); break;
	case TOKEN_BLEND:       token = new Token_BLEND(depth); break;
	case TOKEN_PLUS:        token = new Token_PLUS(depth); break;

	}

	return token;
}


Token* createTokenFromFile(FILE* file)
{
	Token* token = NULL;

	char tokenName[1000];
	fscanf(file,"%[^[]",tokenName);
	fscanf(file,"[");
	
	if (match(tokenName,"CONST"))  
	{ 
		token = new Token_Const(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"X"))      
	{ 
		token = new Token_X(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"Y"))      
	{ 
		token = new Token_Y(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"RGB"))    
	{ 
		token = new Token_RGB(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"IF"))     
	{ 
		token = new Token_IF(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"SIN"))    
	{ 
		token = new Token_SIN(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"COS"))    
	{ 
		token = new Token_COS(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"SINRGB")) 
	{ 
		token = new Token_SINRGB(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"COSRGB")) 
	{ 
		token = new Token_COSRGB(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"MOD")) 
	{ 
		token = new Token_MOD(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"MOD2")) 
	{ 
		token = new Token_MOD2(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"MULT")) 
	{ 
		token = new Token_MULT(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"EXP")) 
	{ 
		token = new Token_EXP(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"BLEND")) 
	{ 
		token = new Token_BLEND(maxDepth); 
		token->load(file); 
	}
	else if (match(tokenName,"PLUS")) 
	{ 
		token = new Token_PLUS(maxDepth); 
		token->load(file); 
	}

	return token;
}

// --------------------------- TOKEN ----------------------

Token::Token(int depth)
{

}

Token::~Token()
{

}

ColorValue* Token::getValue(double x, double y)
{
	return NULL;
}

void Token::save(FILE* file)
{
	fprintf(file,"\n\n[ERROR: TRYING TO SAVE A \"TOKEN\"]\n\n");
}

void Token::load(FILE* file)
{
	
}



// --------------------------- TOKEN_CONST ----------------------

Token_Const::Token_Const(int depth) : Token(depth)
{
	double val = ((double)(rand() % 32000) / (double)16000.0) - (double)1.0;

	myValue.r = val;
	myValue.g = val;
	myValue.b = val;
}

Token_Const::~Token_Const()
{

}

ColorValue* Token_Const::getValue(double x, double y)
{
	return &myValue;
}

void Token_Const::save(FILE* file)
{
	fprintf(file,"CONST[%f]",normalize(&myValue));
}

void Token_Const::load(FILE* file)
{
	float val;

	fscanf(file,"%f",&val);
	fscanf(file,"]");

	myValue.r = val;
	myValue.g = val;
	myValue.b = val;
}


// --------------------------- TOKEN_X ----------------------

Token_X::Token_X(int depth) : Token(depth)
{

}

Token_X::~Token_X()
{

}

ColorValue* Token_X::getValue(double x, double y)
{
	myValue.r = x;
	myValue.g = x;
	myValue.b = x;

	return &myValue;
}

void Token_X::save(FILE* file)
{
	fprintf(file,"X[]");
}

void Token_X::load(FILE* file)
{
	fscanf(file,"]");	
}

// --------------------------- TOKEN_Y ----------------------

Token_Y::Token_Y(int depth) : Token(depth)
{

}

Token_Y::~Token_Y()
{

}

ColorValue* Token_Y::getValue(double x, double y)
{
	myValue.r = y;
	myValue.g = y;
	myValue.b = y;

	return &myValue;
}

void Token_Y::save(FILE* file)
{
	fprintf(file,"Y[]");
}

void Token_Y::load(FILE* file)
{
	fscanf(file,"]");	
}


// --------------------------- TOKEN_RGB ----------------------

Token_RGB::Token_RGB(int depth) : Token(depth)
{
	r = createToken(depth+1);
	g = createToken(depth+1);
	b = createToken(depth+1);
}

Token_RGB::~Token_RGB()
{
	delete r;
	delete g;
	delete b;
}

ColorValue* Token_RGB::getValue(double x, double y)
{
	myValue.r = normalize(r->getValue(x,y));
	myValue.g = normalize(g->getValue(x,y));
	myValue.b = normalize(b->getValue(x,y));

	return &myValue;
}

void Token_RGB::save(FILE* file)
{
	fprintf(file,"RGB[");
	r->save(file);
	fprintf(file,",");
	g->save(file);
	fprintf(file,",");
	b->save(file);
	fprintf(file,"]");
}

void Token_RGB::load(FILE* file)
{
	delete r;
	delete g;
	delete b;

	r = createTokenFromFile(file);
	fscanf(file,",");
	g = createTokenFromFile(file);
	fscanf(file,",");
	b = createTokenFromFile(file);
	fscanf(file,"]");
}

// --------------------------- TOKEN_IF ----------------------

Token_IF::Token_IF(int depth) : Token(depth)
{
	pred_val = createToken(depth+1);
	then_val = createToken(depth+1);
	else_val = createToken(depth+1);
}

Token_IF::~Token_IF()
{
	delete pred_val;
	delete then_val;
	delete else_val;
}

ColorValue* Token_IF::getValue(double x, double y)
{
	if (normalize(pred_val->getValue(x,y)) >= 0) return then_val->getValue(x,y);
	
	return else_val->getValue(x,y);
}

void Token_IF::save(FILE* file)
{
	fprintf(file,"IF[");
	pred_val->save(file);
	fprintf(file,",");
	then_val->save(file);
	fprintf(file,",");
	else_val->save(file);
	fprintf(file,"]");
}

void Token_IF::load(FILE* file)
{
	delete pred_val;
	delete then_val;
	delete else_val;

	pred_val = createTokenFromFile(file);
	fscanf(file,",");
	then_val = createTokenFromFile(file);
	fscanf(file,",");
	else_val = createTokenFromFile(file);
	fscanf(file,"]");
}

// --------------------------- TOKEN_SIN ----------------------

Token_SIN::Token_SIN(int depth) : Token(depth)
{
	val = createToken(depth+1);	
}

Token_SIN::~Token_SIN()
{
	delete val;	
}

ColorValue* Token_SIN::getValue(double x, double y)
{
	double dval = normalize(val->getValue(x,y));
	dval = sin(M_PI*dval);
	
	myValue.r = dval;
	myValue.g = dval;
	myValue.b = dval;

	return &myValue;
}

void Token_SIN::save(FILE* file)
{
	fprintf(file,"SIN[");
	val->save(file);
	fprintf(file,"]");
}

void Token_SIN::load(FILE* file)
{
	delete val;

	val = createTokenFromFile(file);
	fscanf(file,"]");
}

// --------------------------- TOKEN_COS ----------------------

Token_COS::Token_COS(int depth) : Token(depth)
{
	val = createToken(depth+1);	
}

Token_COS::~Token_COS()
{
	delete val;	
}

ColorValue* Token_COS::getValue(double x, double y)
{
	double dval = normalize(val->getValue(x,y));
	dval = cos(M_PI*dval);
	
	myValue.r = dval;
	myValue.g = dval;
	myValue.b = dval;

	return &myValue;
}

void Token_COS::save(FILE* file)
{
	fprintf(file,"COS[");
	val->save(file);
	fprintf(file,"]");
}

void Token_COS::load(FILE* file)
{
	delete val;

	val = createTokenFromFile(file);
	fscanf(file,"]");
}

// --------------------------- TOKEN_SINRGB ----------------------

Token_SINRGB::Token_SINRGB(int depth) : Token(depth)
{
	val = createToken(depth+1);	
}

Token_SINRGB::~Token_SINRGB()
{
	delete val;	
}

ColorValue* Token_SINRGB::getValue(double x, double y)
{
	ColorValue* cv = val->getValue(x,y);
	double rval = sin(cv->r * M_PI);
	double gval = sin(cv->g * M_PI);
	double bval = sin(cv->b * M_PI);
	
	myValue.r = rval;
	myValue.g = gval;
	myValue.b = bval;

	return &myValue;
}

void Token_SINRGB::save(FILE* file)
{
	fprintf(file,"SINRGB[");
	val->save(file);
	fprintf(file,"]");
}

void Token_SINRGB::load(FILE* file)
{
	delete val;

	val = createTokenFromFile(file);
	fscanf(file,"]");
}

// --------------------------- TOKEN_COSRGB ----------------------

Token_COSRGB::Token_COSRGB(int depth) : Token(depth)
{
	val = createToken(depth+1);	
}

Token_COSRGB::~Token_COSRGB()
{
	delete val;	
}

ColorValue* Token_COSRGB::getValue(double x, double y)
{
	ColorValue* cv = val->getValue(x,y);
	double rval = cos(cv->r * M_PI);
	double gval = cos(cv->g * M_PI);
	double bval = cos(cv->b * M_PI);
	
	myValue.r = rval;
	myValue.g = gval;
	myValue.b = bval;

	return &myValue;
}

void Token_COSRGB::save(FILE* file)
{
	fprintf(file,"COSRGB[");
	val->save(file);
	fprintf(file,"]");
}

void Token_COSRGB::load(FILE* file)
{
	delete val;

	val = createTokenFromFile(file);
	fscanf(file,"]");
}


// --------------------------- TOKEN_MOD ----------------------

Token_MOD::Token_MOD(int depth) : Token(depth)
{
	val = createToken(depth+1);	
	mod = createToken(depth+1);
}

Token_MOD::~Token_MOD()
{
	delete val;	
	delete mod;
}

ColorValue* Token_MOD::getValue(double x, double y)
{
	ColorValue* cvval = val->getValue(x,y);
	ColorValue* cvmod = mod->getValue(x,y);
	double rval = cvval->r / cvmod->r;
	double gval = cvval->g / cvmod->g;
	double bval = cvval->b / cvmod->b;

	if (rval < 0) rval *= -1;
	if (gval < 0) gval *= -1;
	if (bval < 0) bval *= -1;

	rval -= floor(rval);
	gval -= floor(gval);
	bval -= floor(bval);
	
	myValue.r = rval;
	myValue.g = gval;
	myValue.b = bval;

	return &myValue;
}

void Token_MOD::save(FILE* file)
{
	fprintf(file,"MOD[");
	val->save(file);
	fprintf(file,",");
	mod->save(file);
	fprintf(file,"]");
}

void Token_MOD::load(FILE* file)
{
	delete val;
	delete mod;

	val = createTokenFromFile(file);
	fscanf(file,",");
	mod = createTokenFromFile(file);
	fscanf(file,"]");
}


// --------------------------- TOKEN_MOD2 ----------------------

Token_MOD2::Token_MOD2(int depth) : Token(depth)
{
	val = createToken(depth+1);	
	mod = createToken(depth+1);
}

Token_MOD2::~Token_MOD2()
{
	delete val;	
	delete mod;
}

ColorValue* Token_MOD2::getValue(double x, double y)
{
	ColorValue* cvval = val->getValue(x,y);
	ColorValue* cvmod = mod->getValue(x,y);
	double rval = cvval->r / cvmod->r;
	double gval = cvval->g / cvmod->g;
	double bval = cvval->b / cvmod->b;

	if (rval < 0) rval *= -1;
	if (gval < 0) gval *= -1;
	if (bval < 0) bval *= -1;

	rval -= floor(rval);
	gval -= floor(gval);
	bval -= floor(bval);
	
	myValue.r = (rval*2)-1;
	myValue.g = (gval*2)-1;
	myValue.b = (bval*2)-1;

	return &myValue;
}

void Token_MOD2::save(FILE* file)
{
	fprintf(file,"MOD2[");
	val->save(file);
	fprintf(file,",");
	mod->save(file);
	fprintf(file,"]");
}

void Token_MOD2::load(FILE* file)
{
	delete val;
	delete mod;

	val = createTokenFromFile(file);
	fscanf(file,",");
	mod = createTokenFromFile(file);
	fscanf(file,"]");
}


// --------------------------- TOKEN_MULT ----------------------

Token_MULT::Token_MULT(int depth) : Token(depth)
{
	v1 = createToken(depth+1);	
	v2 = createToken(depth+1);
}

Token_MULT::~Token_MULT()
{
	delete v1;	
	delete v2;
}

ColorValue* Token_MULT::getValue(double x, double y)
{
	ColorValue* cv1 = v1->getValue(x,y);
	ColorValue* cv2 = v2->getValue(x,y);
		
	myValue.r = cv1->r * cv2->r;
	myValue.g = cv1->g * cv2->g;
	myValue.b = cv1->b * cv2->b;

	return &myValue;
}

void Token_MULT::save(FILE* file)
{
	fprintf(file,"MULT[");
	v1->save(file);
	fprintf(file,",");
	v2->save(file);
	fprintf(file,"]");
}

void Token_MULT::load(FILE* file)
{
	delete v1;
	delete v2;

	v1 = createTokenFromFile(file);
	fscanf(file,",");
	v2 = createTokenFromFile(file);
	fscanf(file,"]");
}


// --------------------------- TOKEN_EXP ----------------------

Token_EXP::Token_EXP(int depth) : Token(depth)
{
	val = createToken(depth+1);		
}

Token_EXP::~Token_EXP()
{
	delete val;		
}

ColorValue* Token_EXP::getValue(double x, double y)
{
	ColorValue* cv = val->getValue(x,y);
		
	myValue.r = exp(cv->r) / M_E;
	myValue.g = exp(cv->g) / M_E;
	myValue.b = exp(cv->b) / M_E;

	return &myValue;
}

void Token_EXP::save(FILE* file)
{
	fprintf(file,"EXP[");
	val->save(file);
	fprintf(file,"]");
}

void Token_EXP::load(FILE* file)
{
	delete val;

	val = createTokenFromFile(file);
	fscanf(file,"]");
}

// --------------------------- TOKEN_BLEND ----------------------

Token_BLEND::Token_BLEND(int depth) : Token(depth)
{
	val1 = createToken(depth+1);	
	val2 = createToken(depth+1);	
	ratio = createToken(depth+1);	
}

Token_BLEND::~Token_BLEND()
{
	delete val1;	
	delete val2;	
	delete ratio;
}

ColorValue* Token_BLEND::getValue(double x, double y)
{
	ColorValue* c1 = val1->getValue(x,y);
	ColorValue* c2 = val2->getValue(x,y);
	double ratiov = normalize(ratio->getValue(x,y));
	ratiov /= 2.0;
	ratiov += 0.5;
	double ratiov2 = 1.0 - ratiov;

	myValue.r = (c1->r * ratiov) + (c2->r * ratiov2);
	myValue.g = (c1->g * ratiov) + (c2->g * ratiov2);
	myValue.b = (c1->b * ratiov) + (c2->b * ratiov2);

	return &myValue;
}

void Token_BLEND::save(FILE* file)
{
	fprintf(file,"BLEND[");
	val1->save(file);
	fprintf(file,",");
	val2->save(file);
	fprintf(file,",");
	ratio->save(file);
	fprintf(file,"]");
}

void Token_BLEND::load(FILE* file)
{
	delete val1;
	delete val2;
	delete ratio;

	val1 = createTokenFromFile(file);
	fscanf(file,",");
	val2 = createTokenFromFile(file);
	fscanf(file,",");
	ratio = createTokenFromFile(file);
	fscanf(file,"]");
}


// --------------------------- TOKEN_PLUS ----------------------

Token_PLUS::Token_PLUS(int depth) : Token(depth)
{
	v1 = createToken(depth+1);	
	v2 = createToken(depth+1);
}

Token_PLUS::~Token_PLUS()
{
	delete v1;	
	delete v2;
}

ColorValue* Token_PLUS::getValue(double x, double y)
{
	ColorValue* cv1 = v1->getValue(x,y);
	ColorValue* cv2 = v2->getValue(x,y);
		
	myValue.r = cv1->r + cv2->r;
	myValue.g = cv1->g + cv2->g;
	myValue.b = cv1->b + cv2->b;

	if (myValue.r > 1) myValue.r = 1;
	if (myValue.g > 1) myValue.g = 1;
	if (myValue.b > 1) myValue.b = 1;
	if (myValue.r < -1) myValue.r = -1;
	if (myValue.g < -1) myValue.g = -1;
	if (myValue.b < -1) myValue.b = -1;

	return &myValue;
}

void Token_PLUS::save(FILE* file)
{
	fprintf(file,"PLUS[");
	v1->save(file);
	fprintf(file,",");
	v2->save(file);
	fprintf(file,"]");
}

void Token_PLUS::load(FILE* file)
{
	delete v1;
	delete v2;

	v1 = createTokenFromFile(file);
	fscanf(file,",");
	v2 = createTokenFromFile(file);
	fscanf(file,"]");
}


