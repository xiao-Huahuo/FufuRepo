#pragma once
#include"AbstractCalculator.h"
class GC :public AbstractCalculator
{
private:
	std::string name_;
	std::string password_;
	int persontype_;
public:

	//构造函数：传入MessagePair（名字和密码的对组）
	GC(const MessagePair& inputPair, int _type);
	~GC();

	//多态菜单
	void showMenu()override;
};
