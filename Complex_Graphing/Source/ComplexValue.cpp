#include <math.h>

#include "ComplexValue.h"

#define PI_VALUE 3.14159265359

ComplexValue::ComplexValue()
{
	realpart = 0;
	imagpart = 0;
}

ComplexValue::ComplexValue(double r, double i)
{
	realpart = r;
	imagpart = i;
}

ComplexValue::ComplexValue(ComplexValue* cv)
{
	realpart = cv->getR();
	imagpart = cv->getI();
}

ComplexValue::~ComplexValue()
{

}


double ComplexValue::getR()
{
	return realpart;
}


double ComplexValue::getI()
{
	return imagpart;
}

double ComplexValue::getMag()
{
	return sqrt( (realpart * realpart) + (imagpart * imagpart) );
}

double ComplexValue::getArg()
{
	if (realpart == 0)
	{
		if (imagpart > 0) return PI_VALUE / 2;
		if (imagpart < 0) return 3 * PI_VALUE / 2;
		return 0;
	}

	double mytan = atan(imagpart / realpart);

	if (realpart < 0) mytan += PI_VALUE;

	return mytan;
}

ComplexValue* ComplexValue::Cadd(ComplexValue* cv)
{
	return new ComplexValue(realpart + cv->realpart, imagpart + cv->imagpart);
}

ComplexValue* ComplexValue::Csub(ComplexValue* cv)
{
	return new ComplexValue(realpart - cv->realpart, imagpart - cv->imagpart);
}

ComplexValue* ComplexValue::Cmult(ComplexValue* cv)
{
	double rp = (realpart * cv->realpart) - (imagpart * cv->imagpart);
	double ip = (imagpart * cv->realpart) + (realpart * cv->imagpart);

	return new ComplexValue(rp,ip);
}

ComplexValue* ComplexValue::Cdiv(ComplexValue* cv)
{
	double rp = (realpart * cv->realpart) + (imagpart * cv->imagpart);
	double ip = (imagpart * cv->realpart) - (realpart * cv->imagpart);
	double sq = (cv->realpart * cv->realpart) + (cv->imagpart * cv->imagpart);

	if (sq == 0) return new ComplexValue(0,0);

	return new ComplexValue(rp/sq,ip/sq);
}

ComplexValue* ComplexValue::Cpow(ComplexValue* cv)
{
	ComplexValue* mylog = Clog();
	ComplexValue* mul = cv->Cmult(mylog);

	ComplexValue* final = mul->Cexp();

	delete mylog;
	delete mul;

	return final;
}

ComplexValue* ComplexValue::Cexp()
{
	double expreal = exp(realpart);
	double cosv = cos(imagpart);
	double sinv = sin(imagpart);

	return new ComplexValue(expreal * cosv, expreal * sinv);
}

ComplexValue* ComplexValue::Clog()
{
	double mag = getMag();

	if (mag == 0) return new ComplexValue(-100000000,0);

	double r = mag;
	double a = getArg();
	
	double myln = log(r);
	
	return new ComplexValue(myln,a);
}

ComplexValue* ComplexValue::Csin()
{
	ComplexValue myi(0,1);
	ComplexValue myin(0,-1);
	ComplexValue my2i(0,2);

	ComplexValue* iz = myi.Cmult(this);
	ComplexValue* niz = myin.Cmult(this);
	ComplexValue* fe = iz->Cexp();
	ComplexValue* se = niz->Cexp();
	ComplexValue* diff = fe->Csub(se);

	ComplexValue* final = diff->Cdiv(&my2i);

	delete iz;
	delete niz;
	delete fe;
	delete se;
	delete diff;

	return final;
}

ComplexValue* ComplexValue::Ccos()
{
	ComplexValue myi(0,1);
	ComplexValue myin(0,-1);
	ComplexValue my2(2,0);

	ComplexValue* iz = myi.Cmult(this);
	ComplexValue* niz = myin.Cmult(this);
	ComplexValue* fe = iz->Cexp();
	ComplexValue* se = niz->Cexp();
	ComplexValue* ad = fe->Cadd(se);

	ComplexValue* final = ad->Cdiv(&my2);

	delete iz;
	delete niz;
	delete fe;
	delete se;
	delete ad;

	return final;
}

ComplexValue* ComplexValue::Ctan()
{
	ComplexValue* mysin = Csin();
	ComplexValue* mycos = Ccos();

	ComplexValue* final = mysin->Cdiv(mycos);

	delete mysin;
	delete mycos;

	return final;
}

ComplexValue* ComplexValue::Casin()
{
	ComplexValue half(0.5,0);
	ComplexValue two(2,0);
	ComplexValue myi(0,1);
	ComplexValue myin(0,-1);
	ComplexValue one(1,0);

	ComplexValue* mesquare = this->Cmult(this);
	ComplexValue* oneminusmesqr = one.Csub(mesquare);
	ComplexValue* quansqrt = oneminusmesqr->Cpow(&half);
	ComplexValue* metimesi = myi.Cmult(this);
	ComplexValue* quanadd = metimesi->Cadd(quansqrt);
	ComplexValue* logall = quanadd->Clog();
	ComplexValue* final = logall->Cmult(&myin);

	delete mesquare;
	delete oneminusmesqr;
	delete quansqrt;
	delete metimesi;
	delete quanadd;
	delete logall;
	
	return final;

}

ComplexValue* ComplexValue::Cacos()
{
	ComplexValue half(0.5,0);
	ComplexValue two(2,0);
	ComplexValue myi(0,1);
	ComplexValue myin(0,-1);
	ComplexValue one(1,0);

	ComplexValue* mesquare = this->Cmult(this);
	ComplexValue* oneminusmesqr = one.Csub(mesquare);
	ComplexValue* quansqrt = oneminusmesqr->Cpow(&half);
	ComplexValue* metimesi = quansqrt->Cmult(&myi);
	ComplexValue* quanadd = this->Cadd(metimesi);
	ComplexValue* logall = quanadd->Clog();
	ComplexValue* final = logall->Cmult(&myin);

	delete mesquare;
	delete oneminusmesqr;
	delete quansqrt;
	delete metimesi;
	delete quanadd;
	delete logall;
	
	return final;

}

ComplexValue* ComplexValue::Catan()
{
	ComplexValue myi(0,1);
	ComplexValue my2(2,0);

	ComplexValue* iover2 = myi.Cdiv(&my2);
	ComplexValue* pl = myi.Cadd(this);
	ComplexValue* mi = myi.Csub(this);
	ComplexValue* quo = pl->Cdiv(mi);
	ComplexValue* lo = quo->Clog();
	ComplexValue* final = iover2->Cmult(lo);

	delete iover2;
	delete pl;
	delete mi;
	delete quo;
	delete lo;

	return final;
}
