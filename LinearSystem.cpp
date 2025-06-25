#include"LinearSystem.h"
using namespace std;

//Matrix A;//系数矩阵,arow_*acolumn_
//Matrix B;//值矩阵,arow_*1
//Matrix X;//未知量x矩阵acolumn_*1
//int arow_; //A的行数
//int acolumn_;//A的列数

LinearSystem::LinearSystem(const Matrix& matA, const Matrix& matB)
{
	if (matA.getRow() != matB.getRow() || B.getColumn() != 1)
	{
		this->A = Matrix();
		this->B = Matrix();
		this->arow_ = 0, this->acolumn_ = 0;
		this->X = Matrix();
	}

	this->A = matA;
	this->B = matB;
	this->arow_ = matA.getRow();
	this->acolumn_ = matA.getColumn();
	this->X = Matrix(acolumn_, 1);
}
LinearSystem::LinearSystem(const LinearSystem& system)
{
	this->A = system.A;
	this->B = system.B;
	this->arow_ = system.A.getRow();
	this->acolumn_ = system.A.getColumn();
	this->X = Matrix(acolumn_, 1);
}
LinearSystem::~LinearSystem() {}

Matrix LinearSystem::getA()  const { return A; }
Matrix LinearSystem::getB() const { return B; }
int LinearSystem::getARow() const { return arow_; }
int LinearSystem::getAColumn() const { return acolumn_; }
//返回A，便于统一接口
ContentVec LinearSystem::getValueVec()const
{
	if (A.getValueVec().size() != 0)
	{
		return A.getValueVec();
	}
	else
	{
		return ContentVec();
	}
}


void LinearSystem::setA(const Matrix& matA)
{
	if (matA.getRow() != A.getRow() || matA.getColumn() != A.getColumn())
	{
		return;
	}

	this->A = matA;
}
void LinearSystem::setB(const Matrix& matB)
{
	if (matB.getRow() != B.getRow() || matB.getColumn() != B.getColumn())
	{
		return;
	}

	this->B = matB;
}

double& LinearSystem::at(int index1, int index2)
{
	if (index1 < 0 || index1 >= this->arow_ || index2 < 0 || index2 >= this->acolumn_)
	{
		throw out_of_range("Out of range !");
	}
	return ref(this->A.at(index1, index2));
}

int LinearSystem::getRow() const
{
	return this->A.getRow();
}
int LinearSystem::getColumn() const
{
	return this->A.getColumn();
}

bool operator==(const LinearSystem& sys1, const LinearSystem& sys2)
{
	return sys1.getA() == sys2.getA() && sys1.getB() == sys2.getB();
}
