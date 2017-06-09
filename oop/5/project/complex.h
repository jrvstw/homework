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
			Complex(Rational realValue);
			Complex(Rational realValue, Rational imaginaryValue);
			friend const Complex operator / (const Complex &complexA, const Complex &complexB);
			friend ostream& operator << (ostream& outs, const Complex &complexOuts);
		private:
			Rational realPart;
			Rational imaginaryPart;
	};
}
#endif
