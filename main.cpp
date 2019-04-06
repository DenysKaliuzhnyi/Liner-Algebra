#include <iostream>
#include "matrix.h"
using namespace std;

void info();
void doChoice1();
void doChoice2();

int main()
{
	int choice;
	info();
	try
	{
		cin >> choice;
		if (cin.fail()) throw std::invalid_argument("you input not a number");
		switch (choice)
		{
		case 1: doChoice1(); break;
		case 2: doChoice2(); break;
		default: cout << "Ops, such option doesn't exist" << endl;
		}
	}
	catch (const bad_alloc &ex) { cout << ex.what() << ": not enough data" << endl; }
	catch (const invalid_argument &ex) { cout << ex.what() << endl; }
	catch (const logic_error &ex) { cout << ex.what() << endl; }
	catch (const exception &ex) { cout << ex.what() << endl; }
	system("pause");
	return 0;
}

void info()
{
	cout << "This program can do such things: " << endl;
	cout << "1) Slove a system of liner equations." << endl;
	cout << "2) Pow matrix." << endl;
	cout << "Input numer of function you need: ";
}

void doChoice1()
{
	unsigned count;
	cout << "Input count of variables:";
	cin >> count;
	if (std::cin.fail()) throw std::invalid_argument("you input not a number");
	if (count == 0) throw invalid_argument("ghm, looks very interesting...");
	linerEquations l(count);
	cout << "Input coefficients from x1, then x2, x3....: ";
	l.input();
	l.slove();
}

void doChoice2()
{
	unsigned dim;
	cout << "Input dim of matrix: ";
	cin >> dim;
	if (std::cin.fail()) throw std::invalid_argument("you input not a number");
	if (dim == 0) throw invalid_argument("ghm, looks very interesting...");
	Matrix m(dim, dim);
	cout << "Input your matrix:" << endl;
	m.input();
	cout << "Powed matrix:" << endl;
	m.pow();
}
