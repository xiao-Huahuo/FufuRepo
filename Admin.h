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

	//��ʾ��ӭ����
	void showMainMenu();
	//��ʾ������ѡ�����
	void showCalMenu(int _type);

	//��½����
	void loginAdmin(std::string FILEname_, int _type);

	//������ѡ��˵�
	void chooseCalculator(AbstractCalculator*& BASE, int _type, const MessagePair& inputPair);
	//����Ա�ڽ�������ѡ��˵�֮����Ӻ�ɾ���Ͳ���Human�Ĺ���
	bool addHuman();
	bool delHuman();
	bool findHuman(const std::string& name_);

	//������̬�Ӳ˵������������ָ�룬������Ҫ��ʽת��Ϊ����
	void generalCalculatorMenu(AbstractCalculator*& general);
	void linearAlgebraCalculatorMenu(AbstractCalculator*& linear);
	void gamesPlayerMenu(AbstractCalculator*& calculus);

};
