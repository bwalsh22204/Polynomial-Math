#include "polynomial.h"


using namespace std;

int main() {
	
	int operation;
	
	cout << "Howdy!" << endl;
	
	cout << "(1) Addition" << endl;
	cout << "(2) Subtraction" << endl;
	cout << "(3) Multiplication" << endl;
	cout << "(4) Modulus" << endl;
	cout << "(5) Exponent" << endl;
	cout << "(6) Evaluate" << endl;
	
	cout << "Operation: ";
	
	cin >> operation;
	
	string buffer;
	getline(cin, buffer);
	
	cout << "Sample Input: 4x^2 + -8x + 3" << endl;
	
	switch (operation) {
	
		case 1: {
		
			cout << "Polynomial 1: ";
			Polynomial * poly1 = new Polynomial(cin);
			
			cout << "Polynomial 2: ";
			Polynomial * poly2 = new Polynomial(cin);
			
			Polynomial * result = &((* poly1) + (* poly2));
			cout << "Result: ";
			result->print();
			
			delete poly1;
			delete poly2;
			delete result;
		
		} break;
		
		case 2: {
		
			cout << "Polynomial 1: ";
			Polynomial * poly1 = new Polynomial(cin);
			
			cout << "Polynomial 2: ";
			Polynomial * poly2 = new Polynomial(cin);
			
			Polynomial * result = &((* poly1) - (* poly2));
			cout << "Result: ";
			result->print();
			
			delete poly1;
			delete poly2;
			delete result;
		
		} break;
		
		case 3: {
		
			cout << "Polynomial 1: ";
			Polynomial * poly1 = new Polynomial(cin);
			
			cout << "Polynomial 2: ";
			Polynomial * poly2 = new Polynomial(cin);
			
			Polynomial * result = &((* poly1) * (* poly2));
			cout << "Result: ";
			result->print();
			
			delete poly1;
			delete poly2;
			delete result;
		
		} break;
		
		case 4: {
		
			cout << "Polynomial 1: ";
			Polynomial * poly1 = new Polynomial(cin);
			
			cout << "Polynomial 2: ";
			Polynomial * poly2 = new Polynomial(cin);
			
			Polynomial * result = &poly1->modulus((* poly2));
			cout << "Result: ";
			result->print();
			
			delete poly1;
			delete poly2;
			delete result;
		
		} break;
		
		case 5: {
		
			cout << "Polynomial: ";
			Polynomial * poly = new Polynomial(cin);
			
			int power;
			cout << "Power: ";
			cin >> power;
			
			Polynomial * result = &poly->exponent(power);
			cout << "Result: ";
			result->print();
			
			delete poly;
			delete result;
		
		} break;
		
		case 6: {
		
			cout << "Polynomial: ";
			Polynomial * poly = new Polynomial(cin);
			
			double x;
			cout << "Value of x: ";
			cin >> x;
			
			double result = poly->evaluate(x);
			cout << "Result: " << result << endl;
			
			delete poly;
		
		} break;
		
		default:
			cout << "Not a valid operation!" << endl;
	
	}
	
	return 0;

}
