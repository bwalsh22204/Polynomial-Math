
#include "polynomial.h"

using namespace std;


Polynomial::Polynomial() {

	current = first = 0;
	size = 0;

}

Polynomial::Polynomial(Polynomial & old) {
	
	* this = old;

}

Polynomial::Polynomial(istream & in) {

	current = first = 0;
	size = 0;
	
	string input;
	getline(in, input);
	input.replace(remove(input.begin(), input.end(), ' '), input.end(), "");
	
	string temp = "";
	size_t plusPos = input.find('+');
	
	while (plusPos != string::npos) {
	
		temp = input.substr(0, plusPos);
		input = input.substr(plusPos + 1);
		plusPos = input.find('+');
	
		if (getSize() == 0)
			current = first = createTerm(temp);
		
		else {
		
			current->next = createTerm(temp);
			advanceCurrent();
		
		}
		
		size++;
	
	}
	
	if (input != "") {
	
		if (getSize() == 0)
			current = first = createTerm(input);
		
		else {
		
			current->next = createTerm(input);
			current = current->next;
		
		}
		
		size++;
	
	}

}

Polynomial::Polynomial(double coefficient, double power) {

	current = first = 0;
	size = 0;
	
	addTerm(coefficient, power);

}

Polynomial::~Polynomial() {

	if (getSize() > 0) {
	
		current = first;
		
		while (current->next != 0) {
		
			first = current->next;
			delete current;
			current = first;
		
		}
		
		delete current;
		
		size = 0;
	
	}

}

Polynomial & Polynomial::operator=(Polynomial & old) {

	current = first = 0;
	size = 0;
	
	if (old.getSize() > 0) {
	
		old.resetCurrent();
		
		current = first = createTerm(
			old.getCurrentCoefficient(),
			old.getCurrentPower()
		);
		size++;
		
		while (old.advanceCurrent()) {
		
			current->next = createTerm(
				old.getCurrentCoefficient(),
				old.getCurrentPower()
			);
			current = current->next;
			
			size++;
		
		}
	
	}
	
	return * this;

}

Polynomial & Polynomial::operator+(Polynomial & input) {

	Polynomial * newPoly;
	
	if ((getSize() == 0) && (input.getSize() == 0))
		newPoly = 0;
	
	else if (getSize() == 0)
		newPoly = new Polynomial(input);
	
	else if (input.getSize() == 0)
		newPoly = new Polynomial(* this);
	
	else {
	
		newPoly = new Polynomial();
	
		bool advanceThis = true;
		bool advanceThat = true;
		
		resetCurrent();
		input.resetCurrent();
		
		while (
			(
				(
					(getCurrentCoefficient() != 0)
					&& advanceThat
				)
				|| (
					(input.getCurrentCoefficient() != 0)
					&& advanceThis
				)
			)
		) {
		
			double newCoefficient = 0;
			double newPower = -1;
			
			if (
				(getCurrentPower() > input.getCurrentPower())
				&& advanceThis
			) {
			
				newCoefficient = getCurrentCoefficient();
				newPower = getCurrentPower();
				advanceThis = advanceCurrent();
			
			}
			
			else if (
				(getCurrentPower() == input.getCurrentPower())
				&& advanceThis
				&& advanceThat
			) {
			
				newCoefficient = 
					getCurrentCoefficient() + input.getCurrentCoefficient();
				newPower = getCurrentPower();
				advanceThis = advanceCurrent();
				advanceThat = input.advanceCurrent();
			
			}
			
			else {
			
				newCoefficient = input.getCurrentCoefficient();
				newPower = input.getCurrentPower();
				advanceThat = input.advanceCurrent();
			
			}
			
			if (newCoefficient != 0)
				newPoly->addTerm(newCoefficient, newPower);
		
		}
	
	}
	
	return * newPoly;

}

Polynomial & Polynomial::operator-(Polynomial & input) {

	Polynomial * newPoly;
	
	if ((getSize() == 0) && (input.getSize() == 0))
		newPoly = 0;
	
	else if (getSize() == 0) {
	
		Polynomial * negative = new Polynomial(-1, 0);
		newPoly = &(input * (* negative));
		
		delete negative;
	
	}
	
	else if (input.getSize() == 0)
		newPoly = new Polynomial(* this);
	
	else {
	
		newPoly = new Polynomial();
	
		bool advanceThis = true;
		bool advanceThat = true;
		
		resetCurrent();
		input.resetCurrent();
		
		while (
			(
				(
					(getCurrentCoefficient() != 0)
					&& advanceThat
				)
				|| (
					(input.getCurrentCoefficient() != 0)
					&& advanceThis
				)
			)
		) {
		
			double newCoefficient = 0;
			double newPower = -1;
			
			if (
				(getCurrentPower() > input.getCurrentPower())
				&& advanceThis
			) {
			
				newCoefficient = getCurrentCoefficient();
				newPower = getCurrentPower();
				advanceThis = advanceCurrent();
			
			}
			
			else if (
				(getCurrentPower() == input.getCurrentPower())
				&& advanceThis
				&& advanceThat
			) {
			
				newCoefficient = 
					getCurrentCoefficient() - input.getCurrentCoefficient();
				newPower = getCurrentPower();
				advanceThis = advanceCurrent();
				advanceThat = input.advanceCurrent();
			
			}
			
			else if (
				(getCurrentPower() < input.getCurrentPower())
				&& advanceThat
			) {
			
				newCoefficient = input.getCurrentCoefficient() * -1;
				newPower = input.getCurrentPower();
				advanceThat = input.advanceCurrent();
			
			}
			
			else if (advanceThis && !advanceThat) {
			
				newCoefficient = getCurrentCoefficient();
				newPower = getCurrentPower();
				advanceThis = advanceCurrent();
			
			}
			
			else if (advanceThat && !advanceThis) {
			
				newCoefficient = input.getCurrentCoefficient() * -1;
				newPower = input.getCurrentPower();
				advanceThat = input.advanceCurrent();
			
			}
			
			if (newCoefficient != 0)
				newPoly->addTerm(newCoefficient, newPower);
		
		}
	
	}
	
	return * newPoly;

}

Polynomial & Polynomial::operator*(Polynomial & input) {

	Polynomial * newPoly;

	if ((getSize() > 0) && (input.getSize() > 0)) {
	
		newPoly = new Polynomial();
		
		resetCurrent();
		
		do {
		
			Polynomial * thisPoly = new Polynomial();
			
			input.resetCurrent();
			
			do {
				
				double newCoefficient =
					getCurrentCoefficient() * input.getCurrentCoefficient();
				double newPower = getCurrentPower() + input.getCurrentPower();
				
				if (newCoefficient != 0)
					thisPoly->addTerm(newCoefficient, newPower);
			
			} while (input.advanceCurrent());
			
			Polynomial * tempPoly = newPoly;
			newPoly = &((* tempPoly) + (* thisPoly));
			
			delete tempPoly;
			delete thisPoly;
			
		} while (advanceCurrent());
	
	}
	
	else
		newPoly = 0;
	
	return * newPoly;

}

int Polynomial::getSize() {

	return size;

}

void Polynomial::print() {

	if (getSize() > 0) {
	
		resetCurrent();
		
		do {
		
			if (getCurrentCoefficient() != 0) {
						
				if (current != first)
					cout << " + ";
				
				if (
					(getCurrentCoefficient() > 1)
					|| (getCurrentCoefficient() < -1)
					|| (getCurrentPower() < 1)
				)
					cout << getCurrentCoefficient();
				
				else if (getCurrentCoefficient() == -1)
					cout << "-";
				
				if (getCurrentPower() != 0) {
					
					cout << "x";
					
					if (getCurrentPower() > 1)
						cout << "^" << getCurrentPower();
				
				}
			
			}
		
		} while  (advanceCurrent());
		
		cout << endl;
	
	}
	
	else
		cout << 0 << endl;

}

double Polynomial::evaluate(double x) {

	if (getSize() > 0) {
	
		resetCurrent();
		
		double result = getCurrentCoefficient()
			* ((getCurrentPower() != -1) ? pow(x, getCurrentPower()) : 1);
		
		while (advanceCurrent())
			result += getCurrentCoefficient()
				* ((getCurrentPower() != -1) ? pow(x, getCurrentPower()) : 1);
		
		return result;
	
	}
	
	else
		return -1;

}

Polynomial & Polynomial::exponent(int n) {

	Polynomial * newPoly = new Polynomial(* this);
	
	if (n > 1) {
		
		while (n > 1) {
			
			Polynomial * tempPoly = newPoly;
			newPoly = &((* this) * (* tempPoly));
			
			delete tempPoly;
			
			n--;
		
		}
	
	}
	
	return * newPoly;

}

Polynomial & Polynomial::modulus(Polynomial & input) {

	Polynomial * remainder;
	
	input.resetCurrent();
	
	if (
		(input.getSize() == 0)
		|| (input.getCurrentCoefficient() != 1)
	)
		remainder = 0;
	
	else if (getSize() == 0)
		remainder = new Polynomial(input);
	
	else {
	
		remainder = this;
		Polynomial * dividend;
		Polynomial * divisor = &input;
		Polynomial * quotient = new Polynomial();
		
		divisor->resetCurrent();
		remainder->resetCurrent();
		
		while (remainder->getCurrentPower() >= divisor->getCurrentPower()) {
			
			dividend = remainder;
			
			quotient->addTerm(
				remainder->getCurrentCoefficient() 
					/ divisor->getCurrentCoefficient(),
				remainder->getCurrentPower() - divisor->getCurrentPower()
			);
			
			Polynomial * tempTerm = new Polynomial(
				quotient->getCurrentCoefficient(),
				quotient->getCurrentPower()
			);
			Polynomial * tempProduct = &((* tempTerm) * (* divisor));
			
			remainder = &((* dividend) - (* tempProduct));
			
			divisor->resetCurrent();
			remainder->resetCurrent();
			
			delete tempTerm;
			delete tempProduct;
			if (dividend != this)
				delete dividend;
		
		}
		
		delete quotient;
	
	}
	
	return * remainder;

}

void Polynomial::resetCurrent() {

	current = first;

}

bool Polynomial::advanceCurrent() {

	if (current->next != 0) {
	
		current = current->next;
		return true;
	
	}
	
	else
		return false;

}

double Polynomial::getCurrentPower() {

	if (current != 0)
		return current->power;
	
	else
		return -1;

}

double Polynomial::getCurrentCoefficient() {

	if (current != 0)
		return current->coefficient;
	
	else
		return 0;

}

void Polynomial::addTerm(double coefficient, double power) {

	Term * newTerm = createTerm(coefficient, power);
	
	if (newTerm != 0) {
	
		if (getSize() <= 0) {
		
			size = 0;
			current = first = newTerm;
		
		}
		
		else if (current != 0) {
		
			current->next = newTerm;
			advanceCurrent();
		
		}
			
		else
			exit(1);
		
		size++;
	
	}
	
	else 
		exit(1);

}

Term * Polynomial::createTerm(double coefficient, double power) {

	Term * newTerm = new Term;
	
	if (coefficient != 0) {
		
		newTerm->power = power;
		newTerm->coefficient = coefficient;
		newTerm->next = 0;
	
	}
	
	else
		newTerm = 0;
	
	return newTerm;

}

// parse string input for use with createTerm(double, double)
Term * Polynomial::createTerm(string temp) {

	size_t xPos = temp.find('x');
	
	double coefficient;
	double power;
	
	
	if (xPos != string::npos) {
		
		if (xPos != 0)
			coefficient = atof(temp.substr(0, xPos).c_str());
		
		else
			coefficient = 1;
		
		temp = temp.substr(xPos + 1);
		
		size_t powPos = temp.find('^');
		string powerString = (powPos != string::npos)
			? temp.substr(powPos + 1).c_str()
			: temp.c_str();
		power = (powerString != "")
			? atof(powerString.c_str())
			: 1.00;
	
	}
	
	else {
	
		power = 0;
		coefficient = atof(temp.c_str());
	
	}
	
	return createTerm(coefficient, power);

}
