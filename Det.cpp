#include"Det.h"
using namespace std;

//int order_;//阶数
//ContentVec valuevec_;//行列式自己
//double prenum_ = 1.0;//行列式前面的系数

//构造函数与析构函数
Det::Det(int order, double premiernumber) :order_(order), prenum_(premiernumber)
{
	this->valuevec_ = ContentVec(order, std::vector<double>(order, 0));

}
Det::Det(int order, ContentVec valuevec, double premiernumber) :order_(order), prenum_(premiernumber)
{
	if (valuevec.size() != order || valuevec.at(0).size() != order)
	{
		this->valuevec_.resize(order);
		for (int i = 0; i < order; i++)
		{
			this->valuevec_[i].resize(order);
		}
		std::cerr << "Construction Fault!" << std::endl;
		return;
	}
	//如果给定的行列式有效
	this->valuevec_ = valuevec;

}
Det::Det(const Det& det)
{
	this->valuevec_.clear();
	//直接拷贝，无需深拷贝
	*this = det;

}
Det::Det(ContentVec valuevec)
{
	this->prenum_ = 1;
	if (valuevec.empty() || valuevec.size() != valuevec.at(0).size())
	{
		order_ = 0;
		this->valuevec_ = ContentVec();
		return;
	}
	order_ = valuevec.size();
	valuevec_ = valuevec;
}
Det::~Det() {}

//设置和获取private的接口
bool Det::setDet(int order, ContentVec valuevec, double premiernumber)
{
	this->valuevec_.clear();
	this->order_ = order;
	this->prenum_ = premiernumber;
	if (valuevec.size() != order || valuevec.at(0).size() != order)
	{
		this->valuevec_.resize(order);
		for (int i = 0; i < order; i++)
		{
			this->valuevec_[i].resize(order);
		}
		std::cerr << "Set Det Fault!" << std::endl;
		return false;
	}
	//如果行列式有效
	this->valuevec_ = valuevec;
	return true;
}
bool Det::setContentVec(ContentVec valuevec)
{
	if (valuevec.size() == 0 || valuevec.size() != order_ || valuevec.at(0).size() != order_)
	{
		return false;
	}
	this->valuevec_ = valuevec;
	return true;
}
bool Det::setPreNum(double num)
{
	this->prenum_ = num;
	return true;
}
int Det::getOrder() const
{
	return this->order_;
}
ContentVec Det::getValueVec() const
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
double Det::getPreNum() const
{
	return this->prenum_;
}

//重载行列式数乘 
Det& Det::operator*(double num)
{
	this->prenum_ *= num;
	return *this;
}

double& Det::at(int index1, int index2)
{
	if (index1 < 0 || index1 >= this->order_ || index2 < 0 || index2 >= this->order_)
	{
		throw out_of_range("Out of range !");
	}
	return ref(this->valuevec_[index1][index2]);

}

std::vector<double>& Det::operator[](int index)
{
	if (index < 0 || index >= this->order_)
	{
		throw out_of_range("Out of range !");
	}
	return ref(this->valuevec_[index]);
}

int Det::getRow() const
{
	return this->order_;
}
int Det::getColumn() const
{
	return this->order_;
}

//重载行列式相等
bool operator==(const Det& det1, const Det& det2)
{
	return det1.getOrder() == det2.getOrder() & det1.getPreNum() == det2.getPreNum() & det1.getValueVec() == det2.getValueVec();
}

