#include "matrix.h"
#include "functions.h"
#include <iostream>
#include <string>
using namespace std;
int h0 = 6, w0 = 0, dist = 6;

Matrix::Matrix(int h_, int w_) :h(h_), w(w_)
{
	create();
}

Matrix::Matrix(const Matrix& other) : h(other.h), w(other.w)
{
	this->create();
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			this->mas[i][j] = other.mas[i][j];
}

Matrix::~Matrix()
{
	clear();
}

void Matrix::create()
{
	mas = new double*[h];
	for (int i = 0; i < h; i++)
		mas[i] = new double[w];
}

void Matrix::clear()
{
	for (int i = 0; i < h; i++)
		delete[]mas[i];
	delete[]mas;
}

void Matrix::input()
{
	for (int i = 0; i < h; i++)
	{
		w0 = 0;
		for (int j = 0; j < w; j++)
		{
			gotoxy(w0, h0);
			std::cin >> mas[i][j];
			if (std::cin.fail()) throw std::invalid_argument("you input not a number");
			w0 += dist;
		}
		h0 += dist / 2 - 1;
	}
}

void Matrix::output() const
{
	int rememb = h0;
	for (int i = 0; i < h; i++)
	{
		w0 = 1;
		for (int j = 0; j < w; j++)
		{
			gotoxy(w0, h0);
			double tmp = round(mas[i][j] * 100) / 100;
			std::cout << tmp;
			w0 += dist;
		}
		h0 += dist / 2;
	}
	for (int i = 0; i < h * 3 - 2; i++)
	{
		gotoxy(0, rememb);
		std::cout << '|';
		gotoxy(w * dist, rememb);
		std::cout << '|';
		rememb++;
	}
	gotoxy(0, h0);
}

//1 2 3 
//4 5 6
//7 8 9
//mas[0,0] = mas[0,0]*mas[0,0] + mas[0,1]*mas[1,0] + .... + mas[0][k]*mas[k][0]
//mas[0,1] = mas[0,0]*mas[0,1] + mas[0,1]*mas[1,1] + mas[0,2]*mas[1,2]
//mas[1,0] = mas[1,0]*mas[0,0] + mas[1,1]*mas[1,0] + mas[1,2]*mas[2,0]
//mas[1,1] = mas[1,0]*mas[0,1] + mas[1,1]*mas[1,1] + mas[1,2]*mas[2,1]
//mas[1,2] = mas[1,0]*mas[0,2] + mas[1,1]*mas[1,2] + mas[1,2]*mas[2,2]

void Matrix::pow() const
{
	this->powMatrix().output();
}

Matrix Matrix::powMatrix() const
{
	Matrix tmp(h, w);
	double sum = 0;
	for (int i_fixed = 0; i_fixed < w; i_fixed++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				sum += mas[i_fixed][j] * mas[j][i];
			}
			tmp.mas[i_fixed][i] = sum;
			sum = 0;
		}
	}
	return tmp;
}

void Matrix::difPow(int st) const
{
	Matrix tmp(h, w);
	for (int i = 0; i < st / 2; i++) tmp.powMatrix();
}

double& Matrix::getij(int i, int j)
{
	if (i < h && j < w) return mas[i][j];
	else throw logic_error("smth wrong with getters");
}

double Matrix::getij(int i, int j) const
{
	if (i < h && j < w) return mas[i][j];
	else throw logic_error("smth wrong with getters");
}

int Matrix::intDigits(int a)
{
	return to_string(a).size();
}

int Matrix::dblDigits(double a) //не всегда работает правильно
{
	if (a - floor(a) == 0) //if integer
		return intDigits(int(a));
	int k = 0;
	if (round(a) == 0) k++; //if a є(-1; 1)
	while (abs(a) - floor(abs(a)) > 0.0001) // example: a = 32.153 and then a = 32153
		a *= 10;
	return intDigits(int(a)) + 1 + k;
}

//------------------------------------------------------
//------------------------------------------------------


void linerEquations::input()
{
	h0++;
	for (int i = 0; i < h; i++)
	{
		w0 = 0;
		for (int j = 0; j < w; j++)
		{
			gotoxy(w0, h0);
			std::cin >> mas[i][j];
			int d = dblDigits(mas[i][j]);
			if (std::cin.fail()) throw std::invalid_argument("you input not a number");
			gotoxy(w0 + d, h0);
			if (j != h) cout << "x" << j + 1;
			if (j < h - 1) cout << " + ";
			if (j == h - 1) cout << " = ";
			cout << endl;
			w0 += dist - 1 + d;
		}
		h0 += 1;
	}
	cout << endl;
}


void linerEquations::slove() const
{
	switch (this->valid())
	{
	case ONE: caseONE(); break;
	case INF_NONE: caseINF_NONE(); break;
	}
}

void linerEquations::caseINF_NONE() const
{
	cout << "this system doesn't has one solution" << endl;
}

void linerEquations::caseONE() const
{
	linerEquations tmp(this->sloveONE());
	if (tmp.h != 0) //sloveONE return linerEquations(0) if find proportionals
	{
		cout << "The solutions are:" << endl;
		for (int i = 0; i < h; i++)
			cout << "x" << i + 1 << " = " << round(tmp.mas[i][h] * 1000) / 1000 << endl;
	}
}

linerEquations linerEquations::sloveONE() const
{
	linerEquations tmp(*this);
	for (int again = 0; again < 2; again++)
	{
		for (int j_fixed = 0; j_fixed < h; j_fixed++)
		{
			tmp.makeOneInColumn(j_fixed);
			tmp.makeZeroInColumn(j_fixed);
			if (tmp.proportional())
			{
				caseINF_NONE();
				return linerEquations(0);
			}
		}
	}
	tmp.makeOneInDiaginal();
	return tmp;
}

void linerEquations::makeOneInColumn(int j_fixed) const
{
	for (int i = 0; i < h; i++)
	{
		if (mas[i][j_fixed] != 0)
		{
			double tm = mas[i][j_fixed];
			for (int j = 0; j < w; j++)
				mas[i][j] /= tm;
			mas[i][j_fixed] = 1;
		}
	}
}

void linerEquations::makeZeroInColumn(int j_fixed) const
{
	for (int i = 0; i < h; i++)
	{
		if (mas[i][j_fixed] != 0 && i != j_fixed)
		{
			for (int j = 0; j < w; j++)
				mas[i][j] -= mas[j_fixed][j];
		}
	}
}

void linerEquations::makeOneInDiaginal() const
{
	for (int i = 0; i < h; i++)
	{
		if (mas[i][i] != 0)
		{
			mas[i][w - 1] /= mas[i][i];
			mas[i][i] = 1;
		}
	}
}

linerEquations::solutionTyte linerEquations::valid() const
{
	bool allKoefZero = true;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w - 1; j++)
		{
			if (mas[i][j] != 0)
			{
				allKoefZero = false;
				break;
			}
		}
		if (allKoefZero) return INF_NONE;
		allKoefZero = true;
	}
	return ONE;
}

bool linerEquations::proportional() const
{
	bool allKoefZero = true;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w - 1; j++)
		{
			if (mas[i][j] != 0)
			{
				allKoefZero = false;
				break;
			}
		}
		if (allKoefZero) return true;
		allKoefZero = true;
	}
	return false;
}
