#pragma once

class Matrix
{
protected:
	const unsigned h, w;
	double **mas;

	void create(); //new data
	void clear(); // delete data

	void output() const;
	Matrix powMatrix() const; //return powed matrix

	double& getij(int i, int j);
	double getij(int i, int j) const;
	static int intDigits(int a); //count number of digits in integer
	static int dblDigits(double a); //count number of digits in double  //не всегда работает правильно
public:
	Matrix() = delete;
	Matrix(int h, int w);
	Matrix(const Matrix& other);
	~Matrix();

	void input();
	void pow() const;
	void difPow(int st) const;
};

class linerEquations :public Matrix
{
	enum solutionTyte { ONE, INF_NONE };
	solutionTyte valid() const;
	void caseINF_NONE() const;
	void caseONE() const; // output solutions - info in last column of matrix returned by sloveONE()
	   linerEquations sloveONE() const; //return matrix with solutions in the last column //  example |1 0 0 7|  return linerEquations(0) if find proportionals
	      void makeOneInColumn(int j_fixed) const;			                              //          |0 1 0 2|
	      void makeZeroInColumn(int j_fixed) const;                                       //          |0 0 1 5|
	      bool proportional() const;
	      void makeOneInDiaginal() const;
public:
	linerEquations() = delete;
	linerEquations(int count) :Matrix(count, count + 1) {}
	linerEquations(const linerEquations &other) :Matrix(other) {}

	void input();
	void slove() const;
};