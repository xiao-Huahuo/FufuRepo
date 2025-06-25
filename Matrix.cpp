#include"Matrix.h"
using namespace std;

//int row_;//����
//int column_;//����
//ContentVec valuevec_;//�����Լ�
//bool issquare_=false;//�Ƿ�Ϊ����

//���캯������������
Matrix::Matrix(int row, int column) :
	row_(row), column_(column)
{

	if (row == column)//����Ƿ���
	{
		this->issquare_ = true;

	}

	this->valuevec_ = ContentVec(row, std::vector<double>(column, 0));
}
Matrix::Matrix(int row, int column, ContentVec valuevec) :
	row_(row), column_(column)
{

	if (row == column)//����Ƿ���
	{
		this->issquare_ = true;

	}

	if (valuevec.size() != row || valuevec.at(0).size() != column)//��������ľ�����Ч
	{
		this->valuevec_.resize(row);
		for (int i = 0; i < row; i++)
		{
			this->valuevec_[i].resize(column);
		}
		std::cerr << "Construction Fault!" << std::endl;
		return;
	}

	//��������ľ�����Ч
	this->valuevec_ = valuevec;
}
Matrix::Matrix(const Matrix& matrix)
{
	this->valuevec_.clear();
	//ֱ�ӿ���������Ҫ���
	*this = matrix;
}
Matrix::Matrix(ContentVec valuevec)
{
	if (valuevec.empty())
	{
		row_ = 0, column_ = 0;
		this->valuevec_ = ContentVec();
		return;
	}
	row_ = valuevec.size();
	column_ = valuevec.at(0).size();
	valuevec_ = valuevec;
}
Matrix::~Matrix() {}

//���úͻ�ȡprivate�Ľӿ�
bool Matrix::setMatrix(int row, int column, ContentVec valuevec)
{
	this->valuevec_.clear();
	this->row_ = row;
	this->column_ = column;
	if (row == column)//����Ƿ���
	{
		this->issquare_ = true;

	}

	if (valuevec.size() != row || valuevec.at(0).size() != column)//��������ľ�����Ч
	{
		this->valuevec_.resize(row);
		for (int i = 0; i < row; i++)
		{
			this->valuevec_[i].resize(column);
		}
		std::cerr << "SetMatrix Fault!" << std::endl;
		return false;
	}

	//��������ľ�����Ч
	this->valuevec_ = valuevec;
	return true;
}
bool Matrix::setContentVec(ContentVec valuevec)
{
	if (valuevec.size() == 0 || valuevec.size() != row_ || valuevec.at(0).size() != column_)
	{
		return false;
	}
	this->valuevec_ = valuevec;
	return true;
}
int Matrix::getRow() const { return row_; }
int Matrix::getColumn() const { return column_; }
ContentVec Matrix::getValueVec() const
{
	if (this->valuevec_.size() != 0)
	{
		return this->valuevec_;
	}
	else
	{
		return ContentVec();
	}
}
bool Matrix::isSquare() const { return issquare_; }

//���ؼӼ����ӵ��ڼ����ڣ�����˷�����������
Matrix Matrix::operator+(const Matrix& otherMatrix)
{
	if (this->row_ != otherMatrix.row_ || this->column_ != otherMatrix.column_)
	{
		return Matrix();
	}
	return Matrix(row_, column_, this->valuevec_ + otherMatrix.valuevec_);
}
Matrix Matrix::operator-(const Matrix& otherMatrix)
{
	if (this->row_ != otherMatrix.row_ || this->column_ != otherMatrix.column_)
	{
		return Matrix();
	}
	return Matrix(row_, column_, this->valuevec_ - otherMatrix.valuevec_);
}
Matrix& Matrix::operator+=(const Matrix& otherMatrix)
{
	if (this->row_ != otherMatrix.row_ || this->column_ != otherMatrix.column_)
	{
		return *this;
	}
	for (int i = 0; i < valuevec_.size(); i++)
	{
		for (int j = 0; j < valuevec_.at(0).size(); j++)
		{
			this->valuevec_[i][j] += otherMatrix.valuevec_[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator -=(const Matrix& otherMatrix)
{
	if (this->row_ != otherMatrix.row_ || this->column_ != otherMatrix.column_)
	{
		return *this;
	}
	for (int i = 0; i < valuevec_.size(); i++)
	{
		for (int j = 0; j < valuevec_.at(0).size(); j++)
		{
			this->valuevec_[i][j] -= otherMatrix.valuevec_[i][j];
		}
	}
	return *this;
}
Matrix Matrix::operator*(const Matrix& otherMatrix)
{
	try
	{
		if (this->column_ != otherMatrix.row_)
		{
			return Matrix();
		}
		ContentVec block(row_, std::vector<double>(otherMatrix.column_, 0));
		for (int i = 0; i < this->row_; i++)
		{
			for (int j = 0; j < otherMatrix.column_; j++)
			{
				for (int k = 0; k < this->column_; k++)
				{
					block[i][j] += this->valuevec_[i][k] * otherMatrix.valuevec_[k][j];
				}
			}
		}

		return Matrix(block.size(), block.at(0).size(), block);
	}
	catch (out_of_range& err)
	{
		std::cerr << "Matrix multiply exception!" << std::endl;
		return Matrix();
	}
}
Matrix& Matrix::operator*(double num)
{
	for (int i = 0; i < this->row_; i++)
	{
		for (int j = 0; j < this->column_; j++)
		{
			this->valuevec_[i][j] *= num;
		}
	}
	return *this;
}

double& Matrix::at(int index1, int index2)
{
	if (index1 < 0 || index1 >= this->row_ || index2 < 0 || index2 >= this->column_)
	{
		throw out_of_range("Out of range !");
	}
	return ref(this->valuevec_[index1][index2]);

}

std::vector<double>& Matrix::operator[](int index)
{
	if (index < 0 || index >= this->row_)
	{
		throw out_of_range("Out of range !");
	}
	return ref(this->valuevec_[index]);
}

//����ContentVec�ļӼ�
ContentVec operator+(const ContentVec& vec1, const ContentVec& vec2)
{
	if (vec1.size() != vec2.size() || vec1.at(0).size() != vec2.at(0).size())
	{
		return ContentVec();
	}

	ContentVec blockvec = vec1;
	for (int i = 0; i < blockvec.size(); i++)
	{
		for (int j = 0; j < blockvec.at(0).size(); j++)
		{
			blockvec[i][j] += vec2[i][j];
		}
	}
	return blockvec;

}
ContentVec operator-(const ContentVec& vec1, const ContentVec& vec2)
{
	if (vec1.size() != vec2.size() || vec1.at(0).size() != vec2.at(0).size())
	{
		return ContentVec();
	}

	ContentVec blockvec = vec1;
	for (int i = 0; i < blockvec.size(); i++)
	{
		for (int j = 0; j < blockvec.at(0).size(); j++)
		{
			blockvec[i][j] -= vec2[i][j];
		}
	}
	return blockvec;

}
//�ڻ��˷������������
double operator*(const ContentVec& vec1, const ContentVec& vec2)//�˷��������ڻ������Դ�����*�С���*�С���*��
{
	double innerproduct = 0;
	//������������������
	if (vec1.size() == 1 && vec2.size() == 1 && vec1.at(0).size() == vec2.at(0).size())
	{
		//����������
		for (int j = 0; j < vec1.at(0).size(); j++)
		{
			innerproduct += vec1[0][j] * vec2[0][j];
		}
	}
	else if (vec1.at(0).size() == 1 && vec2.at(0).size() == 1 && vec1.size() == vec2.size())
	{
		for (int i = 0; i < vec1.size(); i++)
		{
			innerproduct += vec1[i][0] * vec2[i][0];
		}
	}
	else if (vec1.size() == 1 && vec2.at(0).size() == 1 && vec1.at(0).size() == vec2.size())
	{
		for (int i = 0; i < vec1.at(0).size(); i++)
		{
			innerproduct += vec1[0][i] * vec2[i][0];
		}
	}
	return innerproduct;
}
//���˵�����
void operator*=(ContentVec& blk, double num)
{
	for (auto& row : blk)for (auto& val : row)val *= num;
}

//���ؾ������
bool operator==(const Matrix& mat1, const Matrix& mat2)
{
	return mat1.getRow() == mat2.getRow() & mat1.getColumn() == mat2.getColumn() & mat1.isSquare() == mat2.isSquare() & mat1.getValueVec() == mat2.getValueVec();
}


