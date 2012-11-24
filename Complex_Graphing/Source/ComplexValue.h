#ifndef __complexvalue_h
#define __complexvalue_h




class ComplexValue
{	
private:

	
public:

	double realpart;
	double imagpart;

	ComplexValue();
	ComplexValue(double r, double i);
	ComplexValue(ComplexValue* cv);
	~ComplexValue();

	double getR();
	double getI();

	double getMag();
	double getArg();

	ComplexValue* Cadd(ComplexValue* cv);
	ComplexValue* Csub(ComplexValue* cv);
	ComplexValue* Cmult(ComplexValue* cv);
	ComplexValue* Cdiv(ComplexValue* cv);

	ComplexValue* Cpow(ComplexValue* cv);

	ComplexValue* Cexp();
	ComplexValue* Clog();

	ComplexValue* Csin();
	ComplexValue* Ccos();
	ComplexValue* Ctan();

	ComplexValue* Casin();
	ComplexValue* Cacos();
	ComplexValue* Catan();


};




#endif