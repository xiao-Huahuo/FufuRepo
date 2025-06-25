#include"LinearAlgebraCalculator.h"
#include<vector>
#include<algorithm>
#include<tuple>
#include<cmath>
#include<fstream>
#include<sstream>
using namespace std;

////1.矩阵；2.行列式；3.线性方程组
//std::vector<std::shared_ptr<Matrix>>matrixVector_;//存放矩阵的智能指针数组
//std::vector<std::shared_ptr<Det>>detVector_;//存放行列式的智能指针数组
//std::vector<std::shared_ptr<LinearSystem>>systemVector_;//存放线性方程组的数组
//std::vector<std::shared_ptr<Basis>>basisVector_;//存放基的数组
//std::string name_;
//std::string password_;
//int persontype_;

//人类至高无上的理想
void LAC::__Soviet__()
{
	std::cout << "□□□□□□□□□□□◥▇▅□□□□□" << std::endl;
	std::cout << "□□□□□◢■■■■◤□■██□□□□" << std::endl;
	std::cout << "□   □□◢████◤□□□□███□□" << std::endl;
	std::cout << " □   □◢█████◣□□□□   ██▋□" << std::endl;
	std::cout << " □   □◥██◤◥██◣□□□   ██▋□" << std::endl;
	std::cout << "□□□□□□□□◥██◣□□███□□ " << std::endl;
	std::cout << "□□◢◣□□  □□□◥██◣◢██□□" << std::endl;
	std::cout << " □□◥██◣□□□□□◥████□□□ " << std::endl;
	std::cout << "□◢█■███▇▇▇▇▇▇███◣□□" << std::endl;
	std::cout << "◢█◤□□□◥█████◤□◥██◣□" << std::endl;
	std::cout << "█◤□□□□□□□□□□□□□  ◥█◤" << std::endl;
}

// 保存矩阵到文件
void LAC::saveMatrix()
{
	std::ofstream ofs(MATRIX_FILE);

	if (!ofs.is_open())
	{
		std::cerr << "Unable to open file for writing matrices." << std::endl;
		return;
	}

	for (auto& p_matrix : matrixVector_)
	{
		Matrix matrix = *p_matrix;
		if (matrix == Matrix())continue;

		// 首先写入行数和列数
		ofs << matrix.getRow() << " " << matrix.getColumn() << std::endl;

		// 然后写入矩阵的所有元素
		for (int i = 0; i < matrix.getRow(); ++i)
		{
			for (int j = 0; j < matrix.getColumn(); ++j)
			{
				ofs << matrix[i][j] << " ";
			}
			ofs << std::endl;
		}
	}

	ofs.close();
}
// 从文件读取矩阵
void LAC::readMatrixFromFile()
{
	std::ifstream ifs(MATRIX_FILE);

	if (!ifs.is_open())
	{
		std::cerr << "Unable to open file for reading matrices." << std::endl;
		return;
	}

	matrixVector_.clear(); // 清空现有的矩阵列表

	// 循环读取每个矩阵
	while (!ifs.eof())
	{ // 使用eof()检查是否到达文件末尾
		int _row, _column;
		if (ifs >> _row >> _column)
		{ // 如果能够读取行数和列数
			if (_row <= 0 || _column <= 0)continue;
			// 创建一个新的矩阵
			Matrix matrix(_row, _column);

			// 读取矩阵的每一行
			for (int i = 0; i < _row; ++i)
			{
				for (int j = 0; j < _column; ++j)
				{
					ifs >> matrix[i][j];
				}
			}

			// 将矩阵添加到所有矩阵中
			this->addItem(matrix, this->matVecSize());
		}
	}

	ifs.close();
}
// 保存行列式到文件
void LAC::saveDet()
{
	std::ofstream ofs(DET_FILE);

	if (!ofs.is_open())
	{
		std::cerr << "Unable to open file for writing determinants." << std::endl;
		return;
	}

	for (auto& p_det : detVector_)
	{
		Det det = *p_det;
		if (det == Det())continue;

		// 首先写入阶数和首数字
		ofs << det.getOrder() << " " << det.getPreNum() << std::endl;

		// 然后写入行列式的所有元素
		for (int i = 0; i < det.getOrder(); ++i)
		{
			for (int j = 0; j < det.getOrder(); ++j)
			{
				ofs << det[i][j] << " ";
			}
			ofs << std::endl;
		}
	}

	ofs.close();
}
// 从文件读取行列式
void LAC::readDetFromFile() {
	std::ifstream ifs(DET_FILE);

	if (!ifs.is_open()) {
		std::cerr << "Unable to open file for reading determinants." << std::endl;
		return;
	}

	detVector_.clear(); // 清空现有的行列式列表

	// 循环读取每个行列式
	while (!ifs.eof())
	{ // 使用eof()检查是否到达文件末尾
		int order;
		double prenum;
		if (ifs >> order >> prenum)
		{ // 如果能够读取行数和列数
			if (order <= 0)continue;

			// 创建一个新的行列式
			Det det(order, prenum);

			// 读取行列式的每一行
			for (int i = 0; i < order; ++i)
			{
				for (int j = 0; j < order; ++j)
				{
					ifs >> det[i][j];
				}
			}

			// 将行列式添加到所有行列式中
			this->addItem(det, this->detVecSize());
		}
	}

	ifs.close();
}
// 保存线性方程组到文件
void LAC::saveLinearSystem()
{
	std::ofstream ofs(LINEARSYSTEM_FILE);

	if (!ofs.is_open())
	{
		std::cerr << "Unable to open file for writing linear systems." << std::endl;
		return;
	}

	for (auto& p_system : systemVector_)
	{
		LinearSystem _system = *p_system;
		Matrix A = _system.getA();
		Matrix B = _system.getB();
		if (A == Matrix() || B == Matrix() || _system == LinearSystem())continue;

		// 首先写入A的行数和(A的列数+1)
		ofs << A.getRow() << " " << (A.getColumn() + 1) << std::endl;

		// 然后写入A和B的所有元素
		for (int i = 0; i < A.getRow(); ++i)
		{
			for (int j = 0; j < A.getColumn(); ++j)
			{
				ofs << A[i][j] << " ";
			}
			// 写入B的对应元素
			ofs << B[i][0] << std::endl;
		}
	}

	ofs.close();
}
// 从文件读取线性方程组
void LAC::readLinearSystemFromFile()
{
	std::ifstream ifs(LINEARSYSTEM_FILE);

	if (!ifs.is_open())
	{
		std::cerr << "Unable to open file for reading linear systems." << std::endl;
		return;
	}

	systemVector_.clear(); // 清空现有的线性方程组列表

	// 循环读取每个线性方程组
	while (!ifs.eof())
	{ // 使用eof()检查是否到达文件末尾
		int Arow, Acol;
		if (ifs >> Arow >> Acol)
		{ // 如果能够读取行数和列数
			Acol--;
			if (Arow <= 0 || Acol <= 0)continue;
			//创建A和B
			Matrix A(Arow, Acol), B(Arow, 1);

			// 读取线性方程组的每一行
			for (int i = 0; i < Arow; ++i)
			{
				for (int j = 0; j < Acol; ++j)
				{
					ifs >> A[i][j];
				}
				ifs >> B[i][0];
			}

			// 创建一个新的线性方程组
			LinearSystem linear(A, B);

			// 将线性方程组添加到所有线性方程组中
			this->addItem(linear, this->sysVecSize());
		}
	}

	ifs.close();
}
// 保存基到文件
void LAC::saveBasis()
{
	std::ofstream ofs(BASIS_FILE);

	if (!ofs.is_open())
	{
		std::cerr << "Unable to open file for writing bases." << std::endl;
		return;
	}

	for (auto& p_basis : basisVector_)
	{
		Basis basis = *p_basis;
		if (basis == Basis())continue;
		// 首先写入基的行数和基的数量
		ofs << basis.at(0).size() << " " << basis.size() << std::endl;

		//合并基
		Matrix temp_mat = this->M_mergeBasis(basis);
		ContentVec temp_blk = temp_mat.getValueVec();

		// 然后写入temp_blk的元素
		for (auto& row : temp_blk)
		{
			for (auto& val : row)
			{
				ofs << val << " ";
			}
			ofs << std::endl;
		}
	}

	ofs.close();
}
// 从文件读取基
void LAC::readBasisFromFile() {
	std::ifstream ifs(BASIS_FILE);

	if (!ifs.is_open()) {
		std::cerr << "Unable to open file for reading bases." << std::endl;
		return;
	}

	basisVector_.clear(); // 清空现有的基列表

	// 循环读取每个矩阵
	while (!ifs.eof())
	{ // 使用eof()检查是否到达文件末尾
		int _row, _column;
		if (ifs >> _row >> _column)
		{ // 如果能够读取行数和列数
			if (_row <= 0 || _column <= 0)continue;
			// 创建一个新的矩阵
			Matrix matrix(_row, _column);

			// 读取矩阵的每一行
			for (int i = 0; i < _row; ++i)
			{
				for (int j = 0; j < _column; ++j)
				{
					ifs >> matrix[i][j];
				}
			}

			Basis basis = this->M_takeBasis(matrix, true);

			if (basis == Basis())continue;

			// 将基添加到所有基中
			this->addItem(basis, this->basisVecSize());
		}
	}

	ifs.close();
}
// 保存矩阵、行列式、线性方程组、基到文件
void LAC::saveFile() {
	this->saveMatrix();
	this->saveDet();
	this->saveLinearSystem();
	this->saveBasis();
}
// 从文件中读取矩阵、行列式、线性方程组、基
void LAC::readFile() {
	this->readMatrixFromFile();
	this->readDetFromFile();
	this->readLinearSystemFromFile();
	this->readBasisFromFile();
}



//返回矩阵容器大小
int LAC::matVecSize() const { return this->getMatVec().size(); }
//返回行列式容器大小
int LAC::detVecSize()const { return this->getDetVec().size(); }
//返回线性方程组容器大小
int LAC::sysVecSize()const { return this->getSysVec().size(); }
//返回基容器大小
int LAC::basisVecSize()const { return this->getBasisVec().size(); }

//根据索引展示
void LAC::showMatVec(int index)
{
	if (index < 0 || index >= this->matVecSize())return;
	this->show(*(this->getMatVec().at(index)));
}
//根据索引展示
void LAC::showDetVec(int index)
{
	if (index < 0 || index >= this->detVecSize())return;
	this->show(*(this->getDetVec().at(index)));
}
//根据索引展示
void LAC::showSysVec(int index)
{
	if (index < 0 || index >= this->sysVecSize())return;
	this->show(*(this->getSysVec().at(index)));
}
//根据索引展示
void LAC::showBasisVec(int index)
{
	if (index < 0 || index >= this->basisVecSize())return;
	this->show(*this->getBasisVec().at(index));
}

//构造函数：传入MessagePair（名字和密码的对组）
LAC::LAC(const MessagePair& inputPair, int _type) :name_(inputPair.first), password_(inputPair.second), persontype_(_type)
{
	this->matrixVector_.emplace_back(make_shared<Matrix>(3, 3, ContentVec{
		{1,2,3},
		{2,3,4},
		{3,4,5}
		}));
	this->matrixVector_.emplace_back(make_shared<Matrix>(3, 3, ContentVec{
		{2,4,8},
		{1,2,2},
		{0,5,3}
		}));
	this->matrixVector_.emplace_back(make_shared<Matrix>(3, 3, ContentVec{
		{1,0,0},
		{0,1,0},
		{0,0,1}
		}));
	this->detVector_.emplace_back(make_shared<Det>(3, ContentVec{
		{1,2,3},
		{2,3,4},
		{3,4,5}
		}, 2));
	this->detVector_.emplace_back(make_shared<Det>(3, ContentVec{
		{2,4,8},
		{1,2,2},
		{0,5,3}
		}, 2));
	this->detVector_.emplace_back(make_shared<Det>(4, ContentVec{
		{1,0,0,2},
		{0,1,0,2},
		{0,0,1,2},
		{0,0,0,2}
		}, 2));
	this->systemVector_.emplace_back(make_shared<LinearSystem>(
		Matrix(3, 3, ContentVec{
			{1,0,3},
			{0,1,5},
			{0,0,0}
			}),
		Matrix(3, 1, ContentVec{
			{4},
			{6},
			{0}
			})
	));
	this->systemVector_.emplace_back(make_shared<LinearSystem>(
		Matrix(4, 4, ContentVec{
			{1,4,8,1},
			{0,2,2,2},
			{0,0,3,3},
			{0,0,0,1}
			}),
		Matrix(4, 1, ContentVec{
			{1},
			{2},
			{3},
			{4}
			})
	));
	this->systemVector_.emplace_back(make_shared<LinearSystem>
		(
			Matrix(4, 4, ContentVec{
				{1,0,0,3},
				{0,1,0,1},
				{0,0,1,2},
				{0,0,0,1}
				}),
			Matrix(4, 1, ContentVec{
				{0},
				{0},
				{0},
				{0}
				})
		));
	this->systemVector_.emplace_back(make_shared<LinearSystem>
		(
			Matrix(4, 4, ContentVec{
				{1,0,0,0},
				{0,2,0,0},
				{0,0,3,0},
				{0,0,0,0}
				}),
			Matrix(4, 1, ContentVec{
				{1},
				{2},
				{3},
				{0}
				})
		));

	// 创建一个 ContentVec 的 vector
	Basis basis1
	{
		ContentVec{ {1}, {2}, {0} },
		ContentVec{ {0}, {1}, {0} },
		ContentVec{ {0}, {1}, {1} }
	};
	this->basisVector_.emplace_back(make_shared<Basis>(basis1));

	Basis basis2
	{
		ContentVec{ {1}, {3}, {2} },
		ContentVec{ {3}, {4}, {1} },
		ContentVec{ {2}, {1}, {1} }
	};
	this->basisVector_.emplace_back(make_shared<Basis>(basis2));

	//读取文件
	this->readFile();

}
//析构函数
LAC::~LAC()
{
	//保存代码到文件
	this->saveFile();
}

//获取private的接口

//获取矩阵的智能指针数组
const std::vector<std::shared_ptr<Matrix>>& LAC::getMatVec() const {
	return ref(matrixVector_);
}
//获取行列式的智能指针数组
const std::vector<std::shared_ptr<Det>>& LAC::getDetVec() const {
	return ref(detVector_);
}
//获取线性方程组的智能指针数组
const std::vector<std::shared_ptr<LinearSystem>>& LAC::getSysVec() const {
	return ref(systemVector_);
}
//获取基的智能指针数组
const std::vector <std::shared_ptr<Basis>>& LAC::getBasisVec()const {
	return ref(basisVector_);
}

//多态菜单
void LAC::showMenu()
{
	std::cout << "\t\t===================LINEAR ALGEBREA CALCULATOR=================" << std::endl;
	std::cout << "\t\t|                           1.Show                           |" << std::endl;
	std::cout << "\t\t|                           2.Add                            |" << std::endl;
	std::cout << "\t\t|                           3.Delete                         |" << std::endl;
	std::cout << "\t\t|                           4.Clear                          |" << std::endl;
	std::cout << "\t\t|                           5.Search                         |" << std::endl;
	std::cout << "\t\t|                           6.Sort                           |" << std::endl;
	std::cout << "\t\t|                           7.Shuffle                        |" << std::endl;
	std::cout << "\t\t|                      8.Matrix Operations                   |" << std::endl;
	std::cout << "\t\t|                    9.Deteminant Operations                 |" << std::endl;
	std::cout << "\t\t|                  10.Linear System Operations               |" << std::endl;
	std::cout << "\t\t|                      11.Basis Operations                   |" << std::endl;
	std::cout << "\t\t|                           0.Exit                           |" << std::endl;
	std::cout << "\t\t==============================================================" << std::endl;
}

//多态子菜单用户交互函数

//显示当前各个容器含内容数量
std::tuple<int, int, int, int> LAC::showContainerStatement(const std::string& phrase)
{
	int matNum = this->matVecSize(), detNum = this->detVecSize(), sysNum = this->sysVecSize(), basisNum = this->basisVecSize();
	if (matNum == 0 && detNum == 0 && sysNum == 0 && basisNum == 0)
	{
		std::cout << "NONE!" << std::endl;
		return std::make_tuple(matNum, detNum, sysNum, basisNum);
	}
	std::cout << "Present Number in containers:" << std::endl;
	std::cout << "Matrix : " << matNum << std::endl
		<< "Det : " << detNum << std::endl
		<< "Linear System : " << sysNum << std::endl
		<< "Basis :" << basisNum << std::endl;
	std::cout << "What kind do you want to " << phrase << " ?" << std::endl;
	std::cout << "1.Matrix  2.Det  3.Linear System 4.Basis" << std::endl;
	return std::make_tuple(matNum, detNum, sysNum, basisNum);
}
//多态子菜单--show
void LAC::linearShow()
{
	std::tuple<int, int, int, int> num_tuple = this->showContainerStatement("show");
	if (std::get<0>(num_tuple) == 0 && std::get<1>(num_tuple) == 0 && std::get<2>(num_tuple) == 0 && std::get<3>(num_tuple) == 0)
	{
		return;
	}
	int choice;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
	{
		if (std::get<0>(num_tuple) == 0)
		{
			std::cout << "NONE!" << std::endl;
		}
		else
		{
			this->show(1);
		}
		break;
	}
	case 2:
	{
		if (std::get<1>(num_tuple) == 0)
		{
			std::cout << "NONE!" << std::endl;
		}
		else
		{
			this->show(2);
		}
		break;
	}
	case 3:
	{
		if (std::get<2>(num_tuple) == 0)
		{
			std::cout << "NONE!" << std::endl;
		}
		else
		{
			this->show(3);
		}
		break;
	}
	case 4:
	{
		if (std::get<3>(num_tuple) == 0)
		{
			std::cout << "NONE!" << std::endl;
		}
		else
		{
			this->show(4);
		}
		break;
	}
	default:
		std::cerr << ERR_PHRASE << std::endl;
		break;
	}

	return;
}
//根据用户输入传出ContentVec和插入索引（左边插入）
std::tuple<ContentVec, int> LAC::allocateContent(int _type, int row_, int column_)
{
	std::vector<std::string> namearr = { "matrix","det","linear system","basis" };
	std::string name_ = namearr.at(_type - 1);
	std::cout << name_;
	int present_container_number = 0;
	if (_type == 1)
	{
		present_container_number = this->matVecSize();
	}
	else if (_type == 2)
	{
		present_container_number = this->detVecSize();
	}
	else if (_type == 3)
	{
		present_container_number = this->sysVecSize();
	}
	else if (_type == 4)
	{
		present_container_number = this->basisVecSize();
	}


	ContentVec inputblock(row_, std::vector<double>(column_, 0));
	if (_type != 3)//线性方程组需要输入A和B，放在子菜单函数里面了
	{
		std::cout << "Input numbers below:" << std::endl;
		for (int i = 0; i < row_; i++)
		{
			std::cout << "Row " << i + 1 << ":  ";
			for (int j = 0; j < column_; j++)
			{
				std::cin >> inputblock[i][j];
			}
			std::cout << std::endl;
		}
	}

	int insertplace = present_container_number;//默认在最后边
	//如果不是新添加一个，可以指定位置，用户输入用户索引，变为索引后，在索引的左边插入
	bool is_specified = false;
	if (present_container_number != 0)
	{
		std::cout << "Whether to specify an index ? (If Not,the " << name_ << " will be put at the end of container)" << std::endl;
		std::cout << "1.No  2.Yes" << std::endl;
		int spe_choice;
		std::cin >> spe_choice;
		if (spe_choice == 1)
		{
			std::cout << "The " << name_ << " will be put at the end of container ." << std::endl;
		}
		else if (spe_choice == 2)
		{
			//指定位置
			std::system("cls");
			std::cout << "Present " << name_ << "s are below:" << std::endl;
			this->show(_type);
			std::cout << "Please chooce the place before which your " << name_ << " will be inserted ." << std::endl;

			std::cin >> insertplace;
			if (insertplace <= 0 || insertplace > present_container_number)
			{
				std::cerr << "Out of range ! The " << name_ << " will be put at the end of container ." << std::endl;
			}
			else
			{
				insertplace--;//变为索引
				is_specified = true;
			}
		}
		else
		{
			std::cerr << "Fault input ! The " << _type << " will be put at the end of container ." << std::endl;
		}

	}
	else
	{
		//如果是新添加一个，则直接传出0
		return std::make_tuple(inputblock, 0);
	}

	if (!is_specified)
	{
		//如果没有指定一个索引则需要转为索引
		insertplace--;//变为索引
	}

	return std::make_tuple(inputblock, insertplace);
}
//多态子菜单--add
void LAC::linearAdd()
{
	std::cout << "Please input the type you want to add in :" << std::endl;
	std::cout << "1.Matrix  2.Det  3.LinearSystem	4.Basis" << std::endl;

	int choice = 0;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
	{
		std::cout << "Input row and column below:" << std::endl;
		int row_, column_;
		while (true)
		{
			std::cin >> row_ >> column_;
			if (row_ <= 0 || column_ <= 0)
			{
				std::cerr << ERR_PHRASE << std::endl;
				return;
			}

			break;
		}

		Matrix add_mat(row_, column_);

		std::tuple<ContentVec, int> block_and_index = this->allocateContent(1, row_, column_);

		add_mat.setContentVec(std::get<0>(block_and_index));

		bool ret = this->addItem(add_mat, std::get<1>(block_and_index));
		if (!ret)
		{
			std::cerr << "Add was failed!" << std::endl;
			break;
		}
		std::cout << "Successfully input!" << std::endl;
		break;
	}
	case 2:
	{
		std::cout << "Input order below:" << std::endl;
		int order_;
		double prenum;
		while (true)
		{
			std::cin >> order_;
			if (order_ <= 0)
			{
				std::cerr << ERR_PHRASE << std::endl;
				return;
			}

			break;
		}
		std::cout << "Input the number premier your det:" << std::endl;
		std::cin >> prenum;
		Det add_det(order_, prenum);

		std::tuple<ContentVec, int> block_and_index = this->allocateContent(2, order_, order_);

		add_det.setContentVec(std::get<0>(block_and_index));

		bool ret = this->addItem(add_det, std::get<1>(block_and_index));
		if (!ret)
		{
			std::cerr << "Add was failed!" << std::endl;
			break;
		}
		std::cout << "Successfully input!" << std::endl;
		break;
	}
	case 3:
	{
		int row_, column_;
		//输入A
		std::cout << "Input row and column of A below:" << std::endl;
		while (true)
		{
			std::cin >> row_ >> column_;
			if (row_ <= 0 || column_ <= 0)
			{
				std::cerr << ERR_PHRASE << std::endl;
				return;
			}
			break;
		}
		Matrix matA(row_, column_);
		std::cout << "Input numbers of A below:" << std::endl;
		for (int i = 0; i < row_; i++)
		{
			std::cout << "Row " << i + 1 << ":  ";
			for (int j = 0; j < column_; j++)
			{
				std::cin >> matA[i][j];
			}
			std::cout << std::endl;
		}
		//输入B
		Matrix matB(row_, 1);
		std::cout << "Input numbers of B below:" << std::endl;
		for (int i = 0; i < row_; i++)
		{
			std::cout << "Row " << i + 1 << ":  ";
			std::cin >> matB[i][0];
			std::cout << std::endl;
		}

		LinearSystem add_system(matA, matB);

		std::tuple<ContentVec, int> block_and_index = this->allocateContent(3, row_ + 1, column_);

		bool ret = this->addItem(add_system, std::get<1>(block_and_index));
		if (!ret)
		{
			std::cerr << "Add was failed!" << std::endl;
			break;
		}
		std::cout << "Successfully input!" << std::endl;

		break;
	}
	case 4:
	{
		std::cout << "Input row and column below:" << std::endl;
		int row_, column_;
		while (true)
		{
			std::cin >> row_ >> column_;
			if (row_ <= 0 || column_ <= 0)
			{
				std::cerr << ERR_PHRASE << std::endl;
				return;
			}

			break;
		}

		Matrix add_mat(row_, column_);

		std::tuple<ContentVec, int> block_and_index = this->allocateContent(4, row_, column_);

		add_mat.setContentVec(std::get<0>(block_and_index));

		Basis result_basis = this->M_takeBasis(add_mat, true);

		if (result_basis == Basis())
		{
			std::cerr << "Add was failed!" << std::endl;
			break;
		}
		bool ret = this->addItem(result_basis, std::get<1>(block_and_index));
		if (!ret)
		{
			std::cerr << "Add was failed!" << std::endl;
			break;
		}
		std::cout << "Successfully input!" << std::endl;
		break;
	}
	default:
		std::cerr << ERR_PHRASE << std::endl;
		break;
	}
}
//删除函数的分支
void LAC::delFunc(int tuplenum, int _type)
{
	std::vector<std::string> namearr = { "matrix","det","linear system","basis" };
	std::string name_ = namearr.at(_type - 1);

	if (tuplenum == 0)
	{
		std::cerr << "There is No " << name_ << " that you can delete !" << std::endl;
		std::system("pause");
		return;
	}

	this->show(_type);
	std::cout << "Please input the index , and the " << name_ << " which has the index will be deleted.(If 0 inputed , you will exit.)" << std::endl;
	int delindex;
	std::cin >> delindex;
	if (delindex < 0 || delindex > tuplenum)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	else if (delindex == 0)
	{
		return;
	}
	delindex--;//变为索引

	std::cout << "Please input the number that you want to delete after this (including this , if 0 inputed ,you will exit.):" << std::endl;
	int delnum;
	std::cin >> delnum;
	if (delnum < 0 || delnum > tuplenum - delindex)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	else if (delnum == 0)
	{
		return;
	}

	bool ret = this->deleteItem(_type, delindex, delnum);
	if (!ret)
	{
		std::cerr << "Deletion was failed!" << std::endl;
		return;
	}
	std::cout << "Successfully deleted!" << std::endl;
}
//多态子菜单--delete
void LAC::linearDelete()
{
	std::tuple<int, int, int, int> num_tuple = this->showContainerStatement("delete");
	if (std::get<0>(num_tuple) == 0 && std::get<1>(num_tuple) == 0 && std::get<2>(num_tuple) == 0 && std::get<3>(num_tuple) == 0)
	{
		return;
	}

	int choice;
	std::cin >> choice;
	std::system("cls");
	switch (choice)
	{
	case 1:
	{
		int tuplenum = std::get<0>(num_tuple);
		this->delFunc(tuplenum, 1);
		break;
	}
	case 2:
	{
		int tuplenum = std::get<1>(num_tuple);
		this->delFunc(tuplenum, 2);
		break;
	}
	case 3:
	{
		int tuplenum = std::get<2>(num_tuple);
		this->delFunc(tuplenum, 3);
		break;
	}
	case 4:
	{
		int tuplenum = std::get<3>(num_tuple);
		this->delFunc(tuplenum, 4);
		break;
	}
	default:
		std::cerr << ERR_PHRASE << std::endl;
		break;
	}

}
//多态子菜单--clear
void LAC::linearClear()
{
	std::cout << "Please choose the container that you want to clear:" << std::endl;
	std::cout << "1.Matrix  2.Det  3.Linear System  4.Basis" << std::endl;
	int choice_vec;
	std::cin >> choice_vec;
	if (choice_vec == 1 || choice_vec == 2 || choice_vec == 3 || choice_vec == 4)
	{
		std::cout << "Sure clearing?" << std::endl;
		std::cout << "1.Yes  2.No" << std::endl;
		int	choice;
		std::cin >> choice;
		if (choice == 1)
		{
			switch (choice_vec)
			{
			case 1:
				this->clearItem(1);
				break;
			case 2:
				this->clearItem(2);
				break;
			case 3:
				this->clearItem(3);
				break;
			case 4:
				this->clearItem(4);
				break;
			default:
				break;
			}
			std::cout << "Successfully cleared!" << std::endl;
		}
		else if (choice == 2)
		{
			std::cout << "Operation has been withdrawn." << std::endl;
		}
		else
		{
			std::cerr << ERR_PHRASE << std::endl;
		}
	}
	else
	{
		std::cerr << ERR_PHRASE << std::endl;
	}

}
//选择函数的分支
int LAC::chooseSearch(int tuplenum, int _type)
{
	std::vector<std::string> namearr = { "matrix","det","linear system","basis" };
	std::string name_ = namearr.at(_type - 1);

	int search_index = -1;
	if (tuplenum == 0)
	{
		std::cout << "No " << name_ << " can you searchItem!" << std::endl;
		return -1;
	}
	std::system("cls");
	std::cout << "By which approach do you searchItem?" << std::endl;
	std::cout << "1.Search by content " << (name_ == "linear system" ? "of A" : "") << std::endl
		<< "2.Search by first value " << (name_ == "linear system" ? "of A" : "") << std::endl
		<< "3.Search by " << (name_ == "matrix" ? "row and column " : "order ") << (name_ == "linear system" ? "of A" : "") << std::endl;
	int approach;
	std::cin >> approach;
	switch (approach)
	{
	case 1://Search by content
	{
		std::cout << "Please input " << (name_ == "matrix" ? "row and column " : "order ") << " of " << (name_ == "linear system" ? "A" : ("the " + name_)) << " :" << std::endl;
		int row_ = 1, column_ = 1, order_ = 1;
		if (_type == 1 || _type == 3 || _type == 4)
		{
			std::cin >> row_ >> column_;
		}
		else if (_type == 2)
		{
			std::cin >> order_;
			row_ = order_;
			column_ = order_;
		}

		if (row_ <= 0 || column_ <= 0)
		{
			std::cerr << ERR_PHRASE << std::endl;
			break;
		}
		ContentVec search_block(row_, std::vector<double>(column_, 0));

		std::cout << "Please input content" << (name_ == "linear system" ? "of A" : "") << " below:" << std::endl;
		for (int i = 0; i < row_; i++)
		{
			std::cout << "Row" << i + 1 << ":";
			for (int j = 0; j < column_; j++)
			{
				std::cin >> search_block[i][j];
			}
			std::cout << std::endl;
		}
		//查找
		search_index = this->searchItem(_type, search_block);

		break;
	}
	case 2://Search by first value
	{
		std::cout << "Please input the first value of " << (name_ == "linear system" ? "A" : ("the " + name_)) << " :" << std::endl;
		double firstval;
		std::cin >> firstval;
		search_index = this->searchItem(_type, firstval);

		break;
	}
	case 3://Search by row and column
	{
		std::cout << "Please input " << (name_ == "matrix" ? "row and column " : "order ") << " of " << (name_ == "linear system" ? "A" : ("the " + name_)) << " :" << std::endl;
		int row_ = 1, column_ = 1, order_ = 1;
		if (_type == 1 || _type == 3 || _type == 4)
		{
			std::cin >> row_ >> column_;
		}
		else if (_type == 2)
		{
			std::cin >> order_;
			row_ = order_;
			column_ = order_;
		}

		if (row_ <= 0 || column_ <= 0)
		{
			std::cerr << ERR_PHRASE << std::endl;
			break;
		}
		search_index = this->searchItem(_type, row_, column_);

		break;
	}
	default:
		std::cerr << ERR_PHRASE << std::endl;
		break;
	}

	if (search_index == -1)
	{
		std::cout << "NO " << name_ << " like the one you provided." << std::endl;
	}
	return search_index;
}
//多态子菜单--searchItem
void LAC::linearSearch()
{
	std::tuple<int, int, int, int> num_tuple = this->showContainerStatement("searchItem");
	if (std::get<0>(num_tuple) == 0 && std::get<1>(num_tuple) == 0 && std::get<2>(num_tuple) == 0 && std::get<3>(num_tuple) == 0)
	{
		return;
	}
	int choice;
	int search_index = -1;
	int tuplenum = 0;

	std::cin >> choice;
	std::system("cls");
	switch (choice)
	{
	case 1://Matrix
	{
		tuplenum = std::get<0>(num_tuple);
		search_index = this->chooseSearch(tuplenum, 1);
		if (search_index == -1)
		{
			break;
		}
		std::cout << "Successfully found!\nThe matrix that fits your description is below:" << std::endl;
		this->showMatVec(search_index);

		break;
	}
	case 2://Det
	{
		tuplenum = std::get<1>(num_tuple);
		search_index = this->chooseSearch(tuplenum, 2);
		if (search_index == -1)
		{
			break;
		}
		std::cout << "Successfully found!\nThe det that fits your description is below:" << std::endl;
		this->showDetVec(search_index);

		break;
	}
	case 3://Linear System
	{
		tuplenum = std::get<2>(num_tuple);
		search_index = this->chooseSearch(tuplenum, 3);
		if (search_index == -1)
		{
			break;
		}
		std::cout << "Successfully found!\nThe linear system that fits your description is below:" << std::endl;
		this->showSysVec(search_index);

		break;
	}
	case 4://Basis
	{
		tuplenum = std::get<3>(num_tuple);
		search_index = this->chooseSearch(tuplenum, 4);
		if (search_index == -1)
		{
			break;
		}
		std::cout << "Successfully found!\nThe basis that fits your description is below:" << std::endl;
		this->showBasisVec(search_index);

		break;
	}
	default:
		std::cerr << ERR_PHRASE << std::endl;
		break;
	}
}
//选择排序方法
void LAC::chooseSort(int tuplenum, int _type)
{
	std::vector<std::string> namearr = { "matrix","det","linear system","basis" };
	std::string name_ = namearr.at(_type - 1);

	if (tuplenum == 0)
	{
		std::cout << "No " << name_ << " can you sort!" << std::endl;
		return;
	}

	std::cout << "By what approach do you want?" << std::endl;
	std::cout << "1.Sort by first value  2.Sort by size" << std::endl;
	int select;
	std::cin >> select;
	switch (select)
	{
	case 1:
	{
		std::cout << "Greater or lower?" << std::endl;
		std::cout << "1.Greater  2.Lower" << std::endl;
		int order;
		std::cin >> order;
		if (order == 1)
		{
			this->firstValSort(_type, true);
		}
		else if (order == 2)
		{
			this->firstValSort(_type, false);
		}
		else
		{
			std::cerr << ERR_PHRASE << std::endl;
			break;
		}

		break;
	}
	case 2:
	{
		std::cout << "Greater or lower?" << std::endl;
		std::cout << "1.Greater  2.Lower" << std::endl;
		int order;
		std::cin >> order;
		if (order == 1)
		{
			this->blockSizeSort(_type, true);
		}
		else if (order == 2)
		{
			this->blockSizeSort(_type, false);
		}
		else
		{
			std::cerr << ERR_PHRASE << std::endl;
			break;
		}

		break;
	}
	default:
		std::cerr << ERR_PHRASE << std::endl;
		break;
	}
	std::cout << "Successfully sorted!" << std::endl;
	std::system("pause");
	std::system("cls");
	std::cout << name_ << "s after sorting are below:" << std::endl;
	this->show(_type);
}
//多态子菜单--Sort
void LAC::linearSort()
{
	std::tuple<int, int, int, int> num_tuple = this->showContainerStatement("sort");
	if (std::get<0>(num_tuple) == 0 && std::get<1>(num_tuple) == 0 && std::get<2>(num_tuple) == 0 && std::get<3>(num_tuple) == 0)
	{
		return;
	}
	int choice;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
	{
		int tuplenum = std::get<0>(num_tuple);
		this->chooseSort(tuplenum, 1);
		break;
	}
	case 2:
	{
		int tuplenum = std::get<1>(num_tuple);
		this->chooseSort(tuplenum, 2);
		break;
	}
	case 3:
	{
		int tuplenum = std::get<2>(num_tuple);
		this->chooseSort(tuplenum, 3);
		break;
	}
	case 4:
	{
		int tuplenum = std::get<3>(num_tuple);
		this->chooseSort(tuplenum, 4);
		break;
	}
	default:
		std::cerr << ERR_PHRASE << std::endl;
		break;
	}

}
//多态子菜单--Shuffle
void LAC::linearShuffle()
{
	std::tuple<int, int, int, int> num_tuple = this->showContainerStatement("shuffle");
	if (std::get<0>(num_tuple) == 0 && std::get<1>(num_tuple) == 0 && std::get<2>(num_tuple) == 0 && std::get<3>(num_tuple) == 0)
	{
		return;
	}
	int choice_container;
	std::cin >> choice_container;
	if (choice_container <= 0 || choice_container > 3)
	{
		std::cerr << ERR_PHRASE << std::endl;
	}
	else
	{
		std::cout << "Sure shuffling?" << std::endl;
		std::cout << "1.Yes  0.No" << std::endl;
		int choice;
		std::cin >> choice;
		if (choice == 1)
		{
			this->shuffleItem(choice_container);
			std::cout << "Successfully shuffled!" << std::endl;
		}
		else if (choice == 0)
		{
			std::cout << "Operation has been withdrawn." << std::endl;
		}
		else
		{
			std::cerr << ERR_PHRASE << std::endl;
		}
	}

}
//矩阵功能子菜单中的专有操作
void LAC::linearMatrixFunc()
{
	try
	{
		system("cls");
		if (this->matVecSize() == 0)
		{
			std::cout << "NONE!" << std::endl;
			return;
		}
		this->show(1);
		std::cout << "Which matrix do you want to operate?" << std::endl;
		int index;
		std::cin >> index;
		if (index <= 0 || index > this->matVecSize())
		{
			std::cerr << ERR_PHRASE << std::endl;
			return;
		}
		index--;//变为索引

		while (true)
		{
			//展示矩阵操作菜单
			system("cls");
			Matrix temp_matrix = *(this->getMatVec().at(index));//形参，不修改实参
			if (temp_matrix == Matrix())return;
			std::cout << "Present matrix is below:" << std::endl;
			this->show(temp_matrix);
			this->matrixMainMenu();

			int choice;
			std::cin >> choice;
			switch (choice)
			{
			case 1:this->matrixOperation_1(temp_matrix, index); break;
			case 2:this->matrixOperation_2(temp_matrix, index); break;
			case 3:this->matrixOperation_3(temp_matrix, index); break;
			case 4:this->matrixOperation_4(temp_matrix, index); break;
			case 5:this->matrixOperation_5(temp_matrix, index); break;
			case 6:this->matrixOperation_6(temp_matrix, index); break;
			case 7:this->matrixOperation_7(temp_matrix, index); break;
			case 8:this->matrixOperation_8(temp_matrix, index); break;
			case 9:this->matrixOperation_9(temp_matrix, index); break;
			case 10:this->matrixOperation_10(temp_matrix, index); break;
			case 11:this->matrixOperation_11(temp_matrix, index); break;
			case 12:this->matrixOperation_12(temp_matrix, index); break;
			case 13:this->matrixOperation_13(temp_matrix, index); break;
			case 14:this->matrixOperation_14(temp_matrix, index); break;
			case 15:this->matrixOperation_15(temp_matrix, index); break;
			case 16:this->matrixOperation_16(temp_matrix, index); break;
			case 17:this->matrixOperation_17(temp_matrix, index); break;
			case 18:this->matrixOperation_18(temp_matrix, index); break;
			case 19:this->matrixOperation_19(temp_matrix, index); break;
			case 20:this->matrixOperation_20(temp_matrix, index); break;
			case 21:this->matrixOperation_21(temp_matrix, index); break;
			case 0:
			{
				return;
			}
			default:
				std::cerr << ERR_PHRASE << std::endl;
				break;
			}
			system("pause");
		}
	}
	catch (out_of_range& err)
	{
		std::cerr << err.what() << std::endl;
		return;
	}
	catch (runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return;
	}
	catch (...)
	{
		std::cerr << "An unknown exception occurred" << std::endl;
		return;
	}

}
//行列式功能子菜单中的专有操作
void LAC::linearDetFunc()
{
	try
	{
		system("cls");
		if (this->detVecSize() == 0)
		{
			std::cout << "NONE!" << std::endl;
			return;
		}
		this->show(2);
		std::cout << "Which det do you want to operate?" << std::endl;
		int index;
		std::cin >> index;
		if (index <= 0 || index > this->detVecSize())
		{
			std::cerr << ERR_PHRASE << std::endl;
			return;
		}
		index--;//变为索引

		while (true)
		{
			//展示行列式操作菜单
			system("cls");
			Det temp_det = *(this->getDetVec().at(index));//形参，不修改实参
			if (temp_det == Det())return;
			std::cout << "Present det is below:" << std::endl;
			this->show(temp_det);
			this->detMainMenu();

			int choice;
			std::cin >> choice;
			switch (choice)
			{
			case 1:this->detOperation_1(temp_det, index); break;
			case 2:this->detOperation_2(temp_det, index); break;
			case 3:this->detOperation_3(temp_det, index); break;
			case 4:this->detOperation_4(temp_det, index); break;
			case 5:this->detOperation_5(temp_det, index); break;
			case 0:
			{
				return;
			}
			default:
				std::cerr << ERR_PHRASE << std::endl;
				break;
			}
			system("pause");
		}
	}
	catch (out_of_range& err)
	{
		std::cerr << err.what() << std::endl;
		return;
	}
	catch (runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return;
	}
	catch (...)
	{
		std::cerr << "An unknown exception occurred" << std::endl;
		return;
	}
}
//线性方程组功能子菜单中的专有操作
void LAC::linearSystemFunc()
{
	try
	{
		system("cls");
		if (this->sysVecSize() == 0)
		{
			std::cout << "NONE!" << std::endl;
			return;
		}
		this->show(3);
		std::cout << "Which linear_system do you want to operate?" << std::endl;
		int index;
		std::cin >> index;
		if (index <= 0 || index > this->sysVecSize())
		{
			std::cerr << ERR_PHRASE << std::endl;
			return;
		}
		index--;//变为索引

		while (true)
		{
			//展示线性方程组操作菜单
			system("cls");
			LinearSystem temp_system = *(this->getSysVec().at(index));//形参，不修改实参
			if (temp_system == LinearSystem())return;
			std::cout << "Present linear_system is below:" << std::endl;
			this->show(temp_system);
			this->systemMainMenu();

			int choice;
			std::cin >> choice;
			switch (choice)
			{
			case 1:systemOperation_1(temp_system, index); break;
			case 2:systemOperation_2(temp_system, index); break;
			case 3:systemOperation_3(temp_system, index); break;
			case 0:
			{
				return;
			}
			default:
				std::cerr << ERR_PHRASE << std::endl;
				break;
			}
			system("pause");
		}
	}
	catch (out_of_range& err)
	{
		std::cerr << err.what() << std::endl;
		return;
	}
	catch (runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return;
	}
	catch (...)
	{
		std::cerr << "An unknown exception occurred" << std::endl;
		return;
	}

}
//基功能子菜单中的专有操作
void LAC::linearBasisFunc()
{
	try
	{
		system("cls");
		if (this->basisVecSize() == 0)
		{
			std::cout << "NONE!" << std::endl;
			return;
		}
		this->show(4);
		std::cout << "Which basis do you want to operate?" << std::endl;
		int index;
		std::cin >> index;
		if (index <= 0 || index > this->basisVecSize())
		{
			std::cerr << ERR_PHRASE << std::endl;
			return;
		}
		index--;//变为索引

		while (true)
		{
			//展示矩阵操作菜单
			system("cls");
			Basis temp_basis = *(this->getBasisVec().at(index));//形参，不修改实参
			if (temp_basis == Basis())return;
			std::cout << "Present basis is below:" << std::endl;
			this->show(temp_basis);
			this->basisMainMenu();

			int choice;
			std::cin >> choice;
			switch (choice)
			{
			case 1:this->basisOperation_1(temp_basis, index); break;
			case 2:this->basisOperation_2(temp_basis, index); break;
			case 3:this->basisOperation_3(temp_basis, index); break;
			case 4:this->basisOperation_4(temp_basis, index); break;
			case 5:this->basisOperation_5(temp_basis, index); break;
			case 6:this->basisOperation_6(temp_basis, index); break;
			case 7:this->basisOperation_7(temp_basis, index); break;
			case 8:this->basisOperation_8(temp_basis, index); break;
			case 0:return;
			default:
				std::cerr << ERR_PHRASE << std::endl;
				break;
			}
			system("pause");
		}
	}
	catch (out_of_range& err)
	{
		std::cerr << err.what() << std::endl;
		return;
	}
	catch (runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return;
	}
	catch (...)
	{
		std::cerr << "An unknown exception occurred" << std::endl;
		return;
	}
}


//展示

//展示某个
void LAC::show(Matrix& matrix)
{
	for (auto& row : matrix.getValueVec())
	{
		std::cout << "\t[";
		for (auto& Number : row)
		{
			Number = std::round(Number * 100) / 100;//精确到0.01
			std::cout << Number << " ";
		}
		std::cout << "]" << std::endl;
	}
}
//展示某个
void LAC::show(Det& det)
{
	if (det.getPreNum() == 1)
	{
		for (auto& row : det.getValueVec())
		{
			std::cout << "\t|";
			for (auto& Number : row)
			{
				Number = std::round(Number * 100) / 100;//精确到0.01
				std::cout << Number << " ";
			}
			std::cout << "|" << std::endl;
		}
	}
	else
	{
		int mid = (det.getOrder() % 2 == 0) ? (det.getOrder() / 2 - 1) : ((det.getOrder() - 1) / 2);//中间行的索引
		for (int i = 0; i < det.getOrder(); i++)
		{
			if (i != mid)
			{
				std::cout << "\t|";
			}
			else
			{
				std::cout << det.getPreNum() << "*\t|";
			}

			for (int j = 0; j < det.getOrder(); j++)
			{
				det[i][j] = std::round(det[i][j] * 100) / 100;//精确到0.01
				std::cout << det[i][j] << " ";
			}
			std::cout << "|" << std::endl;
		}
	}
}
//展示某个
void LAC::show(LinearSystem& system)
{
	Matrix A = system.getA(), B = system.getB();
	for (int i = 0; i < system.getARow(); i++)
	{
		std::cout << "\t{  ";
		for (int j = 0; j < system.getAColumn(); j++)
		{
			A[i][j] = std::round(A[i][j] * 100) / 100;//精确到0.01
			std::cout << A[i][j] << " * X" << j + 1;
			if (j != system.getAColumn() - 1)
			{
				std::cout << " + ";
			}
		}
		B[i][0] = std::round(B[i][0] * 100) / 100;//精确到0.01
		std::cout << " = " << B[i][0] << std::endl;
	}
}
//展示某个
void LAC::show(Basis& basis)
{
	for (int i = 0; i < basis.at(0).size(); i++)
	{
		std::cout << "\t";
		for (int j = 0; j < basis.size(); j++)
		{
			basis[j][i][0] = std::round(basis[j][i][0] * 100) / 100;//精确到0.01
			std::cout << "[" << basis[j][i][0] << "]  ";
		}
		std::cout << std::endl;
	}
}
//展示所有
void LAC::show(int _type)
{
	int index = 1;
	switch (_type)
	{
	case 1:
	{
		if (this->matVecSize() != 0)
		{
			for (auto& pmat : matrixVector_)
			{
				if (*pmat == Matrix())
				{
					continue;
				}
				std::cout << index << ".";
				index++;
				this->show(*pmat);
			}
		}
		break;
	}
	case 2:
	{
		if (this->detVecSize() != 0)
		{
			for (auto& pdet : detVector_)
			{
				if (*pdet == Det())
				{
					continue;
				}
				std::cout << index << ".";
				index++;
				this->show(*pdet);
			}
		}
		break;
	}
	case 3:
	{
		if (this->sysVecSize() != 0)
		{
			for (auto& psys : systemVector_)
			{
				if (*psys == LinearSystem())
				{
					continue;
				}
				std::cout << index << ".";
				index++;
				this->show(*psys);
			}
		}
		break;
	}
	case 4:
	{
		if (this->basisVecSize() != 0)
		{
			for (auto& pbas : basisVector_)
			{
				if (*pbas == Basis())
				{
					continue;
				}
				std::cout << index << ".";
				index++;
				this->show(*pbas);
			}
		}
		break;
	}
	default:
		std::cerr << "Fault input!" << std::endl;
		return;
		break;
	}
}


//添加

//添加一个矩阵，可选择插入的位置索引（左插）
bool LAC::addItem(Matrix& matrix, int index)
{
	if (index == 0 && this->matVecSize() == 0)//如果新传入
	{
		this->matrixVector_.emplace_back(make_shared<Matrix>(matrix));
		return true;
	}
	else if (index > this->matVecSize() || index < 0)
	{
		throw out_of_range("MatrixVector out of range !");
	}
	else if (index == this->matVecSize())
	{
		this->matrixVector_.emplace_back(make_shared<Matrix>(matrix));
		return true;
	}
	auto it = this->matrixVector_.begin() + index;
	this->matrixVector_.insert(it, make_shared<Matrix>(matrix));
	return true;
}
//添加一些矩阵
bool LAC::addItem(std::vector<Matrix>& matrixvec, int index)
{
	std::vector<std::shared_ptr<Matrix>>ptrmatrixVec;
	std::for_each(matrixvec.begin(), matrixvec.end(), [&ptrmatrixVec](const Matrix& matrix) {
		ptrmatrixVec.emplace_back(std::make_shared<Matrix>(matrix));
		});
	if (index == 0 && this->matrixVector_.empty())//如果新传入
	{
		for (auto it = ptrmatrixVec.begin(); it != ptrmatrixVec.end(); it++)
		{
			this->matrixVector_.emplace_back(*it);
		}
		return true;
	}
	if (index > this->matVecSize() || index < 0)
	{
		throw out_of_range("MatrixVector out of range !");
	}
	else if (index == this->matVecSize())
	{
		for (int i = 0; i < ptrmatrixVec.size(); i++)
		{
			this->matrixVector_.emplace_back(ptrmatrixVec.at(i));
		}
		return true;
	}
	if (matrixvec.empty())
	{
		return true;
	}

	auto it = this->matrixVector_.begin() + index;

	this->matrixVector_.insert(it, ptrmatrixVec.begin(), ptrmatrixVec.end());

	return true;
}
//添加一个行列式，可选择插入的位置索引
bool LAC::addItem(Det& det, int index)
{
	if (index == 0 && this->detVector_.empty())//如果新传入
	{
		this->detVector_.emplace_back(make_shared<Det>(det));
		return true;
	}
	else if (index > this->detVecSize() || index < 0)
	{
		throw out_of_range("DetVector out of range !");
	}
	else if (index == this->detVecSize())
	{
		this->detVector_.emplace_back(make_shared<Det>(det));
		return true;
	}
	auto it = this->detVector_.begin() + index;
	this->detVector_.insert(it, make_shared<Det>(det));
	return true;
}
//添加一些行列式
bool LAC::addItem(std::vector<Det>& detvec, int index)
{
	std::vector<std::shared_ptr<Det>>ptrdetVec;
	std::for_each(detvec.begin(), detvec.end(), [&ptrdetVec](const Det& det) {
		ptrdetVec.emplace_back(std::make_shared<Det>(det));
		});
	if (index == 0 && this->detVector_.empty())//如果新传入
	{
		for (auto it = ptrdetVec.begin(); it != ptrdetVec.end(); it++)
		{
			this->detVector_.emplace_back(*it);
		}
		return true;
	}
	if (index > this->detVecSize() || index < 0)
	{
		throw out_of_range("DetVector out of range !");
	}
	else if (index == this->matVecSize())
	{
		for (int i = 0; i < ptrdetVec.size(); i++)
		{
			this->detVector_.emplace_back(ptrdetVec.at(i));
		}
		return true;
	}
	if (detvec.empty())
	{
		return true;
	}

	auto it = this->detVector_.begin() + index;

	this->detVector_.insert(it, ptrdetVec.begin(), ptrdetVec.end());

	return true;
}
//添加一个线性方程组，可选择插入的位置索引
bool LAC::addItem(LinearSystem& system, int index)
{
	if (index == 0 && this->systemVector_.empty())//如果新传入
	{
		this->systemVector_.emplace_back(make_shared<LinearSystem>(system));
		return true;
	}
	else if (index > this->sysVecSize() || index < 0)
	{
		throw out_of_range("LinearSystemVector out of range !");
	}
	else if (index == this->sysVecSize())
	{
		this->systemVector_.emplace_back(make_shared<LinearSystem>(system));
		return true;
	}
	auto it = this->systemVector_.begin() + index;
	this->systemVector_.insert(it, make_shared<LinearSystem>(system));
	return true;
}
//添加一些线性方程组
bool LAC::addItem(std::vector<LinearSystem>& systemvec, int index)
{
	std::vector<std::shared_ptr<LinearSystem>>ptrsystemVec;
	std::for_each(systemvec.begin(), systemvec.end(), [&ptrsystemVec](const LinearSystem& system) {
		ptrsystemVec.emplace_back(std::make_shared<LinearSystem>(system));
		});
	if (index == 0 && this->systemVector_.empty())//如果新传入
	{
		for (auto it = ptrsystemVec.begin(); it != ptrsystemVec.end(); it++)
		{
			this->systemVector_.emplace_back(*it);
		}
		return true;
	}
	if (index > this->sysVecSize() || index < 0)
	{
		throw out_of_range("LinearSystemVector out of range !");
	}
	else if (index == this->sysVecSize())
	{
		for (int i = 0; i < ptrsystemVec.size(); i++)
		{
			this->systemVector_.emplace_back(ptrsystemVec.at(i));
		}
		return true;
	}
	if (systemvec.empty())
	{
		return true;
	}

	auto it = this->systemVector_.begin() + index;

	this->systemVector_.insert(it, ptrsystemVec.begin(), ptrsystemVec.end());

	return true;
}
//添加一个基，可选择插入的位置索引（左插）
bool LAC::addItem(Basis& basis, int index)
{
	if (index == 0 && this->basisVecSize() == 0)//如果新传入
	{
		this->basisVector_.emplace_back(make_shared<Basis>(basis));
		return true;
	}
	else if (index > this->basisVecSize() || index < 0)
	{
		throw out_of_range("BasisVector out of range !");
	}
	else if (index == this->basisVecSize())
	{
		this->basisVector_.emplace_back(make_shared<Basis>(basis));
		return true;
	}
	auto it = this->basisVector_.begin() + index;
	this->basisVector_.insert(it, make_shared<Basis>(basis));
	return true;
}
//添加一些基
bool LAC::addItem(std::vector<Basis>& basisvec, int index)
{
	std::vector<std::shared_ptr<Basis>>p_basisvec;
	std::for_each(basisvec.begin(), basisvec.end(), [&p_basisvec](const Basis& basis) {
		p_basisvec.emplace_back(std::make_shared<Basis>(basis));
		});
	if (index == 0 && this->basisVector_.empty())//如果新传入
	{
		for (auto it = p_basisvec.begin(); it != p_basisvec.end(); it++)
		{
			this->basisVector_.emplace_back(*it);
		}
		return true;
	}
	if (index > this->basisVecSize() || index < 0)
	{
		throw out_of_range("BasisVector out of range !");
	}
	else if (index == this->basisVecSize())
	{
		for (int i = 0; i < p_basisvec.size(); i++)
		{
			this->basisVector_.emplace_back(p_basisvec.at(i));
		}
		return true;
	}
	if (basisvec.empty())
	{
		return true;
	}

	auto it = this->basisVector_.begin() + index;

	this->basisVector_.insert(it, p_basisvec.begin(), p_basisvec.end());

	return true;
}


//删除

//删除，第二个参数是索引，第三个是索引及之后的删除数量（默认为1）
bool LAC::deleteItem(int _type, int vec_index, int del_number)
{
	switch (_type)
	{
	case 1:
	{
		if (vec_index >= this->matVecSize() || vec_index < 0)
		{
			throw out_of_range("MatrixVector out of range !");
		}
		auto it = this->matrixVector_.begin() + vec_index;
		auto rit = it + del_number;
		this->matrixVector_.erase(it, rit);
	}
	break;
	case 2:
	{
		if (vec_index >= this->detVecSize() || vec_index < 0)
		{
			throw out_of_range("DetVector out of range !");
		}
		auto it = this->detVector_.begin() + vec_index;
		auto rit = it + del_number;
		this->detVector_.erase(it, rit);
	}
	break;
	case 3:
	{
		if (vec_index >= this->sysVecSize() || vec_index < 0)
		{
			throw out_of_range("LinearSystemVector out of range !");
		}
		auto it = this->systemVector_.begin() + vec_index;
		auto rit = it + del_number;
		this->systemVector_.erase(it, rit);
	}
	break;
	case 4:
	{
		if (vec_index >= this->basisVecSize() || vec_index < 0)
		{
			throw out_of_range("BasisVector out of range !");
		}
		auto it = this->basisVector_.begin() + vec_index;
		auto rit = it + del_number;
		this->basisVector_.erase(it, rit);
	}
	break;
	default:
		std::cerr << "Fault input!" << std::endl;
		return false;
		break;
	}
	return true;
}
//删除数组所有的东西
bool LAC::clearItem(int _type)
{
	switch (_type)
	{
	case 1:
		this->matrixVector_.clear();
		break;
	case 2:
		this->detVector_.clear();
		break;
	case 3:
		this->systemVector_.clear();
		break;
	case 4:
		this->basisVector_.clear();
		break;
	default:
		std::cerr << "Fault input!" << std::endl;
		return false;
		break;
	}
	return true;
}
//清除容器的空东西
void LAC::removeEmpty() {
	//使用erase-remove惯用法删除
	//移除所有指向空矩阵的智能指针
	this->matrixVector_.erase(
		std::remove_if(matrixVector_.begin(), matrixVector_.end(), [&](std::shared_ptr<Matrix>& pmat) {
			return *pmat == Matrix();
			}),
		matrixVector_.end());
	//移除所有指向空行列式的智能指针
	this->detVector_.erase(
		std::remove_if(detVector_.begin(), detVector_.end(), [&](std::shared_ptr<Det>& pdet) {
			return *pdet == Det();
			}),
		detVector_.end());
	//移除所有指向空矩阵的智能指针
	this->systemVector_.erase(
		std::remove_if(systemVector_.begin(), systemVector_.end(), [&](std::shared_ptr<LinearSystem>& psys) {
			return *psys == LinearSystem();
			}),
		systemVector_.end());
	//移除所有指向空基的智能指针
	this->basisVector_.erase(
		std::remove_if(basisVector_.begin(), basisVector_.end(), [&](std::shared_ptr<Basis>& pbas) {
			return *pbas == Basis();
			}),
		basisVector_.end());
}

//查找(对基的查找要填写最后的参数为true）
//查找：找到了返回索引，找不到返回-1（注：线性方程组则是根据A）

//前三类的内容查找
template<class T>
int contentSearch(const T& vec, const ContentVec& target)//矩阵行列式方程组的
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& ptr) {
		return ptr->getValueVec() == target;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//基的内容查找
template<class T>
int contentSearchBasis(const T& vec, const ContentVec& target, LAC* This)//基的
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& basptr) {
		Matrix merged = This->M_mergeBasis(*basptr);
		return merged.getValueVec() == target;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//前三类的首元查找
template<class T>
int firstValSearch(const T& vec, double target)//矩阵行列式方程组的
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& ptr) {
		return ptr->at(0, 0) == target;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//基的首元查找
template<class T>
int firstValSearchBasis(const T& vec, double target)//基的
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& basptr) {
		return (basptr->at(0))[0][0] == target;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//前三类的行列查找
template<class T>
int rowColumnSearch(const T& vec, int row_, int column_)//矩阵行列式方程组的
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& ptr) {
		return ptr->getRow() == row_ & ptr->getColumn() == column_;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//基的行列查找
template<class T>
int rowColumnSearchBasis(const T& vec, int row_, int column_)//基的
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& basptr) {
		return basptr->size() == column_ && basptr->at(0).size() == row_;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}

//内容查找
int LAC::searchItem(int _type, const ContentVec& blockvec)
{
	switch (_type)
	{
	case 1:
	{
		return contentSearch(this->matrixVector_, blockvec);
		break;
	}

	case 2:
	{
		return contentSearch(this->detVector_, blockvec);
		break;
	}

	case 3:
	{
		return contentSearch(this->systemVector_, blockvec);
		break;
	}
	case 4:
	{
		return contentSearchBasis(this->basisVector_, blockvec, this);
		break;
	}
	default:
		std::cerr << "Fault input!" << std::endl;
		return -1;
		break;
	}
}
//首元查找
int LAC::searchItem(int _type, double first_val)
{
	switch (_type)
	{
	case 1:
	{
		return firstValSearch(this->matrixVector_, first_val);
		break;
	}
	case 2:
	{
		return firstValSearch(this->detVector_, first_val);
		break;
	}
	case 3:
	{
		return firstValSearch(this->systemVector_, first_val);
		break;
	}
	case 4:
	{
		return firstValSearchBasis(this->basisVector_, first_val);
		break;
	}
	default:
		std::cerr << "Fault input!" << std::endl;
		return -1;
		break;
	}
}
//行列查找
int LAC::searchItem(int _type, int row, int column)
{
	switch (_type)
	{
	case 1:
	{
		return rowColumnSearch(this->matrixVector_, row, column);
		break;
	}
	case 2:
	{
		return rowColumnSearch(this->detVector_, row, column);
		break;
	}
	case 3:
	{
		return rowColumnSearch(this->systemVector_, row, column);
		break;
	}
	case 4:
	{
		return rowColumnSearchBasis(this->basisVector_, row, column);
		break;
	}
	default:
		std::cerr << "Fault input!" << std::endl;
		return -1;
		break;
	}
}


//排序和乱序(对基的排序要填写最后的参数为true)
	//排序，注意线性方程组按照A
//处理智能指针数组的排序函数

//前三类的首元排序
template<class T>
bool normalSort(T& container, bool sort_order)//矩阵行列式方程组的
{
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		return sort_order ? p_pre->at(0, 0) < p_lat->at(0, 0) : p_pre->at(0, 0) > p_lat->at(0, 0);
		});
	return true;
}
//基的首元排序
template<class T>
bool normalSortBasis(T& container, bool sort_order)//基的
{
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		return sort_order ? (p_pre->at(0))[0][0] < (p_lat->at(0))[0][0] : (p_pre->at(0))[0][0] > (p_lat->at(0))[0][0];
		});
	return true;
}
//前三类的大小排序
template<class T>
bool sizeSort(T& container, bool sort_order)//矩阵行列式方程组的
{
	//两次排序
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		return sort_order ? p_pre->getRow() < p_lat->getRow() : p_pre->getRow() > p_lat->getRow();
		});
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		return sort_order ? p_pre->getColumn() < p_lat->getColumn() : p_pre->getColumn() > p_lat->getColumn();
		});
	return true;
}
//基的大小排序
template<class T>
bool sizeSortBasis(T& container, bool sort_order, LAC* This)//基的
{
	//两次排序
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		Matrix merge_pre = This->M_mergeBasis(*p_pre), merge_lat = This->M_mergeBasis(*p_lat);
		return sort_order ? merge_pre.getRow() < merge_lat.getRow() : merge_pre.getRow() > merge_lat.getRow();
		});
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		Matrix merge_pre = This->M_mergeBasis(*p_pre), merge_lat = This->M_mergeBasis(*p_lat);
		return sort_order ? merge_pre.getColumn() < merge_lat.getColumn() : merge_pre.getColumn() > merge_lat.getColumn();
		});
	return true;
}
//首元排序，排序方式：true：升序；false：逆序；
bool LAC::firstValSort(int _type, bool sort_order)
{
	switch (_type)
	{
	case 1:
	{
		normalSort(this->matrixVector_, sort_order);
		break;
	}
	case 2:
	{
		normalSort(this->detVector_, sort_order);
		break;
	}
	case 3:
	{
		normalSort(this->systemVector_, sort_order);
		break;
	}
	case 4:
	{
		normalSortBasis(this->basisVector_, sort_order);
		break;
	}
	default:
		std::cerr << "Fault input!" << std::endl;
		return false;
		break;
	}
	return true;
}
//大小排序，需要研究一点算法
bool LAC::blockSizeSort(int _type, bool sort_order)
{
	switch (_type)
	{
	case 1:
	{
		sizeSort(this->matrixVector_, sort_order);
		break;
	}
	case 2:
	{
		sizeSort(this->detVector_, sort_order);
		break;
	}
	case 3:
	{
		sizeSort(this->systemVector_, sort_order);
		break;
	}
	case 4:
	{
		sizeSortBasis(this->basisVector_, sort_order, this);
		break;
	}
	default:
		std::cerr << "Fault input!" << std::endl;
		return false;
		break;
	}
	return true;
}
//洗牌
bool LAC::shuffleItem(int _type)
{
	// 获取当前时间作为随机数生成器的种子
	time_t seed = std::time(0);
	// 创建一个随机数生成器
	std::default_random_engine engine(seed);
	// 打乱容器
	switch (_type)
	{
	case 1:
	{
		std::shuffle(this->matrixVector_.begin(), this->matrixVector_.end(), engine);
		break;
	}
	case 2:
	{
		std::shuffle(this->detVector_.begin(), this->detVector_.end(), engine);
		break;
	}
	case 3:
	{
		std::shuffle(this->systemVector_.begin(), this->systemVector_.end(), engine);
		break;
	}
	case 4:
	{
		std::shuffle(this->basisVector_.begin(), this->basisVector_.end(), engine);
		break;
	}
	default:
		std::cerr << "Fault input!" << std::endl;
		return false;
		break;
	}
	return true;
}


//其他工具

//浮点数精度不够时，四舍五入（前三类）
void LAC::castVal(ContentVec& blk)
{
	//四舍五入，尤其是0
	int Inter;
	for (auto& row : blk)for (auto& val : row) { val = std::round(val * 100) / 100; }

}
//浮点数精度不够时，四舍五入（基）
void LAC::castVal(Basis& basis)
{
	//四舍五入，尤其是0
	int Inter;
	for (auto& blk : basis)for (auto& row : blk)for (auto& val : row) { val = std::round(val * 100) / 100; }

}



//用户交互部分

//矩阵菜单
void LAC::matrixMainMenu()
{
	std::cout << "Choose your operation:" << std::endl;
	std::cout << "1.Take Det or Linear System" << std::endl;
	std::cout << "2.Power N" << std::endl;
	std::cout << "3.Multiply a number" << std::endl;
	std::cout << "4.transportortation" << std::endl;
	std::cout << "5.Obtain the minor (获取余子式)" << std::endl;
	std::cout << "6.Obtain the adjugate matrix (获取伴随矩阵)" << std::endl;
	std::cout << "7.Concatenate matrix" << std::endl;
	std::cout << "8.Split matrix" << std::endl;
	std::cout << "9.Elementary row transformation (初等行变换)" << std::endl;
	std::cout << "10.Finding the inverse matrix by ERT (初等行变换求逆矩阵)" << std::endl;
	std::cout << "11.Obtain rank of matrix by ERT (初等行变换求秩)" << std::endl;
	std::cout << "12.Multiply a matrix" << std::endl;
	std::cout << "13.Get the inverse matrix directly" << std::endl;
	std::cout << "14.Split matrix into basis(把矩阵拆成基)" << std::endl;
	std::cout << "15.Gain the trace (获取矩阵的迹)" << std::endl;
	std::cout << "16.Versify the eigen value (判断是否为特征值)" << std::endl;
	std::cout << "17.Find eigen vectors with provided eigen values (根据提供的特征值寻找所有的特征向量)" << std::endl;
	std::cout << "18.Normal diaglization (普通对角化)" << std::endl;
	std::cout << "19.Orthogonal diaglization (正交对角化)" << std::endl;
	std::cout << "20.Contract diaglization (合同对角化，二次型标准化中的初等变换法)" << std::endl;
	std::cout << "21.Gain A^n through diaglization (对角化方法获取A^n)" << std::endl;
	std::cout << "0.Exit" << std::endl;
}

//1.Take Det or Linear System
void LAC::matrixOperation_1(Matrix& temp_matrix, int index)
{
	std::cout << "Choose your operation:\n1.take Det 2. take Linear System" << std::endl;
	int choice;
	std::cin >> choice;
	if (choice == 1)
	{
		Det result_det = this->M_takeDet(temp_matrix);
		std::cout << "Result is below:" << std::endl;
		this->show(result_det);
		this->addItem(result_det, this->detVecSize());
	}
	else if (choice == 2)
	{
		LinearSystem result_system = this->M_takeLinearSystem(temp_matrix);
		std::cout << "Result is below:" << std::endl;
		this->show(result_system);
		this->addItem(result_system, this->sysVecSize());
	}
	else
	{
		std::cerr << ERR_PHRASE << std::endl;
	}
}
//2.Power N
void LAC::matrixOperation_2(Matrix& temp_matrix, int index)
{
	int powN;
	std::cout << "Input the figure:" << std::endl;
	std::cin >> powN;
	if (powN <= 0)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	Matrix Nsq = this->M_pow(temp_matrix, powN);
	std::cout << "Result is below:" << std::endl;
	this->show(Nsq);
	this->addItem(Nsq, this->matVecSize());
}
//3.Multiply a number
void LAC::matrixOperation_3(Matrix& temp_matrix, int index)
{
	double mul_num;
	std::cout << "Input the number:" << std::endl;
	std::cin >> mul_num;
	//操作实参
	this->M_numMult(*(this->getMatVec().at(index)), mul_num);
	std::cout << "Result is below:" << std::endl;
	this->showMatVec(index);
}
//4.transportortation
void LAC::matrixOperation_4(Matrix& temp_matrix, int index)
{
	//操作实参
	this->M_transport(*(this->getMatVec().at(index)));
	std::cout << "Result is below:" << std::endl;
	this->showMatVec(index);
}
//5.Obtain the minor (获取余子式)
void LAC::matrixOperation_5(Matrix& temp_matrix, int index)
{
	std::cout << "Input row and column index of the centre value:" << std::endl;
	int row, col;
	std::cin >> row >> col;
	if (row <= 0 || row > temp_matrix.getRow() || col <= 0 || col > temp_matrix.getColumn())
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	Matrix minor_matrix = this->M_getMinor(row - 1, col - 1, temp_matrix);
	if (minor_matrix == Matrix())
	{
		return;
	}
	std::cout << "Result is below:" << std::endl;
	this->show(minor_matrix);
	this->addItem(minor_matrix, this->matVecSize());
}
//6.Obtain the adjugate matrix (获取伴随矩阵)
void LAC::matrixOperation_6(Matrix& temp_matrix, int index)
{
	Matrix adjugate_matrix = this->M_getAdjugate(temp_matrix);
	if (adjugate_matrix == Matrix())
	{
		std::cerr << "Adjugate matrix failed." << std::endl;
		return;
	}
	std::cout << "Result is below:" << std::endl;
	this->show(adjugate_matrix);
	this->addItem(adjugate_matrix, this->matVecSize());
}
//7.Concatenate matrix
void LAC::matrixOperation_7(Matrix& temp_matrix, int index)
{
	system("cls");
	int Sz = this->matVecSize();
	if (Sz < 2)
	{
		std::cerr << "Matrixes are NOT enough!" << std::endl;
		return;
	}

	std::cout << "Present matrixes are below:" << std::endl;
	this->show(1);
	std::cout << "Please choose the matrix that you want to concatenate:" << std::endl;
	int matrix_index;
	std::cin >> matrix_index;

	matrix_index--;//变为索引
	if (matrix_index < 0 || matrix_index >= Sz)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	Matrix to_concatenate = *(this->getMatVec().at(matrix_index));
	if (to_concatenate.getRow() != temp_matrix.getRow() && to_concatenate.getColumn() != temp_matrix.getColumn())
	{
		std::cerr << "The matrix CANNOT be concatenated with present matrix!" << std::endl;
		return;
	}
	std::cout << "Choose the approach to concatenate (Present matrix is A,and the matrix chosen latter is B):" << std::endl;
	std::cout << "1.A + B;  2.B + A;  3.A upper B lower;  4.A lowerB upper" << std::endl;
	int approach;
	std::cin >> approach;
	if (approach <= 0 || approach > 4)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	else if (((approach == 1 || approach == 2) && to_concatenate.getRow() != temp_matrix.getRow())
		|| ((approach == 3 || approach == 4) && to_concatenate.getColumn() != temp_matrix.getColumn()))
	{
		std::cerr << "The matrix CANNOT be concatenated with present matrix!" << std::endl;
		return;
	}
	Matrix concatenated = this->M_concatenate(temp_matrix, to_concatenate, approach);
	if (concatenated == Matrix())
	{
		std::cerr << "Concatenation failed." << std::endl;
		return;
	}

	std::cout << "Successfully concatenated ! Result is below:" << std::endl;
	this->show(concatenated);

	this->addItem(concatenated, Sz);//放入拼接后的矩阵

}
//8.Split matrix
void LAC::matrixOperation_8(Matrix& temp_matrix, int index)
{
	system("cls");
	int Sz = this->matVecSize();
	if (temp_matrix.getRow() == 1 || temp_matrix.getColumn() == 1)
	{
		std::cout << "The matrix is too small!" << std::endl;
		return;
	}
	std::cout << "Choose the approach to concatenate:" << std::endl;
	std::cout << "1.M --> A | B;  2.M --> A upper B lower" << std::endl;
	int approach;
	std::cin >> approach;
	std::string Phrase;
	if (approach == 1 || approach == 2)
	{
		Phrase = (approach == 1) ? "row" : "column";
	}
	else
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}

	Matrix& to_split = temp_matrix;
	system("cls");
	std::cout << "Present matrix is below:" << std::endl;
	this->show(to_split);
	std::cout << "Please input the index of " << Phrase << " after which the matrix will be splited :" << std::endl;
	int row_or_column;
	std::cin >> row_or_column;
	row_or_column--;//变为索引
	if ((approach == 1 && (row_or_column < 0 || row_or_column >= to_split.getRow() - 1))
		|| (approach == 2 && (row_or_column < 0 || row_or_column >= to_split.getColumn() - 1)))
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	std::pair<Matrix, Matrix>result_pair = this->M_split(to_split, (approach == 1) ? true : false, row_or_column);
	if (result_pair == std::pair<Matrix, Matrix>())
	{
		std::cerr << "Splition failed." << std::endl;
		return;
	}
	std::cout << "Successfully splited ! Result is below:" << std::endl;
	std::cout << "Matrix1:" << std::endl;
	this->show(result_pair.first);
	std::cout << "Matrix2:" << std::endl;
	this->show(result_pair.second);

	//放入拆分后的矩阵
	this->addItem(result_pair.first, Sz);
	this->addItem(result_pair.second, Sz);

}
//9.Elementary row transformation (初等行变换)
void LAC::matrixOperation_9(Matrix& temp_matrix, int index)
{
	bool ret = this->M_elementaryRowTransformation(temp_matrix);
	if (!ret)
	{
		std::cerr << "Elementary row transformation failed." << std::endl;
	}
}
//10.Finding the inverse matrix by ERT (初等行变换求逆矩阵)
void LAC::matrixOperation_10(Matrix& temp_matrix, int index)
{
	Matrix inverse_matrix = this->M_getInverseByTransformation(temp_matrix);
	if (inverse_matrix == Matrix())
	{
		std::cerr << "Finding the inverse matrix using ERT failed." << std::endl;
	}
	//将逆矩阵添加到数组
	this->addItem(inverse_matrix, this->matVecSize());
}
//11.Obtain _rank of matrix by ERT (初等行变换求秩)
void LAC::matrixOperation_11(Matrix& temp_matrix, int index)
{
	int _rank = this->S_getRank(temp_matrix);
	if (_rank == 0)
	{
		std::cerr << "Obtaining _rank failed." << std::endl;
	}
}
//12.multiply a matrix
void LAC::matrixOperation_12(Matrix& temp_matrix, int index)
{
	system("cls");
	if (this->matVecSize() == 0)
	{
		std::cout << "NONE!" << std::endl;
		return;
	}
	this->show(1);
	std::cout << "Please choose the matrix you want to multiply with your matrix:" << std::endl;
	int choice_index;
	std::cin >> choice_index;
	choice_index--;//变为索引
	if (choice_index < 0 || choice_index >= this->matVecSize())
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	Matrix to_multiply = *(this->getMatVec().at(choice_index));
	std::cout << "Choose the way to multiply (Present matrix is A , and the matrix you chose is B) :" << std::endl;
	std::cout << "1.A * B  2.B * A" << std::endl;
	int choice;
	std::cin >> choice;
	if (choice != 1 && choice != 2)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	if ((choice == 1 && temp_matrix.getColumn() != to_multiply.getRow())
		|| (choice == 2 && to_multiply.getColumn() != temp_matrix.getRow()))
	{
		std::cerr << "The matrix is NOT able to multiply with the one in this way!\n" << ERR_PHRASE << std::endl;
		return;
	}
	Matrix result_matrix = (choice == 1) ? (temp_matrix * to_multiply) : (to_multiply * temp_matrix);
	std::cout << "Result is below:" << std::endl;
	this->show(result_matrix);
	this->addItem(result_matrix, this->matVecSize());
}
//13.Get the inverse matrix directly
void LAC::matrixOperation_13(Matrix& temp_matrix, int index)
{
	Matrix inverse_mat = this->M_getInverse(temp_matrix);
	if (inverse_mat == Matrix())
	{
		std::cout << "The matrix is NOT inversable!" << std::endl;
		return;
	}
	std::cout << "The inverse matrix is :" << std::endl;
	this->show(inverse_mat);
	this->addItem(inverse_mat, this->matVecSize());
}
//14.Split matrix into basis(把矩阵拆成基)
void LAC::matrixOperation_14(Matrix& temp_matrix, int index)
{
	system("cls");
	std::cout << "Present matrix is below:" << std::endl;
	this->show(temp_matrix);
	std::cout << "Which kind of basis do you want to split the matrix into ?\n1.Column vectors  2.Row vectors" << std::endl;
	int choice;
	std::cin >> choice;
	if (choice != 1 && choice != 2)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	Basis result_basis = this->M_takeBasis(temp_matrix, choice);
	this->addItem(result_basis, this->basisVecSize());
	std::cout << "Successfully splited ! The basis are :" << std::endl;
	this->show(result_basis);
}
//15.Gain the trace (获取矩阵的迹)
void LAC::matrixOperation_15(Matrix& temp_matrix, int index)
{
	double _trace = this->M_getTrace(temp_matrix);
	std::cout << "The trace of the matrix is : " << _trace << std::endl;
}
//16.Versify the eigen value (判断是否为特征值)
void LAC::matrixOperation_16(Matrix& temp_matrix, int index)
{
	std::cout << "Input λ : ";
	double λ;
	std::cin >> λ;
	std::cout << (this->M_isEigenValue(temp_matrix, λ) ? "True !" : "False !") << std::endl;
}
//17.Find eigen vectors with provided eigen values (根据提供的特征值寻找所有的特征向量)
void LAC::matrixOperation_17(Matrix& temp_matrix, int index)
{
	std::map<double, Basis> result_vec = this->M_getEigenVector(temp_matrix);
	if (result_vec == std::map<double, Basis>())
	{
		std::cerr << "Eigen vector searching failed!" << std::endl;
		return;
	}
	system("cls");
	std::cout << "The eigen values and vectors you have found :" << std::endl;
	std::cout << "values : ";
	for (const auto& kv : result_vec)std::cout << kv.first << " ";
	std::cout << "\nvectors:" << std::endl;
	for (const auto& kv : result_vec)
	{
		Basis temp_basis = kv.second;
		this->show(temp_basis);
		std::cout << std::endl;
	}
}
//18.Normal diaglization (普通对角化)
void LAC::matrixOperation_18(Matrix& temp_matrix, int index)
{
	std::pair<Matrix, Matrix>result_pair = this->M_normalDiaglization(temp_matrix);
	if (result_pair == std::pair<Matrix, Matrix>())return;
	this->addItem(result_pair.first, this->matVecSize());
	this->addItem(result_pair.second, this->matVecSize());
}
//19.Orthogonal diaglization (正交对角化)
void LAC::matrixOperation_19(Matrix& temp_matrix, int index)
{
	std::pair<Matrix, Matrix>result_pair = this->M_orthogonalDiaglization(temp_matrix);
	if (result_pair == std::pair<Matrix, Matrix>())return;
	this->addItem(result_pair.first, this->matVecSize());
	this->addItem(result_pair.second, this->matVecSize());
}
//20.Contract diaglization (合同对角化，二次型标准化中的初等变换法)
void LAC::matrixOperation_20(Matrix& temp_matrix, int index)
{
	std::pair<Matrix, Matrix>result_pair = this->M_contractDiaglization(temp_matrix);
	if (result_pair == std::pair<Matrix, Matrix>())return;
	this->addItem(result_pair.first, this->matVecSize());
	this->addItem(result_pair.second, this->matVecSize());
}
//21.Gain A^n through diaglization (对角化方法获取A^n)
void LAC::matrixOperation_21(Matrix& temp_matrix, int index)
{
	std::cout << "input the figure : ";
	int _figure;
	std::cin >> _figure;
	Matrix power_A_n = this->M_getPowerByDiaglization(temp_matrix, _figure);
	if (power_A_n == Matrix())
	{
		std::cout << "Power failed." << std::endl;
		return;
	}
	this->addItem(power_A_n, this->matVecSize());
}


//行列式菜单
void LAC::detMainMenu()
{
	std::cout << "Choose your operation:" << std::endl;
	std::cout << "1.Take Matrix" << std::endl;
	std::cout << "2.Multiply a number on row or column" << std::endl;
	std::cout << "3.transportortation" << std::endl;
	std::cout << "4.Elementary transformation (初等变换)" << std::endl;
	std::cout << "5.Finding value of the det by ERT (初等变换求值)" << std::endl;
	std::cout << "0.Exit" << std::endl;
}
//1.Take Matrix
void LAC::detOperation_1(Det& temp_det, int index)
{
	Matrix result_matrix = this->D_takeMat(temp_det);
	std::cout << "Result is below:" << std::endl;
	this->show(result_matrix);
	this->addItem(result_matrix, this->matVecSize());
}
//2.Multiply a number on row or column
void LAC::detOperation_2(Det& temp_det, int index)
{
	int row_or_col, mul_index;
	std::cout << "Which kind do you want to multiply?\n1.Row  2.Column" << std::endl;
	std::cin >> row_or_col;
	if (row_or_col != 1 && row_or_col != 2)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	std::cout << "Which " << ((row_or_col == 1) ? "row" : "column") << " do you want to multiply?" << std::endl;
	std::cin >> mul_index;
	if (mul_index <= 0 || mul_index > temp_det.getOrder())
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	mul_index--;//变为索引
	double mul_num;
	std::cout << "Input the number:" << std::endl;
	std::cin >> mul_num;
	//操作实参
	this->D_numMult(*(this->getDetVec().at(index)), (row_or_col == 1) ? true : false, mul_index, mul_num);
	std::cout << "Result is below:" << std::endl;
	this->showDetVec(index);
}
//3.transportortation
void LAC::detOperation_3(Det& temp_det, int index)
{
	//操作实参
	this->D_transport(*(this->getDetVec().at(index)));
	std::cout << "Result is below:" << std::endl;
	this->showDetVec(index);
}
//4.Elementary transformation (初等变换)
void LAC::detOperation_4(Det& temp_det, int index)
{
	bool ret = this->D_elementaryTransformation(temp_det);
	if (!ret)
	{
		std::cerr << "Elementary transformation failed." << std::endl;
	}
}
//5.Finding value of the det by ERT (初等变换求值)
void LAC::detOperation_5(Det& temp_det, int index)
{
	double res = this->D_getValue_Eletrans(temp_det);
	std::cout << "Successfully solved!\nThe value of the det is " << res << std::endl;
}


//线性方程组菜单
void LAC::systemMainMenu()
{
	std::cout << "Choose your operation:" << std::endl;
	std::cout << "1.Get A or B" << std::endl;
	std::cout << "2.Solve System by elementary transformation" << std::endl;
	std::cout << "3.Solve System (only unhomo) by Law of Cramer(克拉默法则,仅仅非齐次)" << std::endl;
	std::cout << "0.Exit" << std::endl;
}
//1.Get A or B
void LAC::systemOperation_1(LinearSystem& temp_system, int index)
{
	int choice;
	Matrix temp_A, temp_B;
	std::cout << "Which one do you want?\n1.A  2.B  3.Both" << std::endl;
	std::cin >> choice;
	if (choice == 1)
	{
		temp_A = temp_system.getA();
	}
	else if (choice == 2)
	{
		temp_B = temp_system.getB();
	}
	else if (choice == 3)
	{
		temp_A = temp_system.getA();
		temp_B = temp_system.getB();
	}
	else
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	//将A，B放进矩阵数组
	if (choice != 2)this->addItem(temp_A, this->matVecSize());
	if (choice != 1)this->addItem(temp_B, this->matVecSize());
	std::cout << "Successfully got ! Matrixes are below:" << std::endl;
	if (choice != 2)this->show(temp_A);
	if (choice != 1)this->show(temp_B);
}
//2.Solve System by elementary transformation
void LAC::systemOperation_2(LinearSystem& temp_system, int index)
{
	//判断是齐次还是非齐次
	Matrix temp_B = temp_system.getB();
	bool isHomo = true;
	for (int i = 0; i < temp_B.getRow(); i++)
	{
		if (temp_B.at(i, 0) != 0)
		{
			isHomo = false;
			break;
		}
	}

	std::pair<ContentVec, ContentVec>solutions;//通解和特解
	if (isHomo)
	{
		//齐次
		solutions.first = this->S_solveHomo(temp_system);
		if (solutions.first == ContentVec())
		{
			std::cerr << "Homo linear system failed!" << std::endl;
			return;
		}
	}
	else
	{
		//非齐次
		solutions = this->S_solveUnhomo(temp_system);
		if (solutions == std::pair<ContentVec, ContentVec>())
		{
			std::cerr << "Unhomo linear system failed!" << std::endl;
			return;
		}
	}
	system("cls");
	std::cout << "Successfully solved ! The General Solution of the " << (isHomo ? "Homo" : "Unhomo") << " linear system " << std::endl;
	this->show(temp_system);
	std::cout << "is below:" << std::endl;
	this->S_showSol(solutions);

}
//3.Solve System (only unhomo) by Law of Cramer(克拉默法则,仅仅非齐次)
void LAC::systemOperation_3(LinearSystem& temp_system, int index)
{
	Matrix temp_B = temp_system.getB();
	bool isHomo = true;
	for (int i = 0; i < temp_B.getRow(); i++)
	{
		if (temp_B.at(i, 0) != 0)
		{
			isHomo = false;
			break;
		}
	}

	if (!isHomo)
	{
		ContentVec cramer_solution = this->S_getCramerSol(temp_system);
		if (cramer_solution == ContentVec())
		{
			std::cerr << "Law of Cramer failed!" << std::endl;
			return;
		}
	}
	else
	{
		std::cerr << "The linear system is homo and it is NOT fit for Law of Cramer." << std::endl;
	}

}


//基菜单
void LAC::basisMainMenu()
{
	std::cout << "Choose your operation:" << std::endl;
	std::cout << "1.Merge into Matrix" << std::endl;
	std::cout << "2.Gain transition matrix from this to another basis (获取过渡矩阵)" << std::endl;
	std::cout << "3.Jugde orthogonal(判断是否正交)" << std::endl;
	std::cout << "4.Gain the coordinate with this basis (求向量在这组基下的坐标)" << std::endl;
	std::cout << "5.Gain metric matrix(获取度量矩阵)" << std::endl;
	std::cout << "6.Model a vector(求向量的模)" << std::endl;
	std::cout << "7.Schmidt Orthogonalization(施密特正交化)" << std::endl;
	std::cout << "8.Normalization(单位化)" << std::endl;
	std::cout << "0.Exit" << std::endl;
}
//1.Merge into Matrix
void LAC::basisOperation_1(Basis& temp_basis, int index)
{
	Matrix merged = M_mergeBasis(temp_basis);
	if (merged == Matrix())
	{
		std::cout << "Merge failed." << std::endl;
		return;
	}
	std::cout << "Successfully merged ! The result is below:" << std::endl;
	this->show(merged);
	this->addItem(merged, this->matVecSize());
}
//2.Gain transition matrix from this to another basis (获取过渡矩阵)
void LAC::basisOperation_2(Basis& temp_basis, int index)
{
	if (this->basisVecSize() <= 1)
	{
		std::cout << "Basis are too less ! " << std::endl;
		return;
	}
	system("cls");
	std::cout << "Present basis are below:" << std::endl;
	this->show(4);
	std::cout << "Choose a basis as Y (present basis are X , and XP = Y ):" << std::endl;
	int choice;
	std::cin >> choice;
	choice--;//变为索引
	if (choice<0 || choice>+this->basisVecSize())
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	Matrix mat_P = this->M_getTransition(temp_basis, *this->getBasisVec().at(choice));
	if (mat_P == Matrix())
	{
		std::cout << "Transition matrix failed . Maybe you CANNOT transit between them !" << std::endl;
		return;
	}
	std::cout << "Transition matrix from X to Y is :" << std::endl;
	this->show(mat_P);
	this->addItem(mat_P, this->matVecSize());
}
//3.Jugde orthogonal(判断是否正交)
void LAC::basisOperation_3(Basis& temp_basis, int index)
{
	bool ret = this->M_isOrthogonal(temp_basis);
	std::cout << (ret ? "True !" : "False !") << std::endl;
}
//4.Gain the coordinate with this basis (求向量在这组基下的坐标)
void LAC::basisOperation_4(Basis& temp_basis, int index)
{
	ContentVec _vec(temp_basis.size(), std::vector<double>(1, 0));
	std::cout << "Please input the values of the vector : ";
	for (int i = 0; i < temp_basis.size(); i++)
	{
		std::cin >> _vec[i][0];
	}
	ContentVec _coordinate = this->M_getCoordinate(_vec, temp_basis);
	if (_coordinate == ContentVec())
	{
		std::cout << "Coodinate failed!" << std::endl;
		return;
	}
	std::cout << "Coordinate is :" << std::endl;
	Matrix showmat(_coordinate);
	this->show(showmat);

}
//5.Gain metric matrix(获取度量矩阵)
void LAC::basisOperation_5(Basis& temp_basis, int index)
{
	Matrix _metric = this->M_getMetric(temp_basis);
	if (_metric == Matrix())
	{
		std::cout << "Metric failed !" << std::endl;
		return;
	}
	std::cout << "Metric matrix is :" << std::endl;
	this->show(_metric);
	this->addItem(_metric, this->matVecSize());
}
//6.Model a vector(求向量的模)
void LAC::basisOperation_6(Basis& temp_basis, int index)
{
	std::vector<double> _vec;
	std::cout << "Input the lenth:" << std::endl;
	int _leng;
	std::cin >> _leng;
	if (_leng <= 0)
	{
		std::cerr << ERR_PHRASE << std::endl;
		return;
	}
	std::cout << "Input the values of the vector: ";
	for (int i = 0; i < _leng; i++)
	{
		double _val;
		std::cin >> _val;
		_vec.push_back(_val);
	}
	double _mod = 0;
	for (int i = 0; i < _vec.size(); i++)
	{
		_mod += _vec[i] * _vec[i];
	}
	_mod = std::sqrt(_mod);
	std::cout << "Model of the vector is :" << _mod << std::endl;
}
//7.Schmidt Orthogonalization(施密特正交化)
void LAC::basisOperation_7(Basis& temp_basis, int index)
{
	Basis after_schmidt = this->M_SchmidtOrthogonalization(temp_basis);
	if (after_schmidt == Basis())
	{
		std::cout << "Schmidt Orthogonalization failed." << std::endl;
		return;
	}
	std::cout << "Basis after Schmidt Orthogonalization is :" << std::endl;
	this->show(after_schmidt);
	this->addItem(after_schmidt, this->basisVecSize());
}
//8.Normalization(单位化)
void LAC::basisOperation_8(Basis& temp_basis, int index)
{
	M_normallize(temp_basis);
	std::cout << "Basis after normalization is :" << std::endl;
	this->show(temp_basis);
	this->addItem(temp_basis, this->basisVecSize());
}



//矩阵专有

//基本计算工具

//取行列式
Det LAC::M_takeDet(Matrix& matrix)
{
	if (!matrix.isSquare())
	{
		return Det();
	}
	else
	{
		return Det(matrix.getRow(), matrix.getValueVec(), 1);
	}
}
//取线性方程组（作为A）
LinearSystem LAC::M_takeLinearSystem(Matrix& matrix)
{
	return LinearSystem(matrix, Matrix(matrix.getRow(), 1));
}
//计算矩阵的N次方
Matrix LAC::M_pow(const Matrix& matrix, int pow)
{
	if (!matrix.isSquare())
	{
		return matrix;
	}
	if (pow <= 0)
	{
		return Matrix();
	}
	Matrix temp_matrix = matrix;
	for (int i = 0; i < pow - 1; i++)
	{
		temp_matrix = temp_matrix * matrix;
	}
	return temp_matrix;
}
//数乘某个数字；第2个是乘的数字.
void LAC::M_numMult(Matrix& matrix, double number)
{
	ContentVec tempblock(matrix.getRow(), std::vector<double>(matrix.getColumn(), 0));
	for (int i = 0; i < matrix.getRow(); i++)
	{
		for (int j = 0; j < matrix.getColumn(); j++)
		{
			tempblock[i][j] = matrix[i][j] * number;
		}
	}
	matrix.setContentVec(tempblock);
}
//矩阵转置
void LAC::M_transport(Matrix& matrix)
{
	int newrow_ = matrix.getColumn();
	int newcolumn_ = matrix.getRow();
	ContentVec tempblock;
	tempblock.resize(newrow_);
	for (int i = 0; i < newrow_; i++)
	{
		tempblock[i].resize(newcolumn_);
	}
	//数值转移
	for (int i = 0; i < matrix.getRow(); i++)
	{
		for (int j = 0; j < matrix.getColumn(); j++)
		{
			tempblock[j][i] = matrix[i][j];
		}
	}
	matrix.setMatrix(newrow_, newcolumn_, tempblock);

}
//获取余子式
Matrix LAC::M_getMinor(int index1, int index2, Matrix matrix)
{
	int row_ = matrix.getRow();
	int column_ = matrix.getColumn();
	if (index1 < 0 || index1 >= row_ || index2 < 0 || index2 >= column_)
	{
		throw out_of_range("minor matrix out of range !");
	}
	ContentVec tempblock(row_ - 1, std::vector<double>(column_ - 1, 0));
	//左上角
	for (int i = 0; i < index1; i++)
	{
		for (int j = 0; j < index2; j++)
		{
			tempblock[i][j] = matrix[i][j];
		}
	}
	//左下角
	for (int i = index1; i < row_ - 1; i++)
	{
		for (int j = 0; j < index2; j++)
		{
			tempblock[i][j] = matrix[i + 1][j];
		}
	}
	//右上角
	for (int i = 0; i < index1; i++)
	{
		for (int j = index2; j < column_ - 1; j++)
		{
			tempblock[i][j] = matrix[i][j + 1];
		}
	}
	//右下角
	for (int i = index1; i < row_ - 1; i++)
	{
		for (int j = index2; j < column_ - 1; j++)
		{
			tempblock[i][j] = matrix[i + 1][j + 1];
		}
	}
	return Matrix(row_ - 1, column_ - 1, tempblock);
}
//获取伴随矩阵
Matrix LAC::M_getAdjugate(const Matrix& matrix)
{
	if (!matrix.isSquare())
	{
		return Matrix();
	}
	if (matrix.getColumn() == 1)
	{
		return matrix;
	}
	int row_ = matrix.getRow();
	Det temp_det;
	Matrix adjmat(row_, row_), temp_matrix;
	for (int i = 0; i < row_; i++)
	{
		for (int j = 0; j < row_; j++)
		{
			temp_matrix = M_getMinor(i, j, matrix);
			if (temp_matrix == Matrix())
			{
				std::cerr << "Adj failed!" << std::endl;
				return Matrix();
			}
			temp_det = M_takeDet(temp_matrix);
			if (temp_det.getOrder() == 0)return Matrix();
			adjmat[i][j] = D_getValue(temp_det);
			//进行代数余子式操作
			if ((i + j) % 2 != 0)
			{
				adjmat[i][j] *= (-1);
			}
		}
	}
	//转置
	this->M_transport(adjmat);
	return adjmat;

}
//直接获取逆矩阵
Matrix LAC::M_getInverse(Matrix& matrix)
{
	Det temp_det = this->M_takeDet(matrix);
	double det_val = this->D_getValue(temp_det);
	Matrix adjugate_matrix = this->M_getAdjugate(matrix);
	if (!matrix.isSquare() || det_val == 0 || adjugate_matrix == Matrix())return Matrix();
	this->M_numMult(adjugate_matrix, 1.0 / det_val);
	return adjugate_matrix;
}

//初等行变换有关
//注：初等变换函数都是对本身进行变换！如果不想改变本身，需要拷贝一次 

//一次初等行变换，变换成功输出true:row1+=row2*k
bool LAC::M_onceRowElementaryTransformation(Matrix& matrix, int row1, int row2, double k)
{
	int row_ = matrix.getRow(), column_ = matrix.getColumn();
	if (row1 < 0 || row1 >= row_ || row2 < 0 || row2 >= row_ || row1 == row2)
	{
		throw out_of_range("out of range !");
	}
	for (int j = 0; j < column_; j++)
	{
		matrix[row1][j] += matrix[row2][j] * k;
	}
	return true;
}
//一次初等列变换，变换成功输出true:column1+=column2*k
bool LAC::M_onceColumnElementaryTransformation(Matrix& matrix, int column1, int column2, double k)
{
	int row_ = matrix.getRow(), column_ = matrix.getColumn();
	if (column1 < 0 || column1 >= column_ || column2 < 0 || column2 >= column_ || column1 == column2)
	{
		throw out_of_range("out of range !");
	}
	for (int i = 0; i < row_; i++)
	{
		matrix[i][column1] += matrix[i][column2] * k;
	}
	return true;
}
//判断初等行变换之后的矩阵是哪种类型的矩阵：1.行阶梯形矩阵；2.行最简型矩阵；3.标准型矩阵。三个都不是返回0
int LAC::M_typeJudge(Matrix matrix)
{
	try
	{
		if (matrix.getRow() == 1 || matrix.getColumn() == 1)
		{
			std::cerr << "Are you kidding me?" << std::endl;
			return 0;
		}
		int matrix_type = 0, row_ = matrix.getRow(), column_ = matrix.getColumn();
		std::map<int, int> zero_of_every_row;//本质是首非零元的坐标

		//检查是否为行阶梯形矩阵
		for (int i = 0; i < row_; i++)
		{
			int first_non_zero = column_; //初始化为列的最大值
			for (int j = 0; j < column_; j++)
			{
				if (matrix[i][j] != 0)
				{
					first_non_zero = j;
					break;
				}
			}
			zero_of_every_row[i] = first_non_zero;
		}
		//检查阶梯
		for (int i = 0; i < row_ - 1; i++)
		{
			if (zero_of_every_row[i] > zero_of_every_row[i + 1])return 0;
		}
		if (!zero_of_every_row.empty()) matrix_type = 1; //检验通过
		else return 0;

		//开始检查是否为行最简形矩阵
		for (int i = 0; i < row_; i++)
		{
			if (zero_of_every_row[i] == column_)continue;
			if (matrix[i][zero_of_every_row[i]] != 1)
			{
				return 1;
			}
		}
		//检查主元列中其他元素是否为0
		for (const auto& kv : zero_of_every_row)
		{
			int row = kv.first;
			int col = kv.second;
			if (col == column_)continue;
			for (int i = 0; i < row_; i++)
			{
				if ((i != row) && (matrix[i][col] != 0))
				{
					return 1;
				}
			}
		}

		matrix_type = 2; //检验通过

		//开始检查是否为标准型矩阵
		int smaller_order = (row_ <= column_) ? row_ : column_;
		int end_one_index = smaller_order;//末端的1的坐标
		for (int i = 0; i < smaller_order; i++)
		{
			if (matrix[i][i] != 1)
			{
				end_one_index = i;
				break;
			}
		}
		for (int i = 0; i < row_; i++)
		{
			for (int j = 0; j < end_one_index + 1; j++)
			{
				if ((i != j) && (matrix[i][j] != 0))return 2;
			}
			for (int j = end_one_index + 1; j < column_; j++)
			{
				if (matrix[i][j] != 0)return 2;
			}
		}
		matrix_type = 3; //检验通过

		return matrix_type;
	}
	catch (out_of_range& err)
	{
		std::cerr << err.what() << " when judging type of matrix.  :(" << std::endl;
		return 0;
	}
}
//多次初等行变换函数（用户交互）
bool LAC::M_elementaryRowTransformation(Matrix& matrix)
{

	int trans_round = 1;
	std::vector<Matrix>history;//历史记录
	try
	{
		while (true)
		{

			system("cls");
			std::cout << "ELEMENTARY  ROW  TRANSFORMATION" << std::endl;
			std::cout << "Present matrix is below:" << std::endl;
			this->show(matrix);
			std::cout << "Choices are below:" << std::endl;
			std::cout << "1.Row adding  \n2.Row number multiply  \n3.Row exchange  \n4.Withdraw  \n0.Exit" << std::endl;


			int choice = 0;
			std::cin >> choice;

			system("cls");
			std::cout << "ELEMENTARY  ROW  TRANSFORMATION" << std::endl;
			std::cout << "ROUND : " << trans_round << std::endl;
			std::cout << "Present matrix is below:" << std::endl;
			this->show(matrix);
			if (choice == 1)//Row adding
			{
				history.push_back(Matrix(matrix));//拷贝一份给history
				std::cout << "Ri + k*Rj" << std::endl << "Input i,j and k(i does NOT equal to j)(if three 0 inputed,you will exit):" << std::endl;
				int i, j;
				double k;

				while (true)
				{
					std::cin >> i >> j >> k;
					if (i == 0 && j == 0 && k == 0)
					{
						break;
					}
					i--, j--;//变为索引
					if (i < 0 || i >= matrix.getRow() || j < 0 || j >= matrix.getRow() || i == j)
					{
						std::cerr << REINPUT_PHRASE << std::endl;
						continue;
					}
					this->M_onceRowElementaryTransformation(matrix, i, j, k);
					break;
				}
				if (i == 0 && j == 0 && k == 0)continue;

			}
			else if (choice == 2)//Row number multiply
			{
				history.push_back(Matrix(matrix));//拷贝一份给history
				int rowindex;
				double mul_num;
				std::cout << "Input the row you want to multiply:" << std::endl;
				std::cin >> rowindex;
				if (rowindex <= 0 || rowindex > matrix.getRow())
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				rowindex--;//变为索引
				std::cout << "Input the number to multiply:" << std::endl;
				std::cin >> mul_num;
				for (int i = 0; i < matrix.getColumn(); i++)
				{
					matrix[rowindex][i] *= mul_num;
				}
			}
			else if (choice == 3)//Row exchange
			{
				history.push_back(Matrix(matrix));//拷贝一份给history
				int row1, row2;
				std::cout << "Input two row index for exchange:" << std::endl;
				std::cin >> row1 >> row2;
				if (row1 <= 0 || row1 > matrix.getRow() || row2 <= 0 || row2 > matrix.getRow() || row1 == row2)
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				row1--, row2--;//变为索引
				std::swap(matrix[row1], matrix[row2]);

			}
			else if (choice == 4)//Withdraw
			{
				if (trans_round == 1)
				{
					std::cerr << "You can't withdraw in the first round!" << std::endl;
					system("pause");
				}
				else
				{
					matrix = history.at(trans_round - 2);
					auto it = history.begin();
					it += trans_round - 2;
					history.erase(it);
					trans_round--;
				}
				continue;
			}
			else if (choice == 0)
			{
				system("cls");
				std::cout << "ELEMENTARY  ROW  TRANSFORMATION" << std::endl;
				std::cout << "Final matrix is below:" << std::endl;
				this->show(matrix);
				return true;
			}
			else
			{
				std::cerr << ERR_PHRASE << std::endl;
				return false;
			}

			trans_round++;//轮次+1
			//浮点数精度不够，需要在达到阈值时简化
			ContentVec casted = matrix.getValueVec();
			this->castVal(casted);
			matrix.setContentVec(casted);
		}
	}
	catch (exception& err)
	{
		std::cerr << err.what() << std::endl;
		std::cerr << "Operation has been withdrawn . Please transform the matrix again or contact relevant technological people!" << std::endl;
		system("pause");
		system("cls");
		return false;
	}
}
//初等行变换求逆矩阵，变换成功之后返回逆矩阵(拷贝，不改变原来矩阵）（用户交互）
Matrix LAC::M_getInverseByTransformation(Matrix& matrix)
{
	int row_ = matrix.getRow(), column_ = matrix.getColumn();
	if (!matrix.isSquare())return Matrix();

	//先判断有没有逆矩阵,即行列式是否为0
	Det judge_det = this->M_takeDet(matrix);
	double judge_val = this->D_getValue(judge_det);
	if (judge_val == 0)
	{
		std::cerr << "The matrix does NOT have an inverse matrix !" << std::endl;
		system("pause");
		return Matrix();
	}

	Matrix temp_matrix = Matrix(matrix);//拷贝一份进行求解

	system("cls");
	std::cout << "INVERSE  MATRIX  BY  ELEMENTARY  ROW  TRANSFORMATION" << std::endl;
	std::cout << "Present matrix is below:" << std::endl;
	this->show(matrix);
	std::cout << "Click any key to continue." << std::endl;
	system("pause");
	//拼接矩阵和一个单位矩阵，刷新页面开始初等变换
	Matrix temp_elematrix = this->M_generateEleMat(row_);
	Matrix montaged = this->M_concatenate(temp_matrix, temp_elematrix, 1);

	while (true)
	{
		system("cls");
		bool _sign = this->M_elementaryRowTransformation(montaged);
		if (!_sign)
		{
			std::cerr << "TRANSFORMATION FAILED!" << std::endl;
			system("pause");
			return Matrix();
		}
		//检查左边是不是单位矩阵
		Matrix copy_montaged(montaged);
		std::pair<Matrix, Matrix>result_pair = this->M_split(copy_montaged, true, montaged.getRow() - 1);
		temp_elematrix = result_pair.second;
		if (!this->M_isEleMat(result_pair.first))
		{
			//没有变换完成，选择继续变换或退出
			std::cerr << "The left part is NOT elementary matrix !" << std::endl;
			std::cerr << "Continue your transformation?" << std::endl;
			std::cerr << "1.Yes  2.No" << std::endl;
			int choice = 0;
			while (true)
			{
				std::cin >> choice;
				if (choice == 1)
				{
					system("cls");
					break;
				}
				else if (choice == 2)
				{
					std::cerr << "TRANSFORMATION HALTED!" << std::endl;
					system("pause");
					return Matrix();
				}
				else
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					continue;
				}
			}
			if (choice == 1)continue;
		}
		break;
	}

	//变换成功，拆分矩阵
	system("cls");
	std::cout << "Inverse Matrix is below:" << std::endl;
	this->show(temp_elematrix);
	return temp_elematrix;
}

//矩阵拼接与拆分

//矩阵拼接，前两个参数是拼接的两个矩阵，第三个是拼接方式：1.A + B; 2.B + A; 3.A上面B下面；4.A下面B上面
Matrix LAC::M_concatenate(Matrix& matrix1, Matrix& matrix2, int _type)
{
	int row_1 = matrix1.getRow(), row_2 = matrix2.getRow(), column_1 = matrix1.getColumn(), column_2 = matrix2.getColumn();
	if (((_type == 1 || _type == 2) && (row_1 != row_2)) || ((_type == 3 || _type == 4) && (column_1 != column_2)))
	{
		return Matrix();
	}

	Matrix blockvec;
	switch (_type)
	{
	case 1:
	{
		blockvec = Matrix(row_1, column_1 + column_2);
		for (int i = 0; i < row_1; i++)
		{
			for (int j = 0; j < column_1; j++)
			{
				blockvec[i][j] = matrix1[i][j];
			}
		}
		for (int i = 0; i < row_1; i++)
		{
			for (int j = 0; j < column_2; j++)
			{
				blockvec[i][column_1 + j] = matrix2[i][j];
			}
		}
		break;
	}
	case 2:
	{
		blockvec = Matrix(row_1, column_1 + column_2);
		for (int i = 0; i < row_1; i++)
		{
			for (int j = 0; j < column_2; j++)
			{
				blockvec[i][j] = matrix2[i][j];
			}
		}
		for (int i = 0; i < row_1; i++)
		{
			for (int j = 0; j < column_1; j++)
			{
				blockvec[i][column_2 + j] = matrix1[i][j];
			}
		}
		break;
	}
	case 3:
	{
		blockvec = Matrix(row_1 + row_2, column_1);
		for (int j = 0; j < column_1; j++)
		{
			for (int i = 0; i < row_1; i++)
			{
				blockvec[i][j] = matrix1[i][j];
			}
		}
		for (int j = 0; j < column_1; j++)
		{
			for (int i = 0; i < row_2; i++)
			{
				blockvec[i + row_1][j] = matrix2[i][j];
			}
		}
		break;
	}
	case 4: {
		blockvec = Matrix(row_1 + row_2, column_1);
		for (int j = 0; j < column_1; j++)
		{
			for (int i = 0; i < row_2; i++)
			{
				blockvec[i][j] = matrix2[i][j];
			}
		}
		for (int j = 0; j < column_1; j++)
		{
			for (int i = 0; i < row_1; i++)
			{
				blockvec[i + row_2][j] = matrix1[i][j];
			}
		}
		break;
	}
	default:
		std::cerr << "Fault input!" << std::endl;
		return Matrix();
		break;
	}

	return blockvec;
}
//矩阵拆分，第二个参数是类型：true：横着拆；false：竖着拆； 
// 第三个参数是拆分的行或列的索引（是索引！！！）从这一行（或列）的下面（或右边）拆。
std::pair<Matrix, Matrix> LAC::M_split(Matrix& matrix, bool _type, int split_index)
{
	int row_ = matrix.getRow(), column_ = matrix.getColumn();
	Matrix mat1, mat2;
	if (_type)//横着拆	
	{
		if (split_index < 0 || split_index >= column_)
		{
			return std::pair<Matrix, Matrix>();
		}
		else if (split_index == column_ - 1)//如果在边上拆
		{
			mat1 = matrix;
			mat2 = Matrix(row_, 0);
		}
		else//正常拆分
		{
			mat1 = Matrix(row_, split_index + 1), mat2 = Matrix(row_, column_ - split_index - 1);
			for (int i = 0; i < row_; i++)
			{
				for (int j = 0; j < split_index + 1; j++)
				{
					mat1[i][j] = matrix[i][j];
				}
			}
			for (int i = 0; i < row_; i++)
			{
				for (int j = split_index + 1; j < column_; j++)
				{
					mat2[i][j - split_index - 1] = matrix[i][j];
				}
			}
		}
	}
	else//竖着拆
	{
		if (split_index < 0 || split_index >= row_)
		{
			return std::pair<Matrix, Matrix>();
		}
		else if (split_index == row_ - 1)//如果在边上拆
		{
			mat1 = matrix;
			mat2 = Matrix(0, column_);
		}
		else//正常拆分
		{
			mat1 = Matrix(split_index + 1, column_), mat2 = Matrix(row_ - split_index - 1, column_);
			for (int i = 0; i < split_index + 1; i++)
			{
				for (int j = 0; j < column_; j++)
				{
					mat1[i][j] = matrix[i][j];
				}

			}
			for (int i = split_index + 1; i < row_; i++)
			{
				for (int j = 0; j < column_; j++)
				{
					mat2[i - split_index - 1][j] = matrix[i][j];
				}
			}
		}
	}

	return std::make_pair(mat1, mat2);
}

//单位矩阵有关

//生成一个order阶的单位矩阵
Matrix LAC::M_generateEleMat(int order)
{
	Matrix temp(order, order);
	for (int i = 0; i < order; i++)
	{
		temp[i][i] = 1;
	}
	return temp;
}
//判断是不是单位矩阵
bool LAC::M_isEleMat(Matrix& matrix)
{
	if (matrix.getRow() != matrix.getColumn())return false;
	int order = matrix.getRow();

	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (matrix[i][j] != 0)return false;
		}
		for (int j = i + 1; j < order; j++)
		{
			if (matrix[i][j] != 0)return false;
		}
	}
	return true;
}


//秩有关

//对矩阵进行初等行变换求秩(改变原来矩阵）（用户交互）
int LAC::S_getRank(Matrix& matrix)
{
	while (true)
	{
		bool _sign = this->M_elementaryRowTransformation(matrix);
		if (!_sign)
		{
			std::cerr << "TRANSFORMATION FAILED!" << std::endl;
			system("pause");
			return 0;
		}
		//检查是不是行阶梯形
		int type_judge = this->M_typeJudge(matrix);
		if (type_judge != 1 && type_judge != 2 && type_judge != 3)
		{
			std::cerr << "The matrix is NOT row echlon form (行阶梯形) !" << std::endl;
			std::cerr << "Continue your transformation?" << std::endl;
			std::cerr << "1.Yes  2.No" << std::endl;
			int choice = 0;
			while (true)
			{
				std::cin >> choice;
				if (choice == 1)
				{
					system("cls");
					break;
				}
				else if (choice == 2)
				{
					std::cerr << "TRANSFORMATION HALTED!" << std::endl;
					system("pause");
					return 0;
				}
				else
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					continue;
				}
			}
			if (choice == 1)continue;
		}
		break;
	}

	//变换成功，根据零行数量间接得到矩阵的秩
	int _rank = 0;
	bool is_row_zeroline = true;
	for (int i = matrix.getRow() - 1; i != -1; i--)
	{
		for (int j = 0; j < matrix.getColumn(); j++)
		{
			if (matrix[i][j] != 0)
			{
				_rank++;
				break;
			}
		}
	}
	std::cout << "Rank of the matrix is : " << _rank << std::endl;
	return _rank;
}

//基与矩阵

//鉴定基是否为合格的基(行一致，列为1)
bool LAC::M_isBasis(const Basis& vec)
{
	if (vec.empty())return false;
	int base_size = vec.at(0).size();
	for (const auto& base : vec)
	{
		if (base.size() != base_size || base.at(0).size() != 1)return false;
	}
	return true;
}
//将基（列向量)合并为矩阵
Matrix LAC::M_mergeBasis(const Basis& basis)
{
	if (!M_isBasis(basis))return Matrix();
	Matrix result_matrix = Matrix(basis.at(0));
	for (int i = 1; i < basis.size(); i++)
	{
		Matrix to_merge(basis.at(i));
		result_matrix = this->M_concatenate(result_matrix, to_merge, 1);
	}
	return result_matrix;
}
//将矩阵拆成基，分为行拆和列拆(true拆成列向量，false拆成行向量）
Basis LAC::M_takeBasis(Matrix& matrix, bool _type)
{
	int row_ = matrix.getRow(), column_ = matrix.getColumn();
	if (row_ < 1 || column_ < 1)return Basis();
	Basis  basis_vec;
	if (_type)
	{
		//拆成列向量
		basis_vec = Basis(column_, ContentVec(row_, std::vector<double>(1, 0)));
		for (int i = 0; i < row_; i++)
		{
			for (int j = 0; j < column_; j++)
			{
				basis_vec[j][i][0] = matrix[i][j];
			}
		}
	}
	else
	{
		//拆成行向量
		basis_vec = Basis(row_, ContentVec(1, std::vector<double>(column_, 0)));
		for (int i = 0; i < row_; i++)
		{
			for (int j = 0; j < column_; j++)
			{
				basis_vec[i][0][j] = matrix[i][j];
			}
		}
	}
	return basis_vec;
}
//获取从基X到基Y的过渡矩阵P,XP=Y
Matrix LAC::M_getTransition(const Basis& basisX, const Basis& basisY)
{
	if (!M_isBasis(basisX) || !M_isBasis(basisY))return Matrix();
	Matrix matX = M_mergeBasis(basisX), matY = M_mergeBasis(basisY);
	if (matX == Matrix() || matY == Matrix()
		|| !matX.isSquare() || !matY.isSquare()
		|| matX.getRow() != matY.getRow())return Matrix();
	Det temp_det = this->M_takeDet(matX);
	if (D_getValue(temp_det) == 0)return Matrix();
	Matrix inverseX = this->M_getInverse(matX);
	return inverseX * matY;
}
//传入基(列向量)，判断是否正交
bool LAC::M_isOrthogonal(const Basis& basis)
{
	if (!M_isBasis(basis))return false;
	for (int i = 0; i < basis.size() - 1; i++)
	{
		for (int j = i; j < basis.size(); j++)
		{
			double inner_product = basis[i] * basis[j];
			if (inner_product != 0)return false;
		}
	}
	return true;
}
//求列向量在基下的坐标，使用y=B^-1 * a,其中B为basis拼起来的矩阵，a是vec
ContentVec LAC::M_getCoordinate(const ContentVec& vec_a, const Basis& basis_B)
{
	if (!M_isBasis(basis_B))return ContentVec();
	Matrix merged_B_inversed = M_mergeBasis(basis_B);
	if (merged_B_inversed == Matrix())return ContentVec();
	if (merged_B_inversed.getColumn() != vec_a.size())return ContentVec();
	if (merged_B_inversed.getRow() != merged_B_inversed.getColumn())return ContentVec();

	//检测B是否可逆
	Det judge_det = this->M_takeDet(merged_B_inversed);
	if (D_getValue(judge_det) == 0)return ContentVec();
	else merged_B_inversed = this->M_getInverse(merged_B_inversed);
	Matrix vec_matrix_a(vec_a);
	return (merged_B_inversed * vec_matrix_a).getValueVec();

}
//传入基，传出度量矩阵
Matrix LAC::M_getMetric(const Basis& basis)
{
	if (!M_isBasis(basis))return Matrix();
	int _order = basis.size();
	if (_order == 0)return Matrix();
	Matrix metric_matrix(_order, _order);
	for (int i = 0; i < _order; i++)
	{
		for (int j = 0; j < _order; j++)
		{
			metric_matrix[i][j] = basis[i] * basis[j];
		}
	}
	return metric_matrix;
}
//获取向量的模
double LAC::M_mod(ContentVec& vec)
{
	if (vec.empty())return 0;
	if (vec.size() != 1 && vec.at(0).size() != 1)return 0;
	double vec_model = 1;
	for (const auto& row : vec)for (const auto& val : row)vec_model += val * val;
	if (vec_model < 0)return 0;
	return std::sqrt(vec_model);
}
//对基进行施密特正交化，传出正交（不单位化）的基
Basis LAC::M_SchmidtOrthogonalization(const Basis& basis)
{
	if (!M_isBasis(basis))return Basis();
	//每个都是列向量，开始进行施密特正交化
	Basis orthogonal;//存放正交化的列向量的数组
	orthogonal.push_back(basis.at(0));
	for (int i = 1; i < basis.size(); i++)
	{
		ContentVec to_orthog = basis.at(i);
		//减去后面的向量
		for (int j = 0; j < i; j++)
		{
			double upper_num = basis.at(i) * orthogonal.at(j), lower_num = orthogonal.at(j) * orthogonal.at(j);
			double prefactor = 1.0 * upper_num / lower_num;//每个减去的向量前面的因子
			ContentVec to_minus = orthogonal.at(j);
			to_minus *= prefactor;
			to_orthog = to_orthog - to_minus;
		}
		orthogonal.push_back(to_orthog);
	}
	return orthogonal;
}
//对基的实参进行单位化
void LAC::M_normallize(Basis& basis)
{
	if (!M_isBasis(basis))return;
	for (ContentVec& base : basis)
	{
		ContentVec temp_vec(base);
		double _model = this->M_mod(temp_vec);
		for (auto& row : base)for (auto& val : row)
		{
			val /= (1.0 * _model);
		}
	}
}

//特征向量与特征值

//判断是否对称
bool LAC::M_isSymmetric(Matrix& matrix)
{
	if (!matrix.isSquare())return false;
	for (int i = 0; i < matrix.getRow(); i++)
	{
		for (int j = 0; j < matrix.getColumn(); j++)
		{
			if (matrix[i][j] != matrix[j][i])return false;
		}
	}
	return true;
}
//获取矩阵的迹
double LAC::M_getTrace(Matrix& matrix)
{
	if (matrix == Matrix() || !matrix.isSquare())return 0;
	double _trace = 0;
	for (int i = 0; i < matrix.getRow(); i++)
	{
		_trace += matrix[i][i];
	}
	return _trace;
}
//验证是否为特征值
bool LAC::M_isEigenValue(const Matrix& matrix, double λ)
{
	if (!matrix.isSquare() || matrix == Matrix())return false;
	//|λE-A|=0
	Matrix λE = this->M_generateEleMat(matrix.getRow());
	for (int i = 0; i < matrix.getRow(); i++)
	{
		λE[i][i] *= λ;
	}
	λE -= matrix;
	Det temp_det = this->M_takeDet(λE);
	if (this->D_getValue(temp_det) == 0)return true;
	else return false;

}
//获取所有特征向量，返回特征值和特征向量对组的map(用户交互)
std::map<double, Basis> LAC::M_getEigenVector(Matrix& matrix)
{
	if (matrix == Matrix())return std::map<double, Basis>();
	if (matrix.getRow() != matrix.getColumn())return std::map<double, Basis>();
	if (!this->M_isSymmetric(matrix))return std::map<double, Basis>();

	std::map<double, Basis>eigen_pairs;//存放特征值和特征向量对组的map
	std::vector<double>recordings;//λ记录

	while (true)
	{
		system("cls");
		std::cout << "Present matrix is below:" << std::endl;
		this->show(matrix);
		if (!recordings.empty())
		{
			std::cout << "Present λ:";
			for (const double& _lambda : recordings)
			{
				std::cout << _lambda << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "Please calculate λ and input them (if 114514 inputed , you will exit):" << std::endl;
		double λ;
		//计算特征向量
		while (true)
		{
			std::cin >> λ;
			if (λ == 114514)return eigen_pairs;
			if (!this->M_isEigenValue(matrix, λ))
			{
				//如果不是特征值
				std::cerr << "The value is NOT λ of the matrix ! Please input again!" << std::endl;
				continue;
			}
			auto ret = std::find_if(recordings.begin(), recordings.end(), [&](const double& record_λ) {return λ == record_λ; });
			if (ret != recordings.end())
			{
				//如果重复，需要重新输入
				std::cerr << "The λ is the same with one of those you have found,please input λ again:" << std::endl;
				continue;
			}
			//是λ,求解特征向量
			system("cls");
			recordings.push_back(λ);
			Matrix λE = this->M_generateEleMat(matrix.getRow());
			for (int i = 0; i < matrix.getRow(); i++)
			{
				λE[i][i] *= λ;
			}
			LinearSystem temp_system(λE - matrix, Matrix(matrix.getRow(), 1));
			ContentVec fundamental_solutions = this->S_solveHomo(temp_system);//解临时方程组
			if (fundamental_solutions == ContentVec())
			{
				std::cerr << "Solution has failed." << std::endl;
				return eigen_pairs;
			}
			system("cls");
			std::cout << "Successfully solved!" << std::endl;
			std::cout << "The eigen-vector of the matrix\n" << std::endl;
			this->show(matrix);
			std::cout << "\nis:\n" << std::endl;
			this->S_showSol(make_pair(fundamental_solutions, ContentVec()));

			Basis eigen_vec;
			if (fundamental_solutions.at(0).size() > 1)
			{
				//需要分割为几个小的列向量
				Matrix temp_matrix(fundamental_solutions);
				eigen_vec = this->M_takeBasis(temp_matrix, true);
				if (eigen_vec == Basis())
				{
					std::cerr << "Fail transporting fundamental solutions into column vector!" << std::endl;
				}
			}
			else
			{
				eigen_vec.push_back(fundamental_solutions);
			}
			eigen_pairs.insert(make_pair(λ, eigen_vec));//存放，进行下一次寻找特征向量
			break;
		}
		system("pause");
	}


}
//普通对角化,传出P和diag（用户交互）
std::pair<Matrix, Matrix> LAC::M_normalDiaglization(Matrix& matrix)
{
	//获取特征向量
	if (!matrix.isSquare() || matrix == Matrix() || !this->M_isSymmetric(matrix))
	{
		std::cerr << "The matrix is NOT fit for diglization!" << std::endl;
		return std::pair<Matrix, Matrix>();
	}
	std::map<double, Basis> eigen_map = this->M_getEigenVector(matrix);
	if (eigen_map == std::map<double, Basis>())
	{
		std::cerr << "Diaglization failed!" << std::endl;
		return std::pair<Matrix, Matrix>();
	}

	int diag_order = 0;//传出diag的总阶数
	for (auto& kv : eigen_map)
	{
		diag_order += kv.second.size();
	}

	Matrix mat_diag = this->M_generateEleMat(diag_order);//传出的diag

	//将特征向量拼成P
	Basis eigen_vecs;//存放所有特征向量的对组（顺序和传出的diag对应，如果是重根需要按顺序排放）
	int place_index = 0;//排放特征值的索引
	for (auto& kv : eigen_map)
	{
		if (kv.second.size() == 1)
		{
			//如果不是重根，直接放
			eigen_vecs.push_back(kv.second.at(0));
			mat_diag[place_index][place_index] = kv.first;
			place_index++;
		}
		else if (kv.second.size() > 1)
		{
			//如果是重根需要按顺序排放
			for (int i = 0; i < kv.second.size(); i++)
			{
				eigen_vecs.push_back(kv.second.at(i));
				mat_diag[place_index][place_index] = kv.first;
				place_index++;
			}
		}
	}

	Matrix mat_P = M_mergeBasis(eigen_vecs);//传出的P

	if (mat_P == Matrix())
	{
		std::cerr << "Basis merging failed!" << std::endl;
		return std::pair<Matrix, Matrix>();
	}

	system("cls");
	std::cout << "Successfully diaglized !" << std::endl;
	std::cout << "\tP^-1 * A * P = Diag" << std::endl;
	std::cout << "P:" << std::endl;
	this->show(mat_P);
	std::cout << "Diag:" << std::endl;
	this->show(mat_diag);

	return make_pair(mat_P, mat_diag);

}
//正交对角化，传出P和diag（用户交互）
std::pair<Matrix, Matrix> LAC::M_orthogonalDiaglization(Matrix& matrix)
{
	//获取特征向量
	if (!matrix.isSquare() || matrix == Matrix() || !this->M_isSymmetric(matrix))
	{
		std::cerr << "The matrix is NOT fit for diglization!" << std::endl;
		return std::pair<Matrix, Matrix>();
	}
	std::map<double, Basis> eigen_map = this->M_getEigenVector(matrix);
	if (eigen_map == std::map<double, Basis>())
	{
		std::cerr << "Diaglization failed!" << std::endl;
		return std::pair<Matrix, Matrix>();
	}

	//对于每个特征值，如果不是重根则单位化，如果有重根则先施密特正交化再单位化
	for (auto& kv : eigen_map)
	{
		if (kv.second.size() > 1)
		{
			//重根，施密特正交化
			kv.second = this->M_SchmidtOrthogonalization(kv.second);
		}
		//单位化
		this->M_normallize(kv.second);
	}

	int diag_order = 0;//传出diag的总阶数
	for (auto& kv : eigen_map)
	{
		diag_order += kv.second.size();
	}

	Matrix mat_diag = this->M_generateEleMat(diag_order);//传出的diag

	//将特征向量拼成P
	Basis eigen_vecs;//存放所有特征向量的对组（顺序和传出的diag对应，如果是重根需要按顺序排放）
	int place_index = 0;//排放特征值的索引
	for (auto& kv : eigen_map)
	{
		if (kv.second.size() == 1)
		{
			//如果不是重根，直接放
			eigen_vecs.push_back(kv.second.at(0));
			mat_diag[place_index][place_index] = kv.first;
			place_index++;
		}
		else if (kv.second.size() > 1)
		{
			//如果是重根需要按顺序排放
			for (int i = 0; i < kv.second.size(); i++)
			{
				eigen_vecs.push_back(kv.second.at(i));
				mat_diag[place_index][place_index] = kv.first;
				place_index++;
			}
		}
	}

	Matrix mat_P = M_mergeBasis(eigen_vecs);//传出的P

	if (mat_P == Matrix())
	{
		std::cerr << "Basis merging failed!" << std::endl;
		return std::pair<Matrix, Matrix>();
	}

	system("cls");
	std::cout << "Successfully diaglized !" << std::endl;
	std::cout << "\tP^T * A * P = Diag" << std::endl;
	std::cout << "P:" << std::endl;
	this->show(mat_P);
	std::cout << "Diag:" << std::endl;
	this->show(mat_diag);

	return make_pair(mat_P, mat_diag);
}
//通过普通对角化获取A^n（用户交互）
Matrix LAC::M_getPowerByDiaglization(Matrix& matrix, int _figure)
{
	system("cls");
	std::pair<Matrix, Matrix>p_and_diag = this->M_normalDiaglization(matrix);
	if (p_and_diag == std::pair<Matrix, Matrix>())return Matrix();
	Matrix mat_P = p_and_diag.first, mat_diag = p_and_diag.second;
	if (!mat_P.isSquare() || !mat_diag.isSquare() || mat_P.getColumn() != mat_diag.getRow())
	{
		std::cerr << "The eigen-vectors are too less! Please find edequate eigen-vectors!" << std::endl;
		return Matrix();
	}
	for (int i = 0; i < mat_diag.getRow(); i++)
	{
		mat_diag[i][i] = std::pow(mat_diag[i][i], _figure);
	}
	Matrix inverse_mat_P = this->M_getInverse(mat_P);
	if (inverse_mat_P == Matrix())
	{
		std::cerr << "P is NOT inversable!" << std::endl;
		return Matrix();
	}

	Matrix result_matrix = (mat_P * mat_diag) * inverse_mat_P;

	std::cout << "The result is :" << std::endl;
	this->show(result_matrix);

	return result_matrix;
}

//二次型中的部分功能

//判断是不是对角矩阵
bool LAC::M_isDiag(Matrix& matrix)
{
	if (matrix == Matrix() || !matrix.isSquare() || !this->M_isSymmetric(matrix))return false;
	for (int i = 0; i < matrix.getRow(); i++)
	{
		for (int j = 0; j < matrix.getColumn(); j++)
		{
			if (i != j && matrix[i][j] != 0)return false;
		}
	}
	return true;
}
//二次型中的合同变换法，传出第一个为C^T*A*C,第二个为C（用户交互）
std::pair<Matrix, Matrix> LAC::M_contractDiaglization(Matrix& matrix)
{
	try
	{
		if (!matrix.isSquare() || matrix == Matrix() || !this->M_isSymmetric(matrix))
		{
			std::cerr << "The matrix is NOT fit for diglization!" << std::endl;
			return std::pair<Matrix, Matrix>();
		}

		Matrix temp_elemat = this->M_generateEleMat(matrix.getRow());
		Matrix concatenated = this->M_concatenate(matrix, temp_elemat, 3);//上下拼接

		int trans_round = 1;
		std::vector<Matrix>history;//历史记录

		while (true)
		{
			system("cls");
			std::cout << "CONTRACT  TRANSFORMATION" << std::endl;
			std::cout << "Present matrix is below:" << std::endl;
			this->show(concatenated);
			std::cout << "Choices are below:" << std::endl;
			std::cout << "1.Row adding and column adding \n2.Row number multiply and column number multiply \n3.Row exchange and column exchange \n4.Withdraw  \n0.Exit" << std::endl;


			int choice = 0;
			std::cin >> choice;

			system("cls");
			std::cout << "CONTRACT  TRANSFORMATION" << std::endl;
			std::cout << "ROUND : " << trans_round << std::endl;
			std::cout << "Present matrix is below:" << std::endl;
			this->show(concatenated);
			if (choice == 1)//Row adding and column adding
			{
				history.push_back(Matrix(concatenated));//拷贝一份给history
				std::cout << "Ri + k*Rj and Ci + k*Cj" << std::endl << "Input i,j and k(i does NOT equal to j)(if three 0 inputed,you will exit):" << std::endl;
				int i, j;
				double k;

				while (true)
				{
					std::cin >> i >> j >> k;
					if (i == 0 && j == 0 && k == 0)
					{
						break;
					}
					i--, j--;//变为索引
					if (i < 0 || i >= concatenated.getColumn() || j < 0 || j >= concatenated.getColumn() || i == j)
					{
						std::cerr << REINPUT_PHRASE << std::endl;
						continue;
					}
					this->M_onceRowElementaryTransformation(concatenated, i, j, k);
					this->M_onceColumnElementaryTransformation(concatenated, i, j, k);
					break;
				}
				if (i == 0 && j == 0 && k == 0)continue;

			}
			else if (choice == 2)//Row number multiply and column number multiply
			{
				history.push_back(Matrix(concatenated));//拷贝一份给history
				int mul_index;
				double mul_num;
				std::cout << "Input the row (column) you want to multiply:" << std::endl;
				std::cin >> mul_index;
				if (mul_index <= 0 || mul_index > concatenated.getColumn())
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				mul_index--;//变为索引
				std::cout << "Input the number to multiply:" << std::endl;
				std::cin >> mul_num;

				for (int i = 0; i < concatenated.getColumn(); i++)
				{
					concatenated[mul_index][i] *= mul_num;//列数乘
					concatenated[i][mul_index] *= mul_num;//行数乘
				}
			}
			else if (choice == 3)//Row exchange and column exchange
			{
				history.push_back(Matrix(concatenated));//拷贝一份给history
				int index1, index2;
				std::cout << "Input two index for exchange:" << std::endl;
				std::cin >> index1 >> index2;
				if (index1 <= 0 || index1 > concatenated.getColumn() || index2 <= 0 || index2 > concatenated.getColumn() || index1 == index2)
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				index1--, index2--;//变为索引
				std::swap(concatenated[index1], concatenated[index2]);//行交换
				//列交换
				for (int i = 0; i < concatenated.getRow(); i++)
				{
					std::swap(concatenated[i][index1], concatenated[i][index2]);
				}

			}
			else if (choice == 4)//Withdraw
			{
				if (trans_round == 1)
				{
					std::cerr << "You can't withdraw in the first round!" << std::endl;
					system("pause");
				}
				else
				{
					concatenated = history.at(trans_round - 2);
					auto it = history.begin();
					it += trans_round - 2;
					history.erase(it);
					trans_round--;
				}
				continue;
			}
			else if (choice == 0)
			{
				system("cls");
				std::pair<Matrix, Matrix>result_pair = this->M_split(concatenated, false, matrix.getColumn());//拆成两个矩阵
				if (!this->M_isDiag(result_pair.first))
				{
					std::cerr << "The upper matrix is NOT diag matrix . Continue transforming?\n1.Yes  0.Exit" << std::endl;
					int choice;
					std::cin >> choice;
					if (choice == 1)
					{
						//继续合同变换
						continue;
					}
					else if (choice == 2)
					{
						return std::pair<Matrix, Matrix>();
					}
					else
					{
						std::cerr << ERR_PHRASE << std::endl;
						return std::pair<Matrix, Matrix>();
					}

				}
				//变换成功
				std::cout << "CONTRACT  TRANSFORMATION" << std::endl;
				std::cout << "C^T * A * C = Diag" << std::endl;
				std::cout << "Final matrixes are below:\nC:" << std::endl;
				this->show(result_pair.first);
				std::cout << "Diag:" << std::endl;
				this->show(result_pair.second);
				return result_pair;
			}
			else
			{
				std::cerr << ERR_PHRASE << std::endl;
				return std::pair<Matrix, Matrix>();
			}

			trans_round++;//轮次+1
			//浮点数精度不够，需要在达到阈值时简化
			ContentVec casted = concatenated.getValueVec();
			this->castVal(casted);
			concatenated.setContentVec(casted);
		}
	}
	catch (exception& err)
	{
		std::cerr << err.what() << std::endl;
		std::cerr << "Operation has been withdrawn . Please transform the matrix again or contact relevant technological people!" << std::endl;
		system("pause");
		system("cls");
		return std::pair<Matrix, Matrix>();
	}
}


//行列式专有

//基本计算工具

//转变为矩阵,注：忽略了premierNum!(因为对矩阵不影响）
Matrix LAC::D_takeMat(const Det& det)
{
	return Matrix(det.getOrder(), det.getOrder(), det.getValueVec());
}
//对某一行或某一列数乘某个数字，第二个参数是行或列：true:行，false:列；  第3个参数是要操作的行或列的索引（索引！！！）；
// 第4个是乘的数字.  ！！注意将prenum_除以number！！
void LAC::D_numMult(Det& det, bool _type, int index, double number)
{
	int order_ = det.getOrder();
	if (index < 0 || index >= order_)return;
	if (_type)//行乘法
	{
		for (int j = 0; j < order_; j++)
		{
			det[index][j] *= number;
		}
	}
	else//列乘法
	{
		for (int i = 0; i < order_; i++)
		{
			det[i][index] += number;
		}
	}
	det.setDet(order_, det.getValueVec(), det.getPreNum() / number);
}
//行列式转置，注意数乘一个-1
void LAC::D_transport(Det& det)
{
	int neworder_ = det.getOrder();
	ContentVec tempblock;
	tempblock.resize(neworder_);
	for (int i = 0; i < neworder_; i++)
	{
		tempblock[i].resize(neworder_);
	}
	//数值转移
	for (int i = 0; i < det.getRow(); i++)
	{
		for (int j = 0; j < det.getColumn(); j++)
		{
			tempblock[j][i] = det[i][j];
		}
	}
	det.setDet(neworder_, tempblock, det.getPreNum() * (-1));
}
//直接获取行列式的值 
double LAC::D_getValue(Det& det)
{
	if (det == Det())
	{
		return 0;
	}
	int order_ = det.getOrder();
	double type_judge = 1;
	switch (order_)
	{
	case 1:
		type_judge = det[0][0];
		break;
	case 2:
		type_judge = det[0][0] * det[1][1] - det[0][1] * det[1][0];
		break;
	case 3:
		type_judge = det[0][0] * (det[1][1] * det[2][2] - det[1][2] * det[2][1])
			- det[0][1] * (det[1][0] * det[2][2] - det[1][2] * det[2][0])
			+ det[0][2] * (det[1][0] * det[2][1] - det[1][1] * det[2][0]);
		break;
	case 4:
		type_judge = det[0][0] * (det[1][2] * det[2][3] * det[3][1] + det[1][3] * det[2][1] * det[3][2] + det[1][1] * det[2][2] * det[3][3])
			- det[0][1] * (det[1][2] * det[2][3] * det[3][0] + det[1][3] * det[2][0] * det[3][2] + det[1][0] * det[2][2] * det[3][3])
			+ det[0][2] * (det[1][0] * det[2][3] * det[3][1] + det[1][1] * det[2][0] * det[3][3] + det[1][3] * det[2][1] * det[3][0])
			- det[0][3] * (det[1][0] * det[2][1] * det[3][2] + det[1][1] * det[2][2] * det[3][0] + det[1][2] * det[2][0] * det[3][1]);
		break;
	default: // 对于五阶以上的，使用拉普拉斯展开（递归）
	{

		std::map<double, double>laplace_map;
		for (int i = 0; i < order_; i++)
		{
			for (int j = 0; j < order_; j++)
			{
				double centre_num = det[i][j];
				//拷贝出来一个，转成矩阵(拷贝出来的被销毁），取余子式
				Matrix temp_matrix = this->M_getMinor(i, j, D_takeMat(Det(det)));
				//将余子式转变为行列式
				Det result_det = M_takeDet(temp_matrix);
				//对行列式取值，和中心数值放进laplace_map
				double detnum = D_getValue(result_det);
				laplace_map.insert(make_pair(centre_num, detnum));
			}
		}
		std::for_each(laplace_map.begin(), laplace_map.end(), [&type_judge](const auto& kv) {
			type_judge += kv.first * kv.second;
			});
		break;

	}
	}
	type_judge *= det.getPreNum();


	return type_judge;
}

//行列式初等变换

//一次行列式初等行变换，变换成功输出true:row1+=row2*k
bool LAC::D_once_R_elementaryTransformation(Det& det, int row1, int row2, double k)
{
	int order_ = det.getOrder();
	if (row1 < 0 || row1 >= order_ || row2 < 0 || row2 >= order_ || row1 == row2)
	{
		throw out_of_range("out of range !");
	}
	for (int j = 0; j < order_; j++)
	{
		det[row1][j] += det[row2][j] * k;
	}
	return true;
}
//一次行列式初等列变换，变换成功输出true:column1+=column2*k
bool LAC::D_once_C_elementaryTransformation(Det& det, int column1, int column2, double k)
{
	int order_ = det.getOrder();
	if (column1 < 0 || column1 >= order_ || column2 < 0 || column2 >= order_ || column1 == column2)
	{
		throw out_of_range("out of range !");
	}
	for (int i = 0; i < order_; i++)
	{
		det[i][column1] += det[i][column2] * k;
	}
	return true;
}
//多次行列式初等变换函数（用户交互）
bool LAC::D_elementaryTransformation(Det& det)
{
	int trans_round = 1;
	std::vector<Det>history;//历史记录
	try
	{
		while (true)
		{
			system("cls");
			std::cout << "ELEMENTARY  TRANSFORMATION" << std::endl;
			std::cout << "Present det is below:" << std::endl;
			this->show(det);
			std::cout << "Choices are below:" << std::endl;
			std::cout << "1.Row adding  \n2.Column adding  \n3.Row number multiply  \n4.Column number multiply  \n5.Row exchange  \n6.Column exchange  \n7.Withdraw  \n0.Exit" << std::endl;


			int choice = 0;
			std::cin >> choice;

			system("cls");
			std::cout << "ELEMENTARY  TRANSFORMATION" << std::endl;
			std::cout << "ROUND : " << trans_round << std::endl;
			std::cout << "Present det is below:" << std::endl;
			this->show(det);
			if (choice == 1)//Row adding
			{
				history.push_back(Det(det));//拷贝一份给history
				std::cout << "Ri + k*Rj" << std::endl << "Input i,j and k(i does NOT equal to j)(if three 0 inputed,you will exit):" << std::endl;
				int i, j;
				double k;

				while (true)
				{
					std::cin >> i >> j >> k;
					if (i == 0 && j == 0 && k == 0)
					{
						break;
					}
					i--, j--;//变为索引
					if (i < 0 || i >= det.getOrder() || j < 0 || j >= det.getOrder() || i == j)
					{
						std::cerr << REINPUT_PHRASE << std::endl;
						continue;
					}
					this->D_once_R_elementaryTransformation(det, i, j, k);
					break;
				}
				if (i == 0 && j == 0 && k == 0)continue;

			}
			else if (choice == 2)//Column adding
			{
				history.push_back(Det(det));//拷贝一份给history
				std::cout << "Ci + k*Cj" << std::endl << "Input i,j and k(i does NOT equal to j)(if three 0 inputed,you will exit):" << std::endl;
				int i, j;
				double k;

				while (true)
				{
					std::cin >> i >> j >> k;
					if (i == 0 && j == 0 && k == 0)
					{
						break;
					}
					i--, j--;//变为索引
					if (i < 0 || i >= det.getOrder() || j < 0 || j >= det.getOrder() || i == j)
					{
						std::cerr << REINPUT_PHRASE << std::endl;
						continue;
					}
					this->D_once_C_elementaryTransformation(det, i, j, k);
					break;
				}
				if (i == 0 && j == 0 && k == 0)continue;
			}
			else if (choice == 3)//Row number multiply
			{
				history.push_back(Det(det));//拷贝一份给history
				int rowindex;
				double mul_num;
				std::cout << "Input the row you want to multiply:" << std::endl;
				std::cin >> rowindex;
				if (rowindex <= 0 || rowindex > det.getOrder())
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				rowindex--;//变为索引
				std::cout << "Input the number to multiply:" << std::endl;
				std::cin >> mul_num;
				for (int i = 0; i < det.getOrder(); i++)
				{
					det[rowindex][i] *= mul_num;
				}
				det.setDet(det.getOrder(), det.getValueVec(), 1.0 * (det.getPreNum()) / mul_num);//行列式前面数字改变
			}
			else if (choice == 4)//Column number multiply
			{
				history.push_back(Det(det));//拷贝一份给history
				int columnindex;
				double mul_num;
				std::cout << "Input the row you want to multiply:" << std::endl;
				std::cin >> columnindex;
				if (columnindex <= 0 || columnindex > det.getOrder())
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				columnindex--;//变为索引
				std::cout << "Input the number to multiply:" << std::endl;
				std::cin >> mul_num;
				for (int i = 0; i < det.getOrder(); i++)
				{
					det[i][columnindex] *= mul_num;
				}
				det.setDet(det.getOrder(), det.getValueVec(), 1.0 * (det.getPreNum()) / mul_num);//行列式前面数字改变
			}
			else if (choice == 5)//Row exchange
			{
				history.push_back(Det(det));//拷贝一份给history
				int row1, row2;
				std::cout << "Input two row index for exchange:" << std::endl;
				std::cin >> row1 >> row2;
				if (row1 <= 0 || row1 > det.getOrder() || row2 <= 0 || row2 > det.getOrder() || row1 == row2)
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				row1--, row2--;//变为索引
				std::swap(det[row1], det[row2]);
				det.setDet(det.getOrder(), det.getValueVec(), (-1.0) * (det.getPreNum()));//行列式前面数字改变
			}
			else if (choice == 6)//Column exchange
			{
				history.push_back(Det(det));//拷贝一份给history
				int column1, column2;
				std::cout << "Input two column index for exchange:" << std::endl;
				std::cin >> column1 >> column2;
				if (column1 <= 0 || column1 > det.getOrder() || column2 <= 0 || column2 > det.getOrder() || column1 == column2)
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				column1--, column2--;//变为索引
				std::swap(det[column1], det[column2]);
				det.setDet(det.getOrder(), det.getValueVec(), (-1.0) * (det.getPreNum()));//行列式前面数字改变
			}
			else if (choice == 7)//Withdraw
			{
				if (trans_round == 1)
				{
					std::cerr << "You can't withdraw in the first round!" << std::endl;
					system("pause");
				}
				else
				{
					det = history.at(trans_round - 2);
					auto it = history.begin();
					it += trans_round - 2;
					history.erase(it);
					trans_round--;
				}
				continue;
			}
			else if (choice == 0)
			{
				system("cls");
				std::cout << "ELEMENTARY  TRANSFORMATION" << std::endl;
				std::cout << "Final det is below:" << std::endl;
				this->show(det);
				return true;
			}
			else
			{
				std::cerr << ERR_PHRASE << std::endl;
				return false;
			}

			trans_round++;//轮次+1
			//浮点数精度不够，需要在达到阈值时简化
			ContentVec casted = det.getValueVec();
			this->castVal(casted);
			det.setDet(det.getOrder(), casted, det.getPreNum());
		}
	}
	catch (exception& err)
	{
		std::cerr << err.what() << std::endl;
		std::cerr << "Operation has been withdrawn . Please transform the det again or contact relevant technological people!" << std::endl;
		system("pause");
		system("cls");
		return false;
	}
}
//初等变换求行列式的值，求值成功之后返回这个值 （用户交互）
double LAC::D_getValue_Eletrans(Det& det)
{
	if (det == Det())
	{
		return 0;
	}
	else if (det.getOrder() == 1 || det.getOrder() == 2 || det.getOrder() == 3)
	{
		return D_getValue(det);
	}
	//阶数大于等于4，需要进行初等变换
	std::cout << "Click to begin transforming." << std::endl;
	system("pause");
	system("cls");

	while (true)
	{
		//开始变换求值
		bool _sign = this->D_elementaryTransformation(det);
		if (!_sign)
		{
			std::cerr << "TRANSFORMATION FAILED!" << std::endl;
			system("pause");
			return 0;
		}

		//变换完成之后
		if (!this->D_isTriangDet(det))//如果变换之后不是三角行列式
		{
			std::cerr << "NOT Triangle Det!" << std::endl;
			std::cerr << "Continue your transformation?" << std::endl;
			std::cerr << "1.Yes  2.No" << std::endl;
			int choice = 0;
			while (true)
			{
				std::cin >> choice;
				if (choice == 1)
				{
					system("cls");
					break;
				}
				else if (choice == 2)
				{
					std::cerr << "TRANSFORMATION HALTED!" << std::endl;
					system("pause");
					return 0;
				}
				else
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					continue;
				}
			}
			if (choice == 1)continue;
		}

		break;
	}


	//变换之后是三角行列式，可以求值
	return this->D_getValue_Triang(det);


}

//三角行列式有关

//判断是不是三角行列式
bool LAC::D_isTriangDet(Det& det)
{
	bool is_upper_triang = true;
	bool is_lower_triang = true;
	int _order = det.getOrder();

	// 判断是否为上三角行列式
	for (int i = 0; i < _order; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (det[i][j] != 0)
			{
				is_upper_triang = false;
				break;
			}
		}
		if (!is_upper_triang) break;
	}

	// 判断是否为下三角行列式
	for (int i = 0; i < _order; i++)
	{
		for (int j = i + 1; j < _order; j++)
		{
			if (det[i][j] != 0)
			{
				is_lower_triang = false;
				break;
			}
		}
		if (!is_lower_triang) break;
	}

	// 如果是上三角或下三角之一，则返回true
	return is_upper_triang || is_lower_triang;
}
//获取三角行列式的值,包含了上面的函数
double LAC::D_getValue_Triang(Det& det)
{
	if (!this->D_isTriangDet(det))return 0;

	double type_judge = 1;
	for (int i = 0; i < det.getOrder(); i++)
	{
		type_judge *= det[i][i];
	}
	//最后要乘以premierNum
	type_judge *= det.getPreNum();


	return type_judge;
}






//线性方程组专有

//方程组的A求秩（用户交互）
int LAC::S_getRank(LinearSystem& system_)
{
	Matrix A = system_.getA();//得到A的拷贝
	int _rank = S_getRank(A);
	if (_rank == 0)
	{
		std::cerr << "LinearSystem transformation failed!" << std::endl;
		system("pause");
	}
	else
	{
		system("cls");
		std::cout << "Final system is below :" << std::endl;
		LinearSystem temp_linear(A, Matrix(system_.getARow(), 1));
		this->show(temp_linear);
		std::cout << "Rank of the system is : " << _rank << std::endl;
	}

	return _rank;
}
//解线性方程组--初等变换法 (拷贝)（用户交互）
ContentVec LAC::S_solveHomo(const LinearSystem& system_)
{
	//解齐次方程组（输出的是基础解系）（基础解系 竖 着 放！）
	//步骤：
	//1.先根据A的行列式判断是否有非零解；
	//2.将A初等变换化为行阶梯形或行最简形或标准型，并判断；
	//3.由于在1中已经排除r=row_的情况，故不可能出现唯一解；
	//4.如果有自由未知量(r<row_)，则先判断出X里面自由未知量的下标，然后继续初等行变换为行最简形，按照“好方法”得到X所有项的值组成的数组（基础解系）；
	//5.输出这个基础解系。
	try
	{
		if (system_.getARow() > system_.getAColumn())
		{
			std::cerr << "Equations are too much!" << std::endl;
			system("pause");
			return ContentVec();
		}
		Matrix A = system_.getA();
		Det adet = M_takeDet(A);
		int _rank_of_A = 0;
		int conti;//下面会用到的一个量，当没有成功变换时重新变换
		while (true)
		{
			system("cls");
			if (system_.getA().isSquare() && this->D_getValue(adet) != 0)//如果A是方阵并可以用行列式判断
			{
				std::cout << "The coefficient determinant of this system is NOT 0 ！" << std::endl
					<< "There is NO non-zero solution !" << std::endl;
				system("pause");
				return ContentVec();
			}
			else//不是方阵，或者是方阵但是不能用行列式，需要初等行变换得到秩
			{
				_rank_of_A = S_getRank(A);

				if (_rank_of_A == 0) return ContentVec();
				else if (_rank_of_A != 0 && _rank_of_A != system_.getARow()) {}
				else
				{
					std::cout << "The coefficient determinant of this system is NOT 0 ！" << std::endl
						<< "There is NO non-zero solution !" << std::endl;
					system("pause");
					return ContentVec();
				}
			}
			//此时必然是0<r<row_
			std::vector<int> free_unknown;//存放自由未知量的列索引的数组
			for (int i = _rank_of_A; i < system_.getAColumn(); i++)
			{
				free_unknown.push_back(i);
			}

			int _type;
			while (true)
			{
				_type = this->M_typeJudge(A);
				if (_type == 1)
				{
					//需要继续变换为行最简形
					system("cls");
					std::cout << "Present matrix is below:" << std::endl;
					this->show(A);
					std::cout << "Type of the matrix:" << _type << std::endl;
					std::cout << "The matrix is NOT row simplest.Continue transforming?\n1.Yes  2.Exit" << std::endl;
					while (true)
					{
						std::cin >> conti;
						if (conti == 1)break;
						else if (conti == 2)return ContentVec();
						else
						{
							std::cerr << REINPUT_PHRASE << std::endl;
							continue;
						}
					}
					if (conti == 1)break;//当没有成功变换时重新变换

					bool _sign = this->M_elementaryRowTransformation(A);
					if (!_sign)
					{
						std::cerr << "TRANSFORMATION FAILED!" << std::endl;
						system("pause");
						return ContentVec();
					}

					//变换之后判断是不是行最简形
					continue;
				}
				else//已经是行最简形,使用方程组法算法
				{
					int num_of_fund = free_unknown.size();//基础解系的数量

					ContentVec fundamental_solutions(system_.getAColumn(), std::vector<double>(num_of_fund, 0));//基础解系，竖着放

					ContentVec zero_one_vec(num_of_fund, std::vector<double>(num_of_fund, 0));//0 1 变换的数组，竖着放
					for (int i = 0; i < num_of_fund; i++)zero_one_vec[i][i] = 1;

					//先将zero_one_vec的量赋值进基础解系
					for (int i = 0; i < num_of_fund; i++)
					{
						for (int j = 0; j < num_of_fund; j++)
						{
							fundamental_solutions[free_unknown[i]][j] = zero_one_vec[i][j];//自由未知量列索引变成基础解系的行索引!
						}
					}
					//再由行最简形A构成的方程组得到剩余的值，放进基础解系
					std::vector<int>rest_col_indexes;//存放其余元素的列索引
					std::vector<int>all_col_indexes;//存放所有列索引
					for (int i = 0; i < system_.getAColumn(); i++)
					{
						all_col_indexes.push_back(i);
					}
					//取rest_col_indexes是free_unknown和all_col_indexes的差集
					std::set_difference(free_unknown.begin(), free_unknown.end(),
						all_col_indexes.begin(), all_col_indexes.end(),
						std::back_inserter(rest_col_indexes));

					for (int i = 0; i < rest_col_indexes.size(); i++)
					{
						for (int j = 0; j < num_of_fund; j++)
						{
							fundamental_solutions[rest_col_indexes[i]][j] = 0;
							for (int k = 0; k < num_of_fund; k++)
							{
								fundamental_solutions[rest_col_indexes[i]][j] -= A[i][free_unknown[j]] * zero_one_vec[j][k];
							}
						}
					}

					//基础解系赋值完成！
					system("cls");
					std::cout << "Homo system has been successfullt solved!" << std::endl << "The general solution is below:" << std::endl;
					this->S_showSol(std::make_pair(fundamental_solutions, ContentVec()));
					system("pause");
					return fundamental_solutions;

				}
			}
			if (conti == 1)continue;//当没有成功变换时重新变换
		}


	}
	catch (out_of_range& err)
	{
		std::cerr << err.what() << std::endl;
		return ContentVec();
	}
	catch (...)
	{
		std::cerr << "An unknown exception occurred!" << std::endl;
		return ContentVec();
	}

}
//解非齐次方程组（输出first为相应齐次方程组的基础解系，second为非齐次通解）（用户交互）
std::pair<ContentVec, ContentVec> LAC::S_solveUnhomo(const LinearSystem& system_)
{
	//步骤：
	//1.先将增广矩阵初等变换为行阶梯形（记得判断），然后判断r(A) == r(A, b)，如果不等就止步于此；
	//2.如果相等，就解相应齐次方程组的基础解系；
	//3.弄出来一个非齐次特解（手动，观察法），并判断是否符合，不符合就重新找；
	//4.找到了就输出基础解系和特解的对组。
	if (system_.getARow() > system_.getAColumn())
	{
		std::cerr << "Equations are too much!" << std::endl;
		system("pause");
		return std::pair<ContentVec, ContentVec>();
	}
	Matrix A = system_.getA(), B = system_.getB();
	int _rank_of_A;
	Matrix extended = this->M_concatenate(A, B, 1);//增广矩阵
	int conti;//下面会用到的一个量，当没有成功变换时重新变换

	while (true)
	{
		//将增广矩阵初等变换为行阶梯形
		system("cls");
		bool _sign = this->M_elementaryRowTransformation(extended);
		if (!_sign)
		{
			std::cerr << "TRANSFORMATION FAILED!" << std::endl;
			system("pause");
			return std::pair<ContentVec, ContentVec>();
		}
		//判断变换之后是否为行阶梯形
		int _type = this->M_typeJudge(extended);
		if (_type != 1 && _type != 2 && _type != 3)
		{
			//不是行阶梯形，回炉重造
			system("cls");
			std::cout << "Present matrix is below:" << std::endl;
			this->show(extended);
			std::cout << "Type of the matrix:" << _type << std::endl;
			std::cout << "The matrix is NOT row simplest.Continue transforming?\n1.Yes  2.Exit" << std::endl;
			while (true)
			{
				std::cin >> conti;
				if (conti == 1)break;
				else if (conti == 2)return std::pair<ContentVec, ContentVec>();
				else
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					continue;
				}
			}
			if (conti == 1)continue;//当没有成功变换时重新变换
		}
		else
		{
			//是行阶梯形，判断r(A) == r(A, b)
			//从最后一行开始找，如果是非零行就进入倒数下一行
			bool is_zerocol = true;//对 A的列 判断是否都为0
			bool is_solveable = true;//r(A) == r(A, b)
			for (int i = system_.getARow() - 1; i != -1; i--)
			{
				for (int j = 0; j < system_.getAColumn(); j++)//对 A的列 判断是否都为0
				{
					if (extended[i][j] != 0)
					{
						is_zerocol = false;
						break;
					}
				}
				if (is_zerocol)//如果A的列都是0，判断B的列
				{
					if (extended[i][system_.getAColumn()] != 0)
					{
						is_solveable = false;
						break;
					}
				}
			}

			//如果r(A) ！= r(A, b)，直接终止
			if (!is_solveable)
			{
				std::cout << "r(A) is NOT equal to r(A, b) ! The system has NO solutions.Click to exit." << std::endl;
				system("pause");
				return std::pair<ContentVec, ContentVec>();
			}

			//r(A) = r(A, b)，解相应齐次方程组的基础解系
			std::pair<Matrix, Matrix>temp_pair = this->M_split(extended, true, system_.getAColumn() - 1);
			LinearSystem temp_system(temp_pair.first, temp_pair.second);
			ContentVec fundamental_solutions = this->S_solveHomo(temp_system);
			if (fundamental_solutions == ContentVec())//如果没有解出来
			{
				system("cls");
				std::cerr << "You did NOT solve the homosystem." << std::endl;
				system("pause");
				return std::pair<ContentVec, ContentVec>();
			}
			//手动、观察法得到一个特解
			system("cls");
			std::cout << "Present system is below:" << std::endl;
			this->show(temp_system);
			std::cout << "Please observe the linear system and get a particular solution:" << std::endl;
			Matrix particular_solution(system_.getAColumn(), 1);//特解
			double cinnum;
			while (true)
			{
				for (int i = 0; i < system_.getAColumn(); i++)
				{
					std::cin >> cinnum;
					particular_solution[i][0] = cinnum;
				}
				//验证是否为真正特解,即验证原始的A*particular_solution==B
				if (system_.getA() * particular_solution == system_.getB())
				{
					std::cout << "Successfully input ! Click to show the General Solution of the system." << std::endl;
					system("pause");
					break;
				}
				else
				{
					//不是真正的特解，重新输入
					std::cout << "This is NOT one of the particular solutions of the system . Please input again!" << std::endl;
					continue;
				}
			}

			return std::make_pair(fundamental_solutions, particular_solution.getValueVec());

		}
	}

}
//以列向量相加的形式展示齐次或非齐次方程组的通解（或解，或无解），需要自动判断,传入是左边通解右边特解（竖着的）
void LAC::S_showSol(const std::pair<ContentVec, ContentVec>& solutions_pair)
{
	ContentVec general = solutions_pair.first, particular = solutions_pair.second;
	int mid = (general.size() % 2 == 0) ? (general.size() / 2 - 1) : ((general.size() - 1) / 2);//中间行的索引
	bool is_unhomo = (particular != ContentVec());
	for (int i = 0; i < general.size(); i++)
	{
		for (int j = 0; j < general.at(0).size(); j++)
		{
			if (i != mid)
			{
				std::cout << "\t[" << general[i][j] << "]\t\t";
				if (is_unhomo && j == general.at(0).size() - 1)
				{
					std::cout << "[" << particular[i][0] << "]\t";
				}
			}
			else
			{
				std::cout << "k" << j + 1 << "*\t[" << general[i][j] << "]\t";
				if (j != general.at(0).size() - 1)
				{
					std::cout << "+\t";
				}

				if (is_unhomo && j == general.at(0).size() - 1)
				{
					std::cout << "+\t[" << particular[i][0] << "]\t";
				}
			}
		}

		std::cout << std::endl;
	}


}

//解线性方程组--克拉默法则 (拷贝)

//判断是否适合克拉默法则（增广矩阵是一个N*（N+1）的）
bool LAC::S_isCramer(const LinearSystem& system)
{
	Matrix A = system.getA();
	std::cout << "Matrix A is:" << std::endl;
	this->show(A);
	Det detA = this->M_takeDet(A);
	std::cout << "Det A is:" << std::endl;
	this->show(detA);
	double valueA = this->D_getValue(detA);
	std::cout << "Value of A is:" << valueA << std::endl;
	std::cout << "Row of A is:" << system.getARow() << std::endl;
	std::cout << "Column of A is:" << system.getAColumn() << std::endl;
	return  (system.getARow() == system.getAColumn()) && (valueA != 0);
}
//在判断适合克拉默法则后生成去除这一列的行列式的数组，按顺序来分别是D1,D2,...,Dn,D；需要根据增广矩阵判断
std::vector<Det> LAC::S_generateRLD(const LinearSystem& system_)
{
	if (S_isCramer(system_))
	{
		std::cout << "The matrix is fit for Law of Cramer . Click to continue." << std::endl;
		system("pause");
		Matrix A = system_.getA(), B = system_.getB();
		Matrix extended = this->M_concatenate(A, B, 1);
		std::vector<Det>upper_dets;//去除这一列的行列式的数组
		std::pair<Matrix, Matrix>left_and_right;
		Matrix temp_exten = Matrix(extended);
		for (int i = 0; i < system_.getAColumn(); i++)
		{
			if (i == 0)
			{
				Matrix zero_rightpart = this->M_split(temp_exten, true, i).second;
				Det zero_right_det = this->M_takeDet(zero_rightpart);
				upper_dets.emplace_back(zero_right_det);
			}
			left_and_right.first = this->M_split(temp_exten, true, i - 1).first;
			left_and_right.second = this->M_split(temp_exten, true, i).second;
			Matrix newmat = this->M_concatenate(left_and_right.first, left_and_right.second, 1);
			Det newdet = this->M_takeDet(newmat);
			upper_dets.emplace_back(newdet);

		}
		return upper_dets;
	}
	else
	{
		return std::vector<Det>();
	}
}
//得到克拉默法则的解，需要使用上面的两个函数（用户交互）
ContentVec LAC::S_getCramerSol(LinearSystem& system_)
{
	std::vector<Det>upperdets = this->S_generateRLD(system_);
	if (upperdets == std::vector<Det>())
	{
		std::cout << "The system is NOT fit for Law_of_Cramer . Please give up using it for your solution." << std::endl;
		system("pause");
		return ContentVec();
	}

	ContentVec cramer_solutions(upperdets.size(), std::vector<double>(1, 0));//克拉默法则的解,竖着放
	Matrix A = system_.getA();
	Det detA = this->M_takeDet(A);
	double valueA = this->D_getValue(detA);
	double value_;
	for (int i = 0; i < upperdets.size(); i++)
	{
		value_ = this->D_getValue(upperdets.at(i));
		cramer_solutions.at(i).at(0) = 1.0 * value_ / valueA;
	}

	system("cls");
	std::cout << "Successfully got the solution!" << std::endl << "The solution of system" << std::endl;
	this->show(system_);
	std::cout << "is " << std::endl;
	this->S_showSol(make_pair(cramer_solutions, ContentVec()));
	system("pause");
	return cramer_solutions;
}


