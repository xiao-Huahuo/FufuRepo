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

//������
class AbstractCalculator
{
public:
	//���������������ڴ�������
	virtual ~AbstractCalculator() {}

	//��̬�˵��麯��
	virtual void showMenu() = 0;
};
