#pragma once
#include"Det.h"
#include"Matrix.h"
class LinearSystem
{
private:
	Matrix A;//ϵ������,arow_*acolumn_
	Matrix B;//ֵ����,arow_*1
	Matrix X;//δ֪��x����acolumn_*1
	int arow_; //A������
	int acolumn_;//A������

public:
	LinearSystem() = default;
	LinearSystem(const Matrix& matA, const Matrix& matB);
	LinearSystem(const LinearSystem& system);

	~LinearSystem();

	Matrix getA() const;
	Matrix getB() const;
	int getARow() const;
	int getAColumn() const;
	ContentVec getValueVec()const;//����A������ͳһ�ӿ�

	void setA(const Matrix& matA);
	void setB(const Matrix& matB);

	double& at(int index1, int index2);

	int getRow() const;
	int getColumn() const;

};

bool operator==(const LinearSystem& sys1, const LinearSystem& sys2);

