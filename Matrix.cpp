#include"Matrix.h"
using namespace std;

//int row_;//行数
//int column_;//列数
//ContentVec valuevec_;//矩阵自己
//bool issquare_=false;//是否为方阵

//构造函数与析构函数
Matrix::Matrix(int row, int column) :
	row_(row), column_(column)
{

	if (row == column)//如果是方阵
	{
		this->issquare_ = true;

	}

	this->valuevec_ = ContentVec(row, std::vector<double>(column, 0));
}
Matrix::Matrix(int row, int column, ContentVec valuevec) :
	row_(row), column_(column)
{

	if (row == column)//如果是方阵
	{
		this->issquare_ = true;

	}

	if (valuevec.size() != row || valuevec.at(0).size() != column)//如果给定的矩阵无效
	{
		this->valuevec_.resize(row);
		for (int i = 0; i < row; i++)
		{
			this->valuevec_[i].resize(column);
		}
		std::cerr << "Construction Fault!" << std::endl;
		return;
	}

	//如果给定的矩阵有效
	this->valuevec_ = valuevec;
}
Matrix::Matrix(const Matrix& matrix)
{
	this->valuevec_.clear();
	//直接拷贝，不需要深拷贝
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

//设置和获取private的接口
bool Matrix::setMatrix(int row, int column, ContentVec valuevec)
{
	this->valuevec_.clear();
	this->row_ = row;
	this->column_ = column;
	if (row == column)//如果是方阵
	{
		this->issquare_ = true;

	}

	if (valuevec.size() != row || valuevec.at(0).size() != column)//如果给定的矩阵无效
	{
		this->valuevec_.resize(row);
		for (int i = 0; i < row; i++)
		{
			this->valuevec_[i].resize(column);
		}
		std::cerr << "SetMatrix Fault!" << std::endl;
		return false;
	}

	//如果给定的矩阵有效
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

//重载加减，加等于减等于，矩阵乘法，矩阵数乘
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

//重载ContentVec的加减
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
//内积乘法的运算符重载
double operator*(const ContentVec& vec1, const ContentVec& vec2)//乘法即向量内积，可以处理行*行、列*列、行*列
{
	double innerproduct = 0;
	//如果两个向量可以相乘
	if (vec1.size() == 1 && vec2.size() == 1 && vec1.at(0).size() == vec2.at(0).size())
	{
		//两个行向量
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
//数乘的重载
void operator*=(ContentVec& blk, double num)
{
	for (auto& row : blk)for (auto& val : row)val *= num;
}

//重载矩阵相等
bool operator==(const Matrix& mat1, const Matrix& mat2)
{
	return mat1.getRow() == mat2.getRow() & mat1.getColumn() == mat2.getColumn() & mat1.isSquare() == mat2.isSquare() & mat1.getValueVec() == mat2.getValueVec();
}


