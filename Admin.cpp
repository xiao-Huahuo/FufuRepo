#include"Admin.h"
using namespace std;

//��ʾ��ӭ����
void Admin::showMainMenu()
{

	std::cout << "\t\t===================Welcome to Calculator��=====================" << std::endl;
	std::cout << "\t\t|                       1.Administrator                      |" << std::endl;
	std::cout << "\t\t|                                                            |" << std::endl;
	std::cout << "\t\t|                          2.Human                           |" << std::endl;
	std::cout << "\t\t|                                                            |" << std::endl;
	std::cout << "\t\t|                          0.Exit                            |" << std::endl;
	std::cout << "\t\t==============================================================" << std::endl;
	std::cout << "Please chooce your identity�� ";

}
//��ʾ������ѡ�����
void Admin::showCalMenu(int _type)
{
	std::cout << "\t\t=====================Welcome to Calculator��===================" << std::endl;
	std::cout << "\t\t|                       1.Linear Algebra                     |" << std::endl;
	std::cout << "\t\t|                                                            |" << std::endl;
	std::cout << "\t\t|                        2.Play Games ?                      |" << std::endl;
	std::cout << "\t\t|                                                            |" << std::endl;
	std::cout << "\t\t|                     3.General Calculator                   |" << std::endl;
	if (_type == 1)
	{
		std::cout << "\t\t|                                                            |\n";
		std::cout << "\t\t|                          4.Add Human                       |\n";
		std::cout << "\t\t|                                                            |\n";
		std::cout << "\t\t|                         5.Delete Human                     |\n";
	}
	std::cout << "\t\t|                                                            |" << std::endl;
	std::cout << "\t\t|                           0.Exit                           |" << std::endl;
	std::cout << "\t\t==============================================================" << std::endl;

}

//��½����
//_type��1�ǹ���Ա��2����ͨ��
void Admin::loginAdmin(std::string FILEname_, int _type)
{
	AbstractCalculator* BASE = nullptr;

	ifstream ifs(FILEname_, ios::in);

	while (true)
	{
		try
		{
			//�ļ���ʧ��
			if (!ifs.is_open())
			{
				throw runtime_error(FILEname_ + " was not open");
				return;
			}
			//����ļ�Ϊ��
			if (ifs.eof())
			{
				return;
			}
			//�ļ������Ҳ�Ϊ��
			std::vector<MessagePair>MessageVec;
			std::string line, tName, tPass;
			//���ļ���ȡ��MessageVec
			while (std::getline(ifs, line))
			{
				stringstream ss(line);
				ss >> tName >> tPass;
				MessageVec.emplace_back(MessagePair(tName, tPass));

			}

			//�������ֺ�����
			MessagePair inputPair;
			std::cout << "Please input your name:";
			std::cin >> inputPair.first;
			std::cout << "Please input your password:";
			std::cin >> inputPair.second;

			auto it = std::find(MessageVec.begin(), MessageVec.end(), inputPair);
			if (it == MessageVec.end())
			{
				std::cout << "No existence of your name ! Please input your name and password!" << std::endl;
				system("pause");
				continue;
			}
			else
			{
				//������֤�ɹ�
				std::cout << "Successfully login!" << std::endl;
				//���������ѡ��˵�
				chooseCalculator(BASE, _type, inputPair);
			}
		}
		catch (runtime_error& err)//���ν��룬���Դ���һ������Ա�˻�
		{
			std::cout << err.what() << std::endl;
			if (_type == 1)
			{
				//ѡ����Ա���Դ���һ������Ա
				std::cout << "You are Administrator.Whether to create an account for you?" << std::endl;
				std::cout << "1.Yes    2.No" << std::endl;
				int choice = 0;
				std::cin >> choice;
				if (choice == 1)
				{
					//�������ֺ�����
					MessagePair reinputPair;
					std::cout << "Please input the name:";
					std::cin >> reinputPair.first;
					std::cout << "Please input the password:";
					std::cin >> reinputPair.second;
					//��¼��ȥ�ļ�
					ofstream ofs(AdminISTRATOR_FILE, ios::out);
					ofs << reinputPair.first << " " << reinputPair.second << std::endl;
					ofs.close();
					std::cout << "Your name is: " << reinputPair.first << ",Password: " << reinputPair.second << std::endl;
					system("pause");
					std::cout << "About to re-login......" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(1200));
					return;
				}
				else if (choice == 2)
				{
					std::cout << "Operation has been withdrawn." << std::endl;
					return;
				}
				else
				{
					std::cerr << ERR_PHRASE << std::endl;
					return;
				}
			}
			else if (_type == 2)
			{
				std::cerr << "You CANNOT login ! Please contact administrator in order to sign up your account." << std::endl;
				system("pause");
				return;
			}
		}
	}
}

//������ѡ��˵�
void Admin::chooseCalculator(AbstractCalculator*& BASE, int _type, const MessagePair& inputPair)
{
	system("cls");
	this->showCalMenu(_type);
	int Choice = 0;
	while (true)
	{

		//������ӹ�Ϊ���������
		cin >> Choice;
		switch (Choice)
		{
		case 1:
			BASE = new LAC(inputPair, _type);
			linearAlgebraCalculatorMenu(BASE);
			break;
		case 2:
			BASE = new GMS(inputPair, _type);
			gamesPlayerMenu(BASE);
			break;
		case 3:
			BASE = new GC(inputPair, _type);
			generalCalculatorMenu(BASE);
			break;
		case 4:
		{
			if (_type == 1)
			{
				//����Ա���Human
				bool ret = this->addHuman();
				if (!ret)
				{
					std::cerr << "Human add failed!" << std::endl;
					system("pause");
					break;
				}
				std::cout << "Successfully added!" << std::endl;
				system("pause");
			}
			else
			{
				std::cerr << "Fault input ! Please input the choice again:" << std::endl;
				system("pause");
			}
			break;
		}
		case 5:
		{
			if (_type == 1)
			{
				//����Աɾ��Human
				bool ret = this->delHuman();
				if (!ret)
				{
					std::cerr << "Human delection failed!" << std::endl;
					system("pause");
					break;
				}
				std::cout << "Successfully deleted!" << std::endl;
				system("pause");
			}
			else
			{
				std::cerr << "Fault input ! Please input the choice again:" << std::endl;
				system("pause");
			}
			break;
		}
		case 0:
			return;
		default:
			std::cerr << "Fault input ! Please input the choice again:" << std::endl;
			system("pause");
			break;
		}
		if (Choice == 1 || Choice == 2 || Choice == 3 || Choice == 0)return;
		else if ((Choice == 4 || Choice == 5) && _type == 1)
		{
			system("cls");
			this->showCalMenu(_type);
			continue;
		}

	}

}

//����Ա�ڽ�������ѡ��˵�֮����Ӻ�ɾ���Ͳ���Human�Ĺ���
bool Admin::addHuman()
{
	std::vector<std::pair<std::string, std::string>>name_pwd_vec;
	std::string name_, PWD, justifyPWD;

	while (true)
	{
		system("cls");
		std::cout << "Please input the name :" << std::endl;
		std::cin >> name_;

		while (true)
		{
			std::cout << "Please input the password :" << std::endl;
			std::cin >> PWD;
			std::cout << "Please input the password again :" << std::endl;
			std::cin >> justifyPWD;
			if (justifyPWD != PWD)
			{
				std::cerr << "Passwords are NOT the same ! Please input the password again !" << std::endl;
				system("pause");
			}
			else
			{
				break;
			}
		}

		name_pwd_vec.emplace_back(std::make_pair(name_, PWD));
		std::cout << "Continue to add human?" << std::endl;
		std::cout << "1.Yes  2.No" << std::endl;
		int choice;
		std::cin >> choice;
		if (choice == 1)
		{
			continue;
		}
		else if (choice == 2)
		{
			break;
		}
		else
		{
			std::cerr << "Fault input ! Cease adding other people." << std::endl;
			system("pause");
			break;
		}
	}

	ofstream ofs(HUMAN_FILE, ios::app);
	if (!ofs.is_open())
	{
		std::cerr << HUMAN_FILE << " was NOT open!" << std::endl;
		return false;
	}
	for_each(name_pwd_vec.begin(), name_pwd_vec.end(), [&](const auto& pr) {
		ofs << pr.first << " " << pr.second << std::endl;
		});
	ofs.close();
	return true;
}
bool Admin::delHuman()
{
	system("cls");
	std::cout << "Please input the name of the human:" << std::endl;
	std::string name_;
	std::cin >> name_;
	bool ret = this->findHuman(name_);
	if (!ret)
	{
		std::cout << "No Human like such!" << std::endl;
		system("pause");
		return false;
	}
	std::ifstream file(HUMAN_FILE);
	std::vector<std::string> lines;
	std::string line;

	//��ȡ�ļ��е�ÿһ��
	while (getline(file, line)) {
		//������Ƿ����Ŀ������
		std::istringstream iss(line);
		std::string name, password;
		if (!(iss >> name >> password)) {
			continue; //�����ȡʧ�ܣ�������һ��
		}
		if (name != name_) {
			lines.push_back(line); //������ֲ�ƥ�䣬������һ��
		}
	}
	file.close();

	// ȥ������
	lines.erase(std::remove(lines.begin(), lines.end(), ""), lines.end());

	// ���޸ĺ������д���ļ�
	std::ofstream ofs(HUMAN_FILE);
	for (const auto& l : lines) {
		ofs << l << std::endl;
	}
	ofs.close();
	return true;
}
bool Admin::findHuman(const std::string& name_)
{
	std::vector<std::string>namevec;
	ifstream ifs(HUMAN_FILE, ios::in);
	if (!ifs.is_open())
	{
		std::cerr << HUMAN_FILE << " was NOT open!" << std::endl;
		return false;
	}
	std::string line, name, pwd;
	while (getline(ifs, line))
	{
		stringstream ss(line);
		ss >> name >> pwd;
		if (name == name_)
		{
			return true;
		}
	}
	ifs.close();
	return false;
}

//������̬�Ӳ˵����������ָ�룬������Ҫ��ʽת��Ϊ����
void Admin::generalCalculatorMenu(AbstractCalculator*& Base_general)
{
	try
	{
		GC* general = dynamic_cast<GC*>(Base_general);
		while (true)
		{
			system("cls");
			general->showMenu();
			/////
			std::cout << "The calculator is debugging!" << std::endl;
			/////
			int select;
			std::cin >> select;
			switch (select)
			{
			case 1:break;




			case 0://exit
			{
				return;
			}
			default:
				std::cerr << ERR_PHRASE << std::endl;
				system("pause");
				break;
			}
		}
	}
	catch (bad_cast& err)
	{
		std::cerr << "Fail casting to General Calculator!" << std::endl;
		return;
	}
}

void Admin::linearAlgebraCalculatorMenu(AbstractCalculator*& Base_linear)
{
	try
	{
		LAC* linear = dynamic_cast<LAC*>(Base_linear);
		while (true)
		{
			system("cls");
			//linear->__Soviet__();
			linear->showMenu();
			/*std::cout << "===================LINEAR ALGEBREA CALCULATOR=================" << std::endl;
			std::cout << "\t1.Show" << std::endl;
			std::cout << "\t2.Add" << std::endl;
			std::cout << "\t3.Delete" << std::endl;
			std::cout << "\t4.Clear" << std::endl;
			std::cout << "\t5.Search" << std::endl;
			std::cout << "\t6.Sort" << std::endl;
			std::cout << "\t7.Shuffle" << std::endl;
			std::cout << "\t8.Matrix Operations" << std::endl;
			std::cout << "\t9.Deteminant Operations" << std::endl;
			std::cout << "\t10.Linear System Operations" << std::endl;
			std::cout << "\t11.Basis Operations" << std::endl;
			std::cout << "\t0.Exit" << std::endl;*/
			int select;
			std::cin >> select;
			system("cls");
			switch (select)
			{
			case 1://show
			{
				linear->linearShow();
				break;
			}
			case 2://add
			{
				linear->linearAdd();
				break;
			}
			case 3://delete
			{
				linear->linearDelete();
				break;
			}
			case 4://clear
			{
				linear->linearClear();
				break;
			}
			case 5://searchItem
			{
				linear->linearSearch();
				break;
			}
			case 6://sort
			{
				linear->linearSort();
				break;
			}
			case 7://shuffle
			{
				linear->linearShuffle();
				break;
			}
			case 8://Matrix Operation
			{
				linear->linearMatrixFunc();
				break;
			}
			case 9://Determinant Operation
			{
				linear->linearDetFunc();
				break;
			}
			case 10://Linear System Operation
			{
				linear->linearSystemFunc();
				break;
			}
			case 11://11.Basis Operations
			{
				linear->linearBasisFunc();
				break;
			}
			case 0://exit
			{
				return;
			}
			default:
				std::cerr << ERR_PHRASE << std::endl;
				break;
			}
			system("pause");
			//�����
			linear->removeEmpty();
			//�����ļ�
			linear->saveFile();
		}
	}
	catch (bad_cast& err)
	{
		std::cerr << "Fail casting to Linear Algebra Calculator!" << std::endl;
		return;
	}
}

void Admin::gamesPlayerMenu(AbstractCalculator*& Base_calculus)
{
	try
	{
		GMS* calculus = dynamic_cast<GMS*>(Base_calculus);
		while (true)
		{
			system("cls");
			/*std::cout << "=========================GAMES===========================" << std::endl;
			std::cout << "\t1.Snake" << std::endl;
			std::cout << "\t0.Exit" << std::endl;*/
			calculus->showMenu();
			int select;
			std::cin >> select;
			switch (select)
			{
			case 1://Snake
			{
				Snake snk;

				while (true)
				{
					snk.playSnake();
					std::cout << "1.Once again  2.Exit" << std::endl;
					int choose;
					std::cin >> choose;
					if (choose == 1)
					{
						snk.resetGame();
						continue;
					}
					else if (choose == 2)break;
					else
					{
						std::cerr << ERR_PHRASE << std::endl;
					}
				}

				system("pause");
				break;
			}


			case 0://exit
			{
				return;
			}
			default:
				std::cerr << ERR_PHRASE << std::endl;
				system("pause");
				break;
			}
		}
	}
	catch (bad_cast& err)
	{
		std::cerr << "Fail casting to Games!" << std::endl;
		return;
	}
}
