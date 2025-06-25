#pragma once
#include"GlobalFile.h"
#include<vector>
class Det
{
private:
	int order_ = 0;//阶数
	ContentVec valuevec_;//行列式自己
	double prenum_ = 1.0;//行列式前面的系数

public:
	//构造函数与析构函数
	Det() = default;
	Det(int order, double premiernumber);
	Det(int order, ContentVec valuevec, double premiernumber);
	Det(const Det& det);
	Det(ContentVec valuevec);
	~Det();

	//设置和获取private的接口
	bool setDet(int order, ContentVec valuevec, double premiernumber);
	bool setContentVec(ContentVec blockvec);
	bool setPreNum(double num);
	int getOrder() const;
	ContentVec getValueVec() const;
	double getPreNum() const;


	Det& operator*(double num);//重载行列式数乘 

	double& at(int index1, int index2);

	std::vector<double>& operator[](int index);

	int getRow() const;
	int getColumn() const;
};


bool operator==(const Det& det1, const Det& det2);//重载行列式相等
