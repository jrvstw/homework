#include <iostream>
#include "complex.h"
namespace complexHuang{
	using std::ostream;
	using namespace rationalJarvis;
	#define a complexA.realPart
	#define b complexA.imaginaryPart
	#define c complexB.realPart
	#define d complexB.imaginaryPart
	Complex::Complex():realPart(0), imaginaryPart(0){
	}
	Complex::Complex(Rational realValue):realPart(realValue), imaginaryPart(0){
	}
	Complex::Complex(Rational realValue, Rational imaginaryValue):realPart(realValue), imaginaryPart(imaginaryValue){
	}
	const Complex operator / (const Complex &complexA, const Complex &complexB){
		Complex result((a*c+b*d)/(c*c+d*d), (b*c-a*d)/(c*c+d*d));
		return result;
	}
	ostream& operator << (ostream& outs, const Complex& complexOuts){
		if(complexOuts.realPart<0||complexOuts.realPart>0){
			outs << complexOuts.realPart;
			if(complexOuts.imaginaryPart<0)
				outs << complexOuts.imaginaryPart << 'i';
			else if(complexOuts.imaginaryPart>0){
				outs << '+';
				outs << complexOuts.imaginaryPart << 'i';
			}
		}
		else{
			if(complexOuts.imaginaryPart<0)
				outs << complexOuts.imaginaryPart << 'i';
			else if(complexOuts.imaginaryPart>0){
				outs << complexOuts.imaginaryPart << 'i';
			}
		}
		return outs;
	} 
}
