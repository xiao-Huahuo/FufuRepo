#pragma once
#include"GlobalFile.h"
#include<vector>
class Det
{
private:
	int order_ = 0;//����
	ContentVec valuevec_;//����ʽ�Լ�
	double prenum_ = 1.0;//����ʽǰ���ϵ��

public:
	//���캯������������
	Det() = default;
	Det(int order, double premiernumber);
	Det(int order, ContentVec valuevec, double premiernumber);
	Det(const Det& det);
	Det(ContentVec valuevec);
	~Det();

	//���úͻ�ȡprivate�Ľӿ�
	bool setDet(int order, ContentVec valuevec, double premiernumber);
	bool setContentVec(ContentVec blockvec);
	bool setPreNum(double num);
	int getOrder() const;
	ContentVec getValueVec() const;
	double getPreNum() const;


	Det& operator*(double num);//��������ʽ���� 

	double& at(int index1, int index2);

	std::vector<double>& operator[](int index);

	int getRow() const;
	int getColumn() const;
};


bool operator==(const Det& det1, const Det& det2);//��������ʽ���
