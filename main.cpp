#include <iostream>
#include <cmath>

using namespace std;

#define URL "pastebin.com/iLBmKdyH"

class Matrix
{
	int n;
	int m;
	float** data;
public:
	Matrix();//+
	Matrix(int m, int n);//+
	Matrix(const Matrix &);//
	~Matrix();//+
	virtual Matrix& operator=(const Matrix&);//+
	virtual Matrix operator+(Matrix&);//*
	virtual Matrix operator*(Matrix&);//
	virtual Matrix operator*(float&);//+
	virtual Matrix operator-(Matrix&);//+
	virtual Matrix reverse();
	virtual Matrix transpose();//+
	virtual float determinant();//+
	virtual Matrix minorcalc(int i, int j);
	virtual ostream& print(ostream& o);//+
	virtual istream& read(istream& o);//+
	virtual void set(int i, int j, float data);//+
	virtual float get(int i, int j);//+
	virtual int getN();//+
	virtual int getM();//+
	virtual bool failed();//+
};
//
Matrix::Matrix(){
	n = 0;
	m = 0;
	data = nullptr;
}
//
Matrix::Matrix(int _m, int _n){
	m = _m;
	n = _n;

	data = new float*[n];
	for (int i = 0; i < n; i++){
		data[i] = new float[m];
		for (int k = 0; k < m; k++){
			data[i][k] = 0;
		}
	}
}
//
Matrix::Matrix(const Matrix &A){
	m = A.m;
	n = A.n;
	data = new float*[n];
		for (int i = 0; i < n; i++){
			data[i] = new float[m];
			for (int k = 0; k < m; k++){
				data[i][k] = A.data[i][k];
		}
	}
}
//
Matrix& Matrix::operator= (const Matrix &A){
		m = A.m;
		n = A.n;
		delete data;
		data = new float*[n];
		for (int i = 0; i < n; i++){
			data[i] = new float[m];
			for (int k = 0; k < n; k++){
				data[i][k] = A.data[i][k];
			}
		}
	return *this;
}
//
Matrix::~Matrix(){
	delete data;
}

//
Matrix Matrix::operator-(Matrix &A){
	Matrix M(m,n);
	if(A.n != n || A.m != m){
		return M;
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			M.set(i,j, data[j][i] - A.data[j][i]);
		}
	}
	return M;
}
//
Matrix Matrix::operator+(Matrix &A){
	Matrix M(m,n);
	if(A.n != n || A.m != m){
		return M;
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			M.set(i,j, data[j][i] + A.data[j][i]);
		}
	}
	return M;
}
//
Matrix Matrix::operator*(Matrix &A){
	if(m != A.n){
		return *this;
	}
	Matrix M(A.m,n);
	for(int i = 0; i < M.m; i++){
		for(int j = 0; j < M.n; j++){
			float mult = 0;
			for(int k = 0; k < m; k++){
				mult += data[i][k]*A.data[k][j];
			}
			M.set(j,i, mult);
		}
	}
	return M;
}
//
Matrix Matrix::operator*(float &A){
	Matrix M(m,n);
	if(this->failed()){
		return *this;
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			M.set(i,j, A*data[j][i]);
		}
	}
	return M;
}

Matrix Matrix::reverse(){
	if (determinant() == 0){
		cout << "Beach!" << endl;
		return *this;
	}
	Matrix A(n, n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			A.set(i, j, pow(-1, i + j)*(minorcalc(i, j).determinant()));
		}
	}
	float d = determinant();
	float D = 1/d;
	A = A.transpose();
	A = A*D;
	return A;
}
//
Matrix Matrix::transpose(){
	Matrix M(n,m);
	if(this->failed()){
		return *this;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			M.set(i,j, data[i][j]);
		}
	}
	return M;
}
//
Matrix Matrix::minorcalc(int col, int raw){
	Matrix Min(m - 1, n - 1);
	int col_flag = 0;
	int raw_flag = 0;
	for(int i = 0; i < n; i++){
		if (i == raw){
			continue;
		}
		for(int j = 0; j < n; j++){
			if(j == col){
				continue;
			}
			Min.set(col_flag, raw_flag, get(j,i));
			col_flag++;
		}
		col_flag = 0;
		raw_flag++;
	}
	return Min;
}
//
float Matrix::determinant(){
	if (failed()){
		return *this;
	}
	float det = 0;
	if (m == 1){
		return get(0,0);
	}
	for(int i = 0; i < n; i++){
		det += pow(-1, i)*get(i, 0)*minorcalc(i, 0).determinant();
	}
	return det;
}

void Matrix::set(int i, int j, float dat){
	data[j][i] = dat;
}
//
float Matrix::get(int i, int j){
	return data[j][i];
}
//
int Matrix::getN(){
	return n;
}
//
int Matrix::getM(){
	return m;
}

//
istream& Matrix::read(istream& in){
	in >> this->m >> this->n;
	data = new float*[n];
	for (int i = 0; i < n; i++){
		data[i] = new float[m];
		for(int k = 0; k < m; k++){
			in >> data[i][k];

		}
	}
	return in;
}
//
ostream& Matrix::print (ostream& out){
	for(int j = 0; j < n; j++){
	for (int i = 0; i < m; i++){

			out << get(i,j) << " ";
		}
		out << endl;
	}
	return out;
}
//
bool Matrix::failed(){
	if (n == 0 && m == 0){
		return true;
	}
	return false;
}

Matrix* get_init(int n, int m)
{
	Matrix* A = new Matrix(m, n);
	return A;
}
