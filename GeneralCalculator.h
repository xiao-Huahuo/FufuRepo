#pragma once
#include"AbstractCalculator.h"
class GC :public AbstractCalculator
{
private:
	std::string name_;
	std::string password_;
	int persontype_;
public:

	//���캯��������MessagePair�����ֺ�����Ķ��飩
	GC(const MessagePair& inputPair, int _type);
	~GC();

	//��̬�˵�
	void showMenu()override;
};
