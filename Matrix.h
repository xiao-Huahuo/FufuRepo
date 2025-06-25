#pragma once
#include"GlobalFile.h"
#include<vector>
class Matrix
{
private:
	int row_;//����
	int column_;//����
	ContentVec valuevec_;//�����Լ�
	bool issquare_ = false;//�Ƿ�Ϊ����

public:
	//���캯������������
	Matrix() = default;
	Matrix(int row, int column);
	Matrix(int row, int column, ContentVec valuevec);
	Matrix(const Matrix& matrix);
	Matrix(ContentVec valuevec);
	~Matrix();

	//���úͻ�ȡprivate�Ľӿ�
	bool setMatrix(int row, int column, ContentVec valuevec);
	bool setContentVec(ContentVec valuevec);
	int getRow() const;
	int getColumn() const;
	ContentVec getValueVec() const;
	bool isSquare() const;




	Matrix operator+(const Matrix& otherMatrix);//���ؼӺ�
	Matrix operator-(const Matrix& otherMatrix);//���ؼ���
	Matrix& operator+=(const Matrix& otherMatrix);//���ؼӵ��ں�
	Matrix& operator -=(const Matrix& otherMatrix);//���ؼ����ں�
	Matrix operator*(const Matrix& otherMatrix);//���ؾ���˷�
	Matrix& operator*(double num);//���ؾ������� 

	double& at(int index1, int index2);

	std::vector<double>& operator[](int index);
};


//����ContentVec�ļӼ�
ContentVec operator+(const ContentVec& vec1, const ContentVec& vec2);
ContentVec operator-(const ContentVec& vec1, const ContentVec& vec2);
//�ڻ��˷������������
double operator*(const ContentVec& vec1, const ContentVec& vec2);
//���˵�����
void operator*=(ContentVec& blk, double num);

//���ؾ������
bool operator==(const Matrix& mat1, const Matrix& mat2);
