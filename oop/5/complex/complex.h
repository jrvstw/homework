#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
#include "rational.h"
namespace complexHuang{
	using namespace rationalJarvis;
	using std::ostream;
	class Complex{
		public:
			Complex();
			//default constructor: set to 0.
			Complex(Rational realValue);
			//if there is only one argument, set it to a real number.
			Complex(Rational realValue, Rational imaginaryValue);
			//set it to A+Bi
			friend const Complex operator / (const Complex &complexA, const Complex &complexB);
			friend ostream& operator << (ostream& outs, const Complex &complexOuts);
		private:
			Rational realPart;
			Rational imaginaryPart;
	};
}
#endif
