/*
		Programming  Assignment 1.                   Due 09 Oct 2008 

1.  Write a C++ program to perform multiplication, addition, subtraction
and evaluation of polynomials USING POINTERS and LINKED LIST implementation.  

Create a polynomial class with the following member functions (you may have
more if you want).

	constructor to initialize zero polynomial.
	constructor to initialize arbitrary polynomial (read input)
	operator+
	operator*
	operator-
	print
	evaluate
	exponent
	modulus

Your implementation should be based on POINTERS and LINKED LIST.  0 points
otherwise.  Also, when storing a polynomial, your linked list should
not contain anything with co-efficient zero.

You develop an interface to test the program.  For instance,
you can create commands such as Create Polynomial,
Add Polynomial, Subtract Polynomial, and Evaluate Polynomial.

In addition to these operators, create member functions to
to perform the following two operations:

Suppose P and Q are two polynomials and n is an integer.

exponentiation operation:  P^n  =  P * P * P * ... n times

modulus operation:   P mod Q

IMPORTANT:  You are not allowed to share codes, copy from any printed
source or internet.  Please see the handout regarding cheating.
We will talk about exponentiation and modulus operation
in the class.


polynomials P and Q
P = x^14 + 5^3 + 7x^2 - 9
Q = x^12 + 15x^11 - 3x^6 + 9
(Q must have first coefficient = 1)
P % Q


*/

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
