#include"GlobalFile.h"
#include"Det.h"
#include"Matrix.h"
#include"LinearSystem.h"
#include"AbstractCalculator.h"
#include"GeneralCalculator.h"
#include"LinearAlgebraCalculator.h"
#include"Games.h"
#include"Admin.h"
#include<thread>
#include<chrono>
using namespace std;

int main()
{
	try
	{
		Admin* admin = new Admin;
		int choice;
		while (true)
		{
			system("cls");
			admin->showMainMenu();
			cin >> choice;
			switch (choice)
			{
			case 1:
				admin->loginAdmin(AdminISTRATOR_FILE, 1);
				break;
			case 2:
				admin->loginAdmin(HUMAN_FILE, 2);
				break;
			case -1:
			{
				//免登录直接进入线性代数计算器
				AbstractCalculator* base = new LAC(std::make_pair("1", "1"), 1);
				admin->linearAlgebraCalculatorMenu(base);
				break;
			}
			case 0:
				std::cout << "=================Looking forward to next-time meeting.！=====================" << std::endl;
				system("pause");
				return 0;
				break;
			default:
				std::cerr << REINPUT_PHRASE << std::endl;
				break;
			}
		}

	}
	catch (out_of_range& err)
	{
		std::cerr << err.what() << std::endl;
		system("pause");
	}
	catch (...)
	{
		std::cerr << "An unknown exception occurred!" << std::endl;
		system("pause");
	}
	return 0;
}

