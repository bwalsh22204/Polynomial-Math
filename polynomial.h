
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;


struct Term {

	double coefficient;
	double power;
	
	Term * next;

};


class Polynomial {

	private:
		Term * first;
		Term * current;
		unsigned int size;
		
		Term * createTerm(double, double);
		Term * createTerm(string);
	
	public:
		Polynomial();
		Polynomial(Polynomial &);
		Polynomial(istream &);
		Polynomial(double, double);
		~Polynomial();
		
		Polynomial & operator=(Polynomial &);
		Polynomial & operator+(Polynomial &);
		Polynomial & operator-(Polynomial &);
		Polynomial & operator*(Polynomial &);
		int getSize();
		void print();
		double evaluate(double);
		Polynomial & exponent(int);
		Polynomial & modulus(Polynomial &);
		
		void resetCurrent();
		bool advanceCurrent();
		double getCurrentPower();
		double getCurrentCoefficient();
		
		void addTerm(double, double);

};


#endif
