#pragma once
#include"GlobalFile.h"
#include"Det.h"
#include"Matrix.h"
#include"LinearSystem.h"
#include"AbstractCalculator.h"
#include"GeneralCalculator.h"
#include"LinearAlgebraCalculator.h"
#include"Games.h"
#include<vector>
#include<thread>
#include<chrono>
#include<string>
#include<algorithm>
#include<iomanip>
#include<iostream>
class Admin
{
public:

	//显示欢迎界面
	void showMainMenu();
	//显示计算器选择界面
	void showCalMenu(int _type);

	//登陆函数
	void loginAdmin(std::string FILEname_, int _type);

	//计算器选择菜单
	void chooseCalculator(AbstractCalculator*& BASE, int _type, const MessagePair& inputPair);
	//管理员在进入计算机选择菜单之后添加和删除和查找Human的功能
	bool addHuman();
	bool delHuman();
	bool findHuman(const std::string& name_);

	//三个多态子菜单，，传入基类指针，首先需要显式转换为子类
	void generalCalculatorMenu(AbstractCalculator*& general);
	void linearAlgebraCalculatorMenu(AbstractCalculator*& linear);
	void gamesPlayerMenu(AbstractCalculator*& calculus);

};
