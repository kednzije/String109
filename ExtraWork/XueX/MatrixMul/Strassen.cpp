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
	if(n != m || other.n != other.m || n <= 3) {
		for(int k = 0; k < m; k++) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < other.m; j++) {
					res.mat[i][j] += mat[i][k] * other.mat[k][j];
				}
			}
		}
		return res;
	}
	Matrix this11(n / 2, m / 2), this12(n / 2, m - m / 2), this21(n - n / 2, m / 2), this22(n - n / 2, m - m / 2);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			switch (((i >= this11.n) << 1) | (j >= this11.m))
			{
			case 0:
				this11.mat[i][j] = mat[i][j];
				break;
			case 1:
				this12.mat[i][j - this11.m] = mat[i][j];
				break;
			case 2:
				this21.mat[i - this11.n][j] = mat[i][j];
				break;
			case 3:
				this22.mat[i - this11.n][j - this11.m] = mat[i][j];
				break;
			default:
				break;
			}
		}
	}
	Matrix other11(other.n / 2, other.m / 2), other12(other.n / 2, other.m - other.m / 2), 
		other21(other.n - other.n / 2, other.m / 2), other22(other.n - other.n / 2, other.m - other.m / 2);
	for(int i = 0; i < other.n; i++) {
		for(int j = 0; j < other.m; j++) {
			switch (((i >= other11.n) << 1) | (j >= other11.m))
			{
			case 0:
				other11.mat[i][j] = other.mat[i][j];
				break;
			case 1:
				other12.mat[i][j - other11.m] = other.mat[i][j];
				break;
			case 2:
				other21.mat[i - other11.n][j] = other.mat[i][j];
				break;
			case 3:
				other22.mat[i - other11.n][j - other11.m] = other.mat[i][j];
				break;
			default:
				break;
			}
		}
	}
	if(n % 2 || m % 2) {
		Matrix res11 = this11 * other11 + this12 * other21;
		Matrix res12 = this11 * other12 + this12 * other22;
		Matrix res21 = this21 * other11 + this22 * other21;
		Matrix res22 = this21 * other12 + this22 * other22;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < other.m; j++) {
				switch (((i >= res11.n) << 1) | (j >= res11.m))
				{
				case 0:
					res.mat[i][j] = res11.mat[i][j];
					break;
				case 1:
					res.mat[i][j] = res12.mat[i][j - res11.m];
					break;
				case 2:
					res.mat[i][j] = res21.mat[i - res11.n][j];
					break;
				case 3:
					res.mat[i][j] = res22.mat[i - res11.n][j - res11.m];
					break;
				default:
					break;
				}
			}
		}
		return res;
	}
	Matrix s1 = other12 - other22,
		s2 = this11 + this12,
		s3 = this21 + this22,
		s4 = other21 - other11,
		s5 = this11 + this22,
		s6 = other11 + other22,
		s7 = this12 - this22,
		s8 = other21 + other22,
		s9 = this11 - this21,
		s10 = other11 + other12;
	Matrix p1 = this11 * s1,
		p2 = s2 * other22,
		p3 = s3 * other11,
		p4 = this22 * s4,
		p5 = s5 * s6,
		p6 = s7 * s8,
		p7 = s9 * s10;
	Matrix res11 = p5 + p4 - p2 + p6;
	Matrix res12 = p1 + p2;
	Matrix res21 = p3 + p4;
	Matrix res22 = p5 + p1 - p3 - p7;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < other.m; j++) {
			switch (((i >= res11.n) << 1) | (j >= res11.m))
			{
			case 0:
				res.mat[i][j] = res11.mat[i][j];
				break;
			case 1:
				res.mat[i][j] = res12.mat[i][j - res11.m];
				break;
			case 2:
				res.mat[i][j] = res21.mat[i - res11.n][j];
				break;
			case 3:
				res.mat[i][j] = res22.mat[i - res11.n][j - res11.m];
				break;
			default:
				break;
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
	ofstream output("res0.txt");
	output << c << endl;

	input.close(), output.close();
}