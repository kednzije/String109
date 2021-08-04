#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;
constexpr int MAXN = 1e4;

class Matrix {
public:
	Matrix();
	Matrix(const Matrix&);
	Matrix(int, int);
	~Matrix();
	Matrix subMat(int, int, int, int) const;
	friend istream& operator >> (istream &in, Matrix &matrix);
	friend ostream& operator << (ostream &out, Matrix &matrix);
	void operator = (const Matrix&);
	Matrix operator + (const Matrix&) const;
	Matrix operator - (const Matrix&) const;
	Matrix operator * (const Matrix&) const;
private:
	int n, m, **mat;
};

Matrix::Matrix() {
	n = m = 0;
	mat = nullptr;
}
Matrix::Matrix(const Matrix& other) {
	n = other.n, m = other.m;
	mat = new int*[n];
	for(int i = 0; i < n; i++) {
		mat[i] = new int[m];
		for(int j = 0; j < m; j++) {
			mat[i][j] = other.mat[i][j];
		}
	}
}
Matrix::Matrix(int _n, int _m) {
	n = _n, m = _m;
	mat = new int*[n];
	for(int i = 0; i < n; i++) {
		mat[i] = new int[m] ();
	}
}
Matrix::~Matrix() {
	for(int i = 0; i < n; i++) {
		delete[] mat[i];
	}
	delete[] mat;
	mat = nullptr;
	n = m = 0;
}
Matrix Matrix::subMat(int l0, int r0, int l1, int r1) const {
	assert(l1 >= l0 && r1 >= r0);
	Matrix submat(l1 - l0 + 1, r1 - r0 + 1);
	for(int i = l0; i <= l1; i++) {
		for(int j = r0; j <= r1; j++) {
			submat.mat[i - l0][j - r0] = mat[i][j];
		}
	}
	return submat;
}
istream& operator >> (istream &in, Matrix &matrix) {
	assert(matrix.mat != nullptr);
	for(int i = 0; i < matrix.n; i++) {
		for(int j = 0; j < matrix.m; j++) {
			in >> matrix.mat[i][j];
		}
	}
	return in;
}
ostream& operator << (ostream &out, Matrix &matrix) {
	assert(matrix.mat != nullptr);
	for(int i = 0; i < matrix.n; i++) {
		for(int j = 0; j < matrix.m; j++) {
			out << matrix.mat[i][j] << ' ';
		}
		if(i < matrix.n - 1) {
			out << endl;
		}
	}
	return out;
}
void Matrix::operator = (const Matrix& other) {
	this->~Matrix();
	n = other.n, m = other.m;
	mat = new int*[n];
	for(int i = 0; i < n; i++) {
		mat[i] = new int[m];
		for(int j = 0; j < m; j++) {
			mat[i][j] = other.mat[i][j];
		}
	}
}
Matrix Matrix::operator + (const Matrix& other) const {
	assert(n == other.n && m == other.m);
	Matrix res(n, m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			res.mat[i][j] = mat[i][j] + other.mat[i][j];
		}
	}
	return res;
}
Matrix Matrix::operator - (const Matrix& other) const {
	assert(n == other.n && m == other.m);
	Matrix res(n, m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			res.mat[i][j] = mat[i][j] - other.mat[i][j];
		}
	}
	return res;
}
Matrix Matrix::operator * (const Matrix& other) const {
	assert(m == other.n);
	Matrix res(n, other.m);
	for(int k = 0; k < m; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < other.m; j++) {
				res.mat[i][j] += mat[i][k] * other.mat[k][j];
			}
		}
	}
	return res;
}

int main() {
	ifstream input("data.txt");
	int n;
	input >> n;
	Matrix a(n, n), b(n, n);
	input >> a >> b;
	Matrix c = a * b;
	ofstream output("res1.txt");
	output << c << endl;

	input.close(), output.close();
}