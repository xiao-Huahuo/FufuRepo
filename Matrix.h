#pragma once
#include"GlobalFile.h"
#include<vector>
class Matrix
{
private:
	int row_;//行数
	int column_;//列数
	ContentVec valuevec_;//矩阵自己
	bool issquare_ = false;//是否为方阵

public:
	//构造函数与析构函数
	Matrix() = default;
	Matrix(int row, int column);
	Matrix(int row, int column, ContentVec valuevec);
	Matrix(const Matrix& matrix);
	Matrix(ContentVec valuevec);
	~Matrix();

	//设置和获取private的接口
	bool setMatrix(int row, int column, ContentVec valuevec);
	bool setContentVec(ContentVec valuevec);
	int getRow() const;
	int getColumn() const;
	ContentVec getValueVec() const;
	bool isSquare() const;




	Matrix operator+(const Matrix& otherMatrix);//重载加号
	Matrix operator-(const Matrix& otherMatrix);//重载减号
	Matrix& operator+=(const Matrix& otherMatrix);//重载加等于号
	Matrix& operator -=(const Matrix& otherMatrix);//重载减等于号
	Matrix operator*(const Matrix& otherMatrix);//重载矩阵乘法
	Matrix& operator*(double num);//重载矩阵数乘 

	double& at(int index1, int index2);

	std::vector<double>& operator[](int index);
};


//重载ContentVec的加减
ContentVec operator+(const ContentVec& vec1, const ContentVec& vec2);
ContentVec operator-(const ContentVec& vec1, const ContentVec& vec2);
//内积乘法的运算符重载
double operator*(const ContentVec& vec1, const ContentVec& vec2);
//数乘的重载
void operator*=(ContentVec& blk, double num);

//重载矩阵相等
bool operator==(const Matrix& mat1, const Matrix& mat2);
