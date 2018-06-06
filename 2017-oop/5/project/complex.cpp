//404410033 資工二 黃郁儒
#include <iostream>
#include <cstdlib>
#include "complex.h"
namespace complexHuang{
	using std::ostream;
	using std::cout;
	using std::endl;
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
		if(complexB.realPart==Rational(0)&&complexB.imaginaryPart==Rational(0)){
			cout << "denominator should not be zero." << endl;
			     exit(-1);
		}
		Complex result((a*c+b*d)/(c*c+d*d), (b*c-a*d)/(c*c+d*d));
		return result;
	}
	ostream& operator << (ostream& outs, const Complex& complexOuts){
		if(complexOuts.realPart<Rational(0)||complexOuts.realPart>Rational(0)){
			outs << complexOuts.realPart;
			if(complexOuts.imaginaryPart<Rational(0))
				outs << complexOuts.imaginaryPart << 'i';
			else if(complexOuts.imaginaryPart>Rational(0)){
				outs << '+';
				outs << complexOuts.imaginaryPart << 'i';
			}
		}
		else{
			if(complexOuts.imaginaryPart<Rational(0))
				outs << complexOuts.imaginaryPart << 'i';
			else if(complexOuts.imaginaryPart>Rational(0)){
				outs << complexOuts.imaginaryPart << 'i';
			}
		}
		if(complexOuts.realPart==Rational(0)&&complexOuts.imaginaryPart==Rational(0))
			outs << '0';
		return outs;
	} 
}
