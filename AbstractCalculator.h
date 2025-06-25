#pragma once
#include"GlobalFile.h"
#include"Matrix.h"
#include"Det.h"
#include<map>
#include<fstream>
#include<sstream>
#include<iostream>
#include<stdexcept>
#include<algorithm>

//抽象类
class AbstractCalculator
{
public:
	//虚析构函数，便于处理子类
	virtual ~AbstractCalculator() {}

	//多态菜单虚函数
	virtual void showMenu() = 0;
};
