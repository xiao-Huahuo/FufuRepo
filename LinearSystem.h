#pragma once
#include"Det.h"
#include"Matrix.h"
class LinearSystem
{
private:
	Matrix A;//系数矩阵,arow_*acolumn_
	Matrix B;//值矩阵,arow_*1
	Matrix X;//未知量x矩阵acolumn_*1
	int arow_; //A的行数
	int acolumn_;//A的列数

public:
	LinearSystem() = default;
	LinearSystem(const Matrix& matA, const Matrix& matB);
	LinearSystem(const LinearSystem& system);

	~LinearSystem();

	Matrix getA() const;
	Matrix getB() const;
	int getARow() const;
	int getAColumn() const;
	ContentVec getValueVec()const;//返回A，便于统一接口

	void setA(const Matrix& matA);
	void setB(const Matrix& matB);

	double& at(int index1, int index2);

	int getRow() const;
	int getColumn() const;

};

bool operator==(const LinearSystem& sys1, const LinearSystem& sys2);

