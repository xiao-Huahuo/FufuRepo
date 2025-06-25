#include"LinearAlgebraCalculator.h"
#include<vector>
#include<algorithm>
#include<tuple>
#include<cmath>
#include<fstream>
#include<sstream>
using namespace std;

////1.����2.����ʽ��3.���Է�����
//std::vector<std::shared_ptr<Matrix>>matrixVector_;//��ž��������ָ������
//std::vector<std::shared_ptr<Det>>detVector_;//�������ʽ������ָ������
//std::vector<std::shared_ptr<LinearSystem>>systemVector_;//������Է����������
//std::vector<std::shared_ptr<Basis>>basisVector_;//��Ż�������
//std::string name_;
//std::string password_;
//int persontype_;

//�����������ϵ�����
void LAC::__Soviet__()
{
	std::cout << "�������������������������~�|����������" << std::endl;
	std::cout << "��������������������������������������" << std::endl;
	std::cout << "��   ����������������������������������" << std::endl;
	std::cout << " ��   ������������������������   ��������" << std::endl;
	std::cout << " ��   ������������������������   ��������" << std::endl;
	std::cout << "�������������������������������������� " << std::endl;
	std::cout << "������������  ������������������������" << std::endl;
	std::cout << " �������������������������������������� " << std::endl;
	std::cout << "���������������~�~�~�~�~�~������������" << std::endl;
	std::cout << "��������������������������������������" << std::endl;
	std::cout << "������������������������������  ������" << std::endl;
}

// ��������ļ�
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

		// ����д������������
		ofs << matrix.getRow() << " " << matrix.getColumn() << std::endl;

		// Ȼ��д����������Ԫ��
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
// ���ļ���ȡ����
void LAC::readMatrixFromFile()
{
	std::ifstream ifs(MATRIX_FILE);

	if (!ifs.is_open())
	{
		std::cerr << "Unable to open file for reading matrices." << std::endl;
		return;
	}

	matrixVector_.clear(); // ������еľ����б�

	// ѭ����ȡÿ������
	while (!ifs.eof())
	{ // ʹ��eof()����Ƿ񵽴��ļ�ĩβ
		int _row, _column;
		if (ifs >> _row >> _column)
		{ // ����ܹ���ȡ����������
			if (_row <= 0 || _column <= 0)continue;
			// ����һ���µľ���
			Matrix matrix(_row, _column);

			// ��ȡ�����ÿһ��
			for (int i = 0; i < _row; ++i)
			{
				for (int j = 0; j < _column; ++j)
				{
					ifs >> matrix[i][j];
				}
			}

			// ��������ӵ����о�����
			this->addItem(matrix, this->matVecSize());
		}
	}

	ifs.close();
}
// ��������ʽ���ļ�
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

		// ����д�������������
		ofs << det.getOrder() << " " << det.getPreNum() << std::endl;

		// Ȼ��д������ʽ������Ԫ��
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
// ���ļ���ȡ����ʽ
void LAC::readDetFromFile() {
	std::ifstream ifs(DET_FILE);

	if (!ifs.is_open()) {
		std::cerr << "Unable to open file for reading determinants." << std::endl;
		return;
	}

	detVector_.clear(); // ������е�����ʽ�б�

	// ѭ����ȡÿ������ʽ
	while (!ifs.eof())
	{ // ʹ��eof()����Ƿ񵽴��ļ�ĩβ
		int order;
		double prenum;
		if (ifs >> order >> prenum)
		{ // ����ܹ���ȡ����������
			if (order <= 0)continue;

			// ����һ���µ�����ʽ
			Det det(order, prenum);

			// ��ȡ����ʽ��ÿһ��
			for (int i = 0; i < order; ++i)
			{
				for (int j = 0; j < order; ++j)
				{
					ifs >> det[i][j];
				}
			}

			// ������ʽ��ӵ���������ʽ��
			this->addItem(det, this->detVecSize());
		}
	}

	ifs.close();
}
// �������Է����鵽�ļ�
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

		// ����д��A��������(A������+1)
		ofs << A.getRow() << " " << (A.getColumn() + 1) << std::endl;

		// Ȼ��д��A��B������Ԫ��
		for (int i = 0; i < A.getRow(); ++i)
		{
			for (int j = 0; j < A.getColumn(); ++j)
			{
				ofs << A[i][j] << " ";
			}
			// д��B�Ķ�ӦԪ��
			ofs << B[i][0] << std::endl;
		}
	}

	ofs.close();
}
// ���ļ���ȡ���Է�����
void LAC::readLinearSystemFromFile()
{
	std::ifstream ifs(LINEARSYSTEM_FILE);

	if (!ifs.is_open())
	{
		std::cerr << "Unable to open file for reading linear systems." << std::endl;
		return;
	}

	systemVector_.clear(); // ������е����Է������б�

	// ѭ����ȡÿ�����Է�����
	while (!ifs.eof())
	{ // ʹ��eof()����Ƿ񵽴��ļ�ĩβ
		int Arow, Acol;
		if (ifs >> Arow >> Acol)
		{ // ����ܹ���ȡ����������
			Acol--;
			if (Arow <= 0 || Acol <= 0)continue;
			//����A��B
			Matrix A(Arow, Acol), B(Arow, 1);

			// ��ȡ���Է������ÿһ��
			for (int i = 0; i < Arow; ++i)
			{
				for (int j = 0; j < Acol; ++j)
				{
					ifs >> A[i][j];
				}
				ifs >> B[i][0];
			}

			// ����һ���µ����Է�����
			LinearSystem linear(A, B);

			// �����Է�������ӵ��������Է�������
			this->addItem(linear, this->sysVecSize());
		}
	}

	ifs.close();
}
// ��������ļ�
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
		// ����д����������ͻ�������
		ofs << basis.at(0).size() << " " << basis.size() << std::endl;

		//�ϲ���
		Matrix temp_mat = this->M_mergeBasis(basis);
		ContentVec temp_blk = temp_mat.getValueVec();

		// Ȼ��д��temp_blk��Ԫ��
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
// ���ļ���ȡ��
void LAC::readBasisFromFile() {
	std::ifstream ifs(BASIS_FILE);

	if (!ifs.is_open()) {
		std::cerr << "Unable to open file for reading bases." << std::endl;
		return;
	}

	basisVector_.clear(); // ������еĻ��б�

	// ѭ����ȡÿ������
	while (!ifs.eof())
	{ // ʹ��eof()����Ƿ񵽴��ļ�ĩβ
		int _row, _column;
		if (ifs >> _row >> _column)
		{ // ����ܹ���ȡ����������
			if (_row <= 0 || _column <= 0)continue;
			// ����һ���µľ���
			Matrix matrix(_row, _column);

			// ��ȡ�����ÿһ��
			for (int i = 0; i < _row; ++i)
			{
				for (int j = 0; j < _column; ++j)
				{
					ifs >> matrix[i][j];
				}
			}

			Basis basis = this->M_takeBasis(matrix, true);

			if (basis == Basis())continue;

			// ������ӵ����л���
			this->addItem(basis, this->basisVecSize());
		}
	}

	ifs.close();
}
// �����������ʽ�����Է����顢�����ļ�
void LAC::saveFile() {
	this->saveMatrix();
	this->saveDet();
	this->saveLinearSystem();
	this->saveBasis();
}
// ���ļ��ж�ȡ��������ʽ�����Է����顢��
void LAC::readFile() {
	this->readMatrixFromFile();
	this->readDetFromFile();
	this->readLinearSystemFromFile();
	this->readBasisFromFile();
}



//���ؾ���������С
int LAC::matVecSize() const { return this->getMatVec().size(); }
//��������ʽ������С
int LAC::detVecSize()const { return this->getDetVec().size(); }
//�������Է�����������С
int LAC::sysVecSize()const { return this->getSysVec().size(); }
//���ػ�������С
int LAC::basisVecSize()const { return this->getBasisVec().size(); }

//��������չʾ
void LAC::showMatVec(int index)
{
	if (index < 0 || index >= this->matVecSize())return;
	this->show(*(this->getMatVec().at(index)));
}
//��������չʾ
void LAC::showDetVec(int index)
{
	if (index < 0 || index >= this->detVecSize())return;
	this->show(*(this->getDetVec().at(index)));
}
//��������չʾ
void LAC::showSysVec(int index)
{
	if (index < 0 || index >= this->sysVecSize())return;
	this->show(*(this->getSysVec().at(index)));
}
//��������չʾ
void LAC::showBasisVec(int index)
{
	if (index < 0 || index >= this->basisVecSize())return;
	this->show(*this->getBasisVec().at(index));
}

//���캯��������MessagePair�����ֺ�����Ķ��飩
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

	// ����һ�� ContentVec �� vector
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

	//��ȡ�ļ�
	this->readFile();

}
//��������
LAC::~LAC()
{
	//������뵽�ļ�
	this->saveFile();
}

//��ȡprivate�Ľӿ�

//��ȡ���������ָ������
const std::vector<std::shared_ptr<Matrix>>& LAC::getMatVec() const {
	return ref(matrixVector_);
}
//��ȡ����ʽ������ָ������
const std::vector<std::shared_ptr<Det>>& LAC::getDetVec() const {
	return ref(detVector_);
}
//��ȡ���Է����������ָ������
const std::vector<std::shared_ptr<LinearSystem>>& LAC::getSysVec() const {
	return ref(systemVector_);
}
//��ȡ��������ָ������
const std::vector <std::shared_ptr<Basis>>& LAC::getBasisVec()const {
	return ref(basisVector_);
}

//��̬�˵�
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

//��̬�Ӳ˵��û���������

//��ʾ��ǰ������������������
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
//��̬�Ӳ˵�--show
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
//�����û����봫��ContentVec�Ͳ�����������߲��룩
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
	if (_type != 3)//���Է�������Ҫ����A��B�������Ӳ˵�����������
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

	int insertplace = present_container_number;//Ĭ��������
	//������������һ��������ָ��λ�ã��û������û���������Ϊ����������������߲���
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
			//ָ��λ��
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
				insertplace--;//��Ϊ����
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
		//����������һ������ֱ�Ӵ���0
		return std::make_tuple(inputblock, 0);
	}

	if (!is_specified)
	{
		//���û��ָ��һ����������ҪתΪ����
		insertplace--;//��Ϊ����
	}

	return std::make_tuple(inputblock, insertplace);
}
//��̬�Ӳ˵�--add
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
		//����A
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
		//����B
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
//ɾ�������ķ�֧
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
	delindex--;//��Ϊ����

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
//��̬�Ӳ˵�--delete
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
//��̬�Ӳ˵�--clear
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
//ѡ�����ķ�֧
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
		//����
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
//��̬�Ӳ˵�--searchItem
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
//ѡ�����򷽷�
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
//��̬�Ӳ˵�--Sort
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
//��̬�Ӳ˵�--Shuffle
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
//�������Ӳ˵��е�ר�в���
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
		index--;//��Ϊ����

		while (true)
		{
			//չʾ��������˵�
			system("cls");
			Matrix temp_matrix = *(this->getMatVec().at(index));//�βΣ����޸�ʵ��
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
//����ʽ�����Ӳ˵��е�ר�в���
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
		index--;//��Ϊ����

		while (true)
		{
			//չʾ����ʽ�����˵�
			system("cls");
			Det temp_det = *(this->getDetVec().at(index));//�βΣ����޸�ʵ��
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
//���Է����鹦���Ӳ˵��е�ר�в���
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
		index--;//��Ϊ����

		while (true)
		{
			//չʾ���Է���������˵�
			system("cls");
			LinearSystem temp_system = *(this->getSysVec().at(index));//�βΣ����޸�ʵ��
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
//�������Ӳ˵��е�ר�в���
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
		index--;//��Ϊ����

		while (true)
		{
			//չʾ��������˵�
			system("cls");
			Basis temp_basis = *(this->getBasisVec().at(index));//�βΣ����޸�ʵ��
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


//չʾ

//չʾĳ��
void LAC::show(Matrix& matrix)
{
	for (auto& row : matrix.getValueVec())
	{
		std::cout << "\t[";
		for (auto& Number : row)
		{
			Number = std::round(Number * 100) / 100;//��ȷ��0.01
			std::cout << Number << " ";
		}
		std::cout << "]" << std::endl;
	}
}
//չʾĳ��
void LAC::show(Det& det)
{
	if (det.getPreNum() == 1)
	{
		for (auto& row : det.getValueVec())
		{
			std::cout << "\t|";
			for (auto& Number : row)
			{
				Number = std::round(Number * 100) / 100;//��ȷ��0.01
				std::cout << Number << " ";
			}
			std::cout << "|" << std::endl;
		}
	}
	else
	{
		int mid = (det.getOrder() % 2 == 0) ? (det.getOrder() / 2 - 1) : ((det.getOrder() - 1) / 2);//�м��е�����
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
				det[i][j] = std::round(det[i][j] * 100) / 100;//��ȷ��0.01
				std::cout << det[i][j] << " ";
			}
			std::cout << "|" << std::endl;
		}
	}
}
//չʾĳ��
void LAC::show(LinearSystem& system)
{
	Matrix A = system.getA(), B = system.getB();
	for (int i = 0; i < system.getARow(); i++)
	{
		std::cout << "\t{  ";
		for (int j = 0; j < system.getAColumn(); j++)
		{
			A[i][j] = std::round(A[i][j] * 100) / 100;//��ȷ��0.01
			std::cout << A[i][j] << " * X" << j + 1;
			if (j != system.getAColumn() - 1)
			{
				std::cout << " + ";
			}
		}
		B[i][0] = std::round(B[i][0] * 100) / 100;//��ȷ��0.01
		std::cout << " = " << B[i][0] << std::endl;
	}
}
//չʾĳ��
void LAC::show(Basis& basis)
{
	for (int i = 0; i < basis.at(0).size(); i++)
	{
		std::cout << "\t";
		for (int j = 0; j < basis.size(); j++)
		{
			basis[j][i][0] = std::round(basis[j][i][0] * 100) / 100;//��ȷ��0.01
			std::cout << "[" << basis[j][i][0] << "]  ";
		}
		std::cout << std::endl;
	}
}
//չʾ����
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


//���

//���һ�����󣬿�ѡ������λ����������壩
bool LAC::addItem(Matrix& matrix, int index)
{
	if (index == 0 && this->matVecSize() == 0)//����´���
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
//���һЩ����
bool LAC::addItem(std::vector<Matrix>& matrixvec, int index)
{
	std::vector<std::shared_ptr<Matrix>>ptrmatrixVec;
	std::for_each(matrixvec.begin(), matrixvec.end(), [&ptrmatrixVec](const Matrix& matrix) {
		ptrmatrixVec.emplace_back(std::make_shared<Matrix>(matrix));
		});
	if (index == 0 && this->matrixVector_.empty())//����´���
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
//���һ������ʽ����ѡ������λ������
bool LAC::addItem(Det& det, int index)
{
	if (index == 0 && this->detVector_.empty())//����´���
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
//���һЩ����ʽ
bool LAC::addItem(std::vector<Det>& detvec, int index)
{
	std::vector<std::shared_ptr<Det>>ptrdetVec;
	std::for_each(detvec.begin(), detvec.end(), [&ptrdetVec](const Det& det) {
		ptrdetVec.emplace_back(std::make_shared<Det>(det));
		});
	if (index == 0 && this->detVector_.empty())//����´���
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
//���һ�����Է����飬��ѡ������λ������
bool LAC::addItem(LinearSystem& system, int index)
{
	if (index == 0 && this->systemVector_.empty())//����´���
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
//���һЩ���Է�����
bool LAC::addItem(std::vector<LinearSystem>& systemvec, int index)
{
	std::vector<std::shared_ptr<LinearSystem>>ptrsystemVec;
	std::for_each(systemvec.begin(), systemvec.end(), [&ptrsystemVec](const LinearSystem& system) {
		ptrsystemVec.emplace_back(std::make_shared<LinearSystem>(system));
		});
	if (index == 0 && this->systemVector_.empty())//����´���
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
//���һ��������ѡ������λ����������壩
bool LAC::addItem(Basis& basis, int index)
{
	if (index == 0 && this->basisVecSize() == 0)//����´���
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
//���һЩ��
bool LAC::addItem(std::vector<Basis>& basisvec, int index)
{
	std::vector<std::shared_ptr<Basis>>p_basisvec;
	std::for_each(basisvec.begin(), basisvec.end(), [&p_basisvec](const Basis& basis) {
		p_basisvec.emplace_back(std::make_shared<Basis>(basis));
		});
	if (index == 0 && this->basisVector_.empty())//����´���
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


//ɾ��

//ɾ�����ڶ�����������������������������֮���ɾ��������Ĭ��Ϊ1��
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
//ɾ���������еĶ���
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
//��������Ŀն���
void LAC::removeEmpty() {
	//ʹ��erase-remove���÷�ɾ��
	//�Ƴ�����ָ��վ��������ָ��
	this->matrixVector_.erase(
		std::remove_if(matrixVector_.begin(), matrixVector_.end(), [&](std::shared_ptr<Matrix>& pmat) {
			return *pmat == Matrix();
			}),
		matrixVector_.end());
	//�Ƴ�����ָ�������ʽ������ָ��
	this->detVector_.erase(
		std::remove_if(detVector_.begin(), detVector_.end(), [&](std::shared_ptr<Det>& pdet) {
			return *pdet == Det();
			}),
		detVector_.end());
	//�Ƴ�����ָ��վ��������ָ��
	this->systemVector_.erase(
		std::remove_if(systemVector_.begin(), systemVector_.end(), [&](std::shared_ptr<LinearSystem>& psys) {
			return *psys == LinearSystem();
			}),
		systemVector_.end());
	//�Ƴ�����ָ��ջ�������ָ��
	this->basisVector_.erase(
		std::remove_if(basisVector_.begin(), basisVector_.end(), [&](std::shared_ptr<Basis>& pbas) {
			return *pbas == Basis();
			}),
		basisVector_.end());
}

//����(�Ի��Ĳ���Ҫ��д���Ĳ���Ϊtrue��
//���ң��ҵ��˷����������Ҳ�������-1��ע�����Է��������Ǹ���A��

//ǰ��������ݲ���
template<class T>
int contentSearch(const T& vec, const ContentVec& target)//��������ʽ�������
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& ptr) {
		return ptr->getValueVec() == target;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//�������ݲ���
template<class T>
int contentSearchBasis(const T& vec, const ContentVec& target, LAC* This)//����
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& basptr) {
		Matrix merged = This->M_mergeBasis(*basptr);
		return merged.getValueVec() == target;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//ǰ�������Ԫ����
template<class T>
int firstValSearch(const T& vec, double target)//��������ʽ�������
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& ptr) {
		return ptr->at(0, 0) == target;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//������Ԫ����
template<class T>
int firstValSearchBasis(const T& vec, double target)//����
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& basptr) {
		return (basptr->at(0))[0][0] == target;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//ǰ��������в���
template<class T>
int rowColumnSearch(const T& vec, int row_, int column_)//��������ʽ�������
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& ptr) {
		return ptr->getRow() == row_ & ptr->getColumn() == column_;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}
//�������в���
template<class T>
int rowColumnSearchBasis(const T& vec, int row_, int column_)//����
{
	auto it = std::find_if(vec.begin(), vec.end(), [&](auto& basptr) {
		return basptr->size() == column_ && basptr->at(0).size() == row_;
		});
	if (it != vec.end()) return std::distance(vec.begin(), it);
	else return -1;
}

//���ݲ���
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
//��Ԫ����
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
//���в���
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


//���������(�Ի�������Ҫ��д���Ĳ���Ϊtrue)
	//����ע�����Է����鰴��A
//��������ָ�������������

//ǰ�������Ԫ����
template<class T>
bool normalSort(T& container, bool sort_order)//��������ʽ�������
{
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		return sort_order ? p_pre->at(0, 0) < p_lat->at(0, 0) : p_pre->at(0, 0) > p_lat->at(0, 0);
		});
	return true;
}
//������Ԫ����
template<class T>
bool normalSortBasis(T& container, bool sort_order)//����
{
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		return sort_order ? (p_pre->at(0))[0][0] < (p_lat->at(0))[0][0] : (p_pre->at(0))[0][0] > (p_lat->at(0))[0][0];
		});
	return true;
}
//ǰ����Ĵ�С����
template<class T>
bool sizeSort(T& container, bool sort_order)//��������ʽ�������
{
	//��������
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		return sort_order ? p_pre->getRow() < p_lat->getRow() : p_pre->getRow() > p_lat->getRow();
		});
	std::sort(container.begin(), container.end(), [&](auto& p_pre, auto& p_lat) {
		return sort_order ? p_pre->getColumn() < p_lat->getColumn() : p_pre->getColumn() > p_lat->getColumn();
		});
	return true;
}
//���Ĵ�С����
template<class T>
bool sizeSortBasis(T& container, bool sort_order, LAC* This)//����
{
	//��������
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
//��Ԫ��������ʽ��true������false������
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
//��С������Ҫ�о�һ���㷨
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
//ϴ��
bool LAC::shuffleItem(int _type)
{
	// ��ȡ��ǰʱ����Ϊ�����������������
	time_t seed = std::time(0);
	// ����һ�������������
	std::default_random_engine engine(seed);
	// ��������
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


//��������

//���������Ȳ���ʱ���������루ǰ���ࣩ
void LAC::castVal(ContentVec& blk)
{
	//�������룬������0
	int Inter;
	for (auto& row : blk)for (auto& val : row) { val = std::round(val * 100) / 100; }

}
//���������Ȳ���ʱ���������루����
void LAC::castVal(Basis& basis)
{
	//�������룬������0
	int Inter;
	for (auto& blk : basis)for (auto& row : blk)for (auto& val : row) { val = std::round(val * 100) / 100; }

}



//�û���������

//����˵�
void LAC::matrixMainMenu()
{
	std::cout << "Choose your operation:" << std::endl;
	std::cout << "1.Take Det or Linear System" << std::endl;
	std::cout << "2.Power N" << std::endl;
	std::cout << "3.Multiply a number" << std::endl;
	std::cout << "4.transportortation" << std::endl;
	std::cout << "5.Obtain the minor (��ȡ����ʽ)" << std::endl;
	std::cout << "6.Obtain the adjugate matrix (��ȡ�������)" << std::endl;
	std::cout << "7.Concatenate matrix" << std::endl;
	std::cout << "8.Split matrix" << std::endl;
	std::cout << "9.Elementary row transformation (�����б任)" << std::endl;
	std::cout << "10.Finding the inverse matrix by ERT (�����б任�������)" << std::endl;
	std::cout << "11.Obtain rank of matrix by ERT (�����б任����)" << std::endl;
	std::cout << "12.Multiply a matrix" << std::endl;
	std::cout << "13.Get the inverse matrix directly" << std::endl;
	std::cout << "14.Split matrix into basis(�Ѿ����ɻ�)" << std::endl;
	std::cout << "15.Gain the trace (��ȡ����ļ�)" << std::endl;
	std::cout << "16.Versify the eigen value (�ж��Ƿ�Ϊ����ֵ)" << std::endl;
	std::cout << "17.Find eigen vectors with provided eigen values (�����ṩ������ֵѰ�����е���������)" << std::endl;
	std::cout << "18.Normal diaglization (��ͨ�Խǻ�)" << std::endl;
	std::cout << "19.Orthogonal diaglization (�����Խǻ�)" << std::endl;
	std::cout << "20.Contract diaglization (��ͬ�Խǻ��������ͱ�׼���еĳ��ȱ任��)" << std::endl;
	std::cout << "21.Gain A^n through diaglization (�Խǻ�������ȡA^n)" << std::endl;
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
	//����ʵ��
	this->M_numMult(*(this->getMatVec().at(index)), mul_num);
	std::cout << "Result is below:" << std::endl;
	this->showMatVec(index);
}
//4.transportortation
void LAC::matrixOperation_4(Matrix& temp_matrix, int index)
{
	//����ʵ��
	this->M_transport(*(this->getMatVec().at(index)));
	std::cout << "Result is below:" << std::endl;
	this->showMatVec(index);
}
//5.Obtain the minor (��ȡ����ʽ)
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
//6.Obtain the adjugate matrix (��ȡ�������)
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

	matrix_index--;//��Ϊ����
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

	this->addItem(concatenated, Sz);//����ƴ�Ӻ�ľ���

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
	row_or_column--;//��Ϊ����
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

	//�����ֺ�ľ���
	this->addItem(result_pair.first, Sz);
	this->addItem(result_pair.second, Sz);

}
//9.Elementary row transformation (�����б任)
void LAC::matrixOperation_9(Matrix& temp_matrix, int index)
{
	bool ret = this->M_elementaryRowTransformation(temp_matrix);
	if (!ret)
	{
		std::cerr << "Elementary row transformation failed." << std::endl;
	}
}
//10.Finding the inverse matrix by ERT (�����б任�������)
void LAC::matrixOperation_10(Matrix& temp_matrix, int index)
{
	Matrix inverse_matrix = this->M_getInverseByTransformation(temp_matrix);
	if (inverse_matrix == Matrix())
	{
		std::cerr << "Finding the inverse matrix using ERT failed." << std::endl;
	}
	//���������ӵ�����
	this->addItem(inverse_matrix, this->matVecSize());
}
//11.Obtain _rank of matrix by ERT (�����б任����)
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
	choice_index--;//��Ϊ����
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
//14.Split matrix into basis(�Ѿ����ɻ�)
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
//15.Gain the trace (��ȡ����ļ�)
void LAC::matrixOperation_15(Matrix& temp_matrix, int index)
{
	double _trace = this->M_getTrace(temp_matrix);
	std::cout << "The trace of the matrix is : " << _trace << std::endl;
}
//16.Versify the eigen value (�ж��Ƿ�Ϊ����ֵ)
void LAC::matrixOperation_16(Matrix& temp_matrix, int index)
{
	std::cout << "Input �� : ";
	double ��;
	std::cin >> ��;
	std::cout << (this->M_isEigenValue(temp_matrix, ��) ? "True !" : "False !") << std::endl;
}
//17.Find eigen vectors with provided eigen values (�����ṩ������ֵѰ�����е���������)
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
//18.Normal diaglization (��ͨ�Խǻ�)
void LAC::matrixOperation_18(Matrix& temp_matrix, int index)
{
	std::pair<Matrix, Matrix>result_pair = this->M_normalDiaglization(temp_matrix);
	if (result_pair == std::pair<Matrix, Matrix>())return;
	this->addItem(result_pair.first, this->matVecSize());
	this->addItem(result_pair.second, this->matVecSize());
}
//19.Orthogonal diaglization (�����Խǻ�)
void LAC::matrixOperation_19(Matrix& temp_matrix, int index)
{
	std::pair<Matrix, Matrix>result_pair = this->M_orthogonalDiaglization(temp_matrix);
	if (result_pair == std::pair<Matrix, Matrix>())return;
	this->addItem(result_pair.first, this->matVecSize());
	this->addItem(result_pair.second, this->matVecSize());
}
//20.Contract diaglization (��ͬ�Խǻ��������ͱ�׼���еĳ��ȱ任��)
void LAC::matrixOperation_20(Matrix& temp_matrix, int index)
{
	std::pair<Matrix, Matrix>result_pair = this->M_contractDiaglization(temp_matrix);
	if (result_pair == std::pair<Matrix, Matrix>())return;
	this->addItem(result_pair.first, this->matVecSize());
	this->addItem(result_pair.second, this->matVecSize());
}
//21.Gain A^n through diaglization (�Խǻ�������ȡA^n)
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


//����ʽ�˵�
void LAC::detMainMenu()
{
	std::cout << "Choose your operation:" << std::endl;
	std::cout << "1.Take Matrix" << std::endl;
	std::cout << "2.Multiply a number on row or column" << std::endl;
	std::cout << "3.transportortation" << std::endl;
	std::cout << "4.Elementary transformation (���ȱ任)" << std::endl;
	std::cout << "5.Finding value of the det by ERT (���ȱ任��ֵ)" << std::endl;
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
	mul_index--;//��Ϊ����
	double mul_num;
	std::cout << "Input the number:" << std::endl;
	std::cin >> mul_num;
	//����ʵ��
	this->D_numMult(*(this->getDetVec().at(index)), (row_or_col == 1) ? true : false, mul_index, mul_num);
	std::cout << "Result is below:" << std::endl;
	this->showDetVec(index);
}
//3.transportortation
void LAC::detOperation_3(Det& temp_det, int index)
{
	//����ʵ��
	this->D_transport(*(this->getDetVec().at(index)));
	std::cout << "Result is below:" << std::endl;
	this->showDetVec(index);
}
//4.Elementary transformation (���ȱ任)
void LAC::detOperation_4(Det& temp_det, int index)
{
	bool ret = this->D_elementaryTransformation(temp_det);
	if (!ret)
	{
		std::cerr << "Elementary transformation failed." << std::endl;
	}
}
//5.Finding value of the det by ERT (���ȱ任��ֵ)
void LAC::detOperation_5(Det& temp_det, int index)
{
	double res = this->D_getValue_Eletrans(temp_det);
	std::cout << "Successfully solved!\nThe value of the det is " << res << std::endl;
}


//���Է�����˵�
void LAC::systemMainMenu()
{
	std::cout << "Choose your operation:" << std::endl;
	std::cout << "1.Get A or B" << std::endl;
	std::cout << "2.Solve System by elementary transformation" << std::endl;
	std::cout << "3.Solve System (only unhomo) by Law of Cramer(����Ĭ����,���������)" << std::endl;
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
	//��A��B�Ž���������
	if (choice != 2)this->addItem(temp_A, this->matVecSize());
	if (choice != 1)this->addItem(temp_B, this->matVecSize());
	std::cout << "Successfully got ! Matrixes are below:" << std::endl;
	if (choice != 2)this->show(temp_A);
	if (choice != 1)this->show(temp_B);
}
//2.Solve System by elementary transformation
void LAC::systemOperation_2(LinearSystem& temp_system, int index)
{
	//�ж�����λ��Ƿ����
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

	std::pair<ContentVec, ContentVec>solutions;//ͨ����ؽ�
	if (isHomo)
	{
		//���
		solutions.first = this->S_solveHomo(temp_system);
		if (solutions.first == ContentVec())
		{
			std::cerr << "Homo linear system failed!" << std::endl;
			return;
		}
	}
	else
	{
		//�����
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
//3.Solve System (only unhomo) by Law of Cramer(����Ĭ����,���������)
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


//���˵�
void LAC::basisMainMenu()
{
	std::cout << "Choose your operation:" << std::endl;
	std::cout << "1.Merge into Matrix" << std::endl;
	std::cout << "2.Gain transition matrix from this to another basis (��ȡ���ɾ���)" << std::endl;
	std::cout << "3.Jugde orthogonal(�ж��Ƿ�����)" << std::endl;
	std::cout << "4.Gain the coordinate with this basis (��������������µ�����)" << std::endl;
	std::cout << "5.Gain metric matrix(��ȡ��������)" << std::endl;
	std::cout << "6.Model a vector(��������ģ)" << std::endl;
	std::cout << "7.Schmidt Orthogonalization(ʩ����������)" << std::endl;
	std::cout << "8.Normalization(��λ��)" << std::endl;
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
//2.Gain transition matrix from this to another basis (��ȡ���ɾ���)
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
	choice--;//��Ϊ����
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
//3.Jugde orthogonal(�ж��Ƿ�����)
void LAC::basisOperation_3(Basis& temp_basis, int index)
{
	bool ret = this->M_isOrthogonal(temp_basis);
	std::cout << (ret ? "True !" : "False !") << std::endl;
}
//4.Gain the coordinate with this basis (��������������µ�����)
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
//5.Gain metric matrix(��ȡ��������)
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
//6.Model a vector(��������ģ)
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
//7.Schmidt Orthogonalization(ʩ����������)
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
//8.Normalization(��λ��)
void LAC::basisOperation_8(Basis& temp_basis, int index)
{
	M_normallize(temp_basis);
	std::cout << "Basis after normalization is :" << std::endl;
	this->show(temp_basis);
	this->addItem(temp_basis, this->basisVecSize());
}



//����ר��

//�������㹤��

//ȡ����ʽ
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
//ȡ���Է����飨��ΪA��
LinearSystem LAC::M_takeLinearSystem(Matrix& matrix)
{
	return LinearSystem(matrix, Matrix(matrix.getRow(), 1));
}
//��������N�η�
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
//����ĳ�����֣���2���ǳ˵�����.
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
//����ת��
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
	//��ֵת��
	for (int i = 0; i < matrix.getRow(); i++)
	{
		for (int j = 0; j < matrix.getColumn(); j++)
		{
			tempblock[j][i] = matrix[i][j];
		}
	}
	matrix.setMatrix(newrow_, newcolumn_, tempblock);

}
//��ȡ����ʽ
Matrix LAC::M_getMinor(int index1, int index2, Matrix matrix)
{
	int row_ = matrix.getRow();
	int column_ = matrix.getColumn();
	if (index1 < 0 || index1 >= row_ || index2 < 0 || index2 >= column_)
	{
		throw out_of_range("minor matrix out of range !");
	}
	ContentVec tempblock(row_ - 1, std::vector<double>(column_ - 1, 0));
	//���Ͻ�
	for (int i = 0; i < index1; i++)
	{
		for (int j = 0; j < index2; j++)
		{
			tempblock[i][j] = matrix[i][j];
		}
	}
	//���½�
	for (int i = index1; i < row_ - 1; i++)
	{
		for (int j = 0; j < index2; j++)
		{
			tempblock[i][j] = matrix[i + 1][j];
		}
	}
	//���Ͻ�
	for (int i = 0; i < index1; i++)
	{
		for (int j = index2; j < column_ - 1; j++)
		{
			tempblock[i][j] = matrix[i][j + 1];
		}
	}
	//���½�
	for (int i = index1; i < row_ - 1; i++)
	{
		for (int j = index2; j < column_ - 1; j++)
		{
			tempblock[i][j] = matrix[i + 1][j + 1];
		}
	}
	return Matrix(row_ - 1, column_ - 1, tempblock);
}
//��ȡ�������
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
			//���д�������ʽ����
			if ((i + j) % 2 != 0)
			{
				adjmat[i][j] *= (-1);
			}
		}
	}
	//ת��
	this->M_transport(adjmat);
	return adjmat;

}
//ֱ�ӻ�ȡ�����
Matrix LAC::M_getInverse(Matrix& matrix)
{
	Det temp_det = this->M_takeDet(matrix);
	double det_val = this->D_getValue(temp_det);
	Matrix adjugate_matrix = this->M_getAdjugate(matrix);
	if (!matrix.isSquare() || det_val == 0 || adjugate_matrix == Matrix())return Matrix();
	this->M_numMult(adjugate_matrix, 1.0 / det_val);
	return adjugate_matrix;
}

//�����б任�й�
//ע�����ȱ任�������ǶԱ�����б任���������ı䱾����Ҫ����һ�� 

//һ�γ����б任���任�ɹ����true:row1+=row2*k
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
//һ�γ����б任���任�ɹ����true:column1+=column2*k
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
//�жϳ����б任֮��ľ������������͵ľ���1.�н����ξ���2.������;���3.��׼�;������������Ƿ���0
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
		std::map<int, int> zero_of_every_row;//�������׷���Ԫ������

		//����Ƿ�Ϊ�н����ξ���
		for (int i = 0; i < row_; i++)
		{
			int first_non_zero = column_; //��ʼ��Ϊ�е����ֵ
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
		//������
		for (int i = 0; i < row_ - 1; i++)
		{
			if (zero_of_every_row[i] > zero_of_every_row[i + 1])return 0;
		}
		if (!zero_of_every_row.empty()) matrix_type = 1; //����ͨ��
		else return 0;

		//��ʼ����Ƿ�Ϊ������ξ���
		for (int i = 0; i < row_; i++)
		{
			if (zero_of_every_row[i] == column_)continue;
			if (matrix[i][zero_of_every_row[i]] != 1)
			{
				return 1;
			}
		}
		//�����Ԫ��������Ԫ���Ƿ�Ϊ0
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

		matrix_type = 2; //����ͨ��

		//��ʼ����Ƿ�Ϊ��׼�;���
		int smaller_order = (row_ <= column_) ? row_ : column_;
		int end_one_index = smaller_order;//ĩ�˵�1������
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
		matrix_type = 3; //����ͨ��

		return matrix_type;
	}
	catch (out_of_range& err)
	{
		std::cerr << err.what() << " when judging type of matrix.  :(" << std::endl;
		return 0;
	}
}
//��γ����б任�������û�������
bool LAC::M_elementaryRowTransformation(Matrix& matrix)
{

	int trans_round = 1;
	std::vector<Matrix>history;//��ʷ��¼
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
				history.push_back(Matrix(matrix));//����һ�ݸ�history
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
					i--, j--;//��Ϊ����
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
				history.push_back(Matrix(matrix));//����һ�ݸ�history
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
				rowindex--;//��Ϊ����
				std::cout << "Input the number to multiply:" << std::endl;
				std::cin >> mul_num;
				for (int i = 0; i < matrix.getColumn(); i++)
				{
					matrix[rowindex][i] *= mul_num;
				}
			}
			else if (choice == 3)//Row exchange
			{
				history.push_back(Matrix(matrix));//����һ�ݸ�history
				int row1, row2;
				std::cout << "Input two row index for exchange:" << std::endl;
				std::cin >> row1 >> row2;
				if (row1 <= 0 || row1 > matrix.getRow() || row2 <= 0 || row2 > matrix.getRow() || row1 == row2)
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				row1--, row2--;//��Ϊ����
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

			trans_round++;//�ִ�+1
			//���������Ȳ�������Ҫ�ڴﵽ��ֵʱ��
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
//�����б任������󣬱任�ɹ�֮�󷵻������(���������ı�ԭ�����󣩣��û�������
Matrix LAC::M_getInverseByTransformation(Matrix& matrix)
{
	int row_ = matrix.getRow(), column_ = matrix.getColumn();
	if (!matrix.isSquare())return Matrix();

	//���ж���û�������,������ʽ�Ƿ�Ϊ0
	Det judge_det = this->M_takeDet(matrix);
	double judge_val = this->D_getValue(judge_det);
	if (judge_val == 0)
	{
		std::cerr << "The matrix does NOT have an inverse matrix !" << std::endl;
		system("pause");
		return Matrix();
	}

	Matrix temp_matrix = Matrix(matrix);//����һ�ݽ������

	system("cls");
	std::cout << "INVERSE  MATRIX  BY  ELEMENTARY  ROW  TRANSFORMATION" << std::endl;
	std::cout << "Present matrix is below:" << std::endl;
	this->show(matrix);
	std::cout << "Click any key to continue." << std::endl;
	system("pause");
	//ƴ�Ӿ����һ����λ����ˢ��ҳ�濪ʼ���ȱ任
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
		//�������ǲ��ǵ�λ����
		Matrix copy_montaged(montaged);
		std::pair<Matrix, Matrix>result_pair = this->M_split(copy_montaged, true, montaged.getRow() - 1);
		temp_elematrix = result_pair.second;
		if (!this->M_isEleMat(result_pair.first))
		{
			//û�б任��ɣ�ѡ������任���˳�
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

	//�任�ɹ�����־���
	system("cls");
	std::cout << "Inverse Matrix is below:" << std::endl;
	this->show(temp_elematrix);
	return temp_elematrix;
}

//����ƴ������

//����ƴ�ӣ�ǰ����������ƴ�ӵ��������󣬵�������ƴ�ӷ�ʽ��1.A + B; 2.B + A; 3.A����B���棻4.A����B����
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
//�����֣��ڶ������������ͣ�true�����Ų�false�����Ų� 
// �����������ǲ�ֵ��л��е�������������������������һ�У����У������棨���ұߣ���
std::pair<Matrix, Matrix> LAC::M_split(Matrix& matrix, bool _type, int split_index)
{
	int row_ = matrix.getRow(), column_ = matrix.getColumn();
	Matrix mat1, mat2;
	if (_type)//���Ų�	
	{
		if (split_index < 0 || split_index >= column_)
		{
			return std::pair<Matrix, Matrix>();
		}
		else if (split_index == column_ - 1)//����ڱ��ϲ�
		{
			mat1 = matrix;
			mat2 = Matrix(row_, 0);
		}
		else//�������
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
	else//���Ų�
	{
		if (split_index < 0 || split_index >= row_)
		{
			return std::pair<Matrix, Matrix>();
		}
		else if (split_index == row_ - 1)//����ڱ��ϲ�
		{
			mat1 = matrix;
			mat2 = Matrix(0, column_);
		}
		else//�������
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

//��λ�����й�

//����һ��order�׵ĵ�λ����
Matrix LAC::M_generateEleMat(int order)
{
	Matrix temp(order, order);
	for (int i = 0; i < order; i++)
	{
		temp[i][i] = 1;
	}
	return temp;
}
//�ж��ǲ��ǵ�λ����
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


//���й�

//�Ծ�����г����б任����(�ı�ԭ�����󣩣��û�������
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
		//����ǲ����н�����
		int type_judge = this->M_typeJudge(matrix);
		if (type_judge != 1 && type_judge != 2 && type_judge != 3)
		{
			std::cerr << "The matrix is NOT row echlon form (�н�����) !" << std::endl;
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

	//�任�ɹ�����������������ӵõ��������
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

//�������

//�������Ƿ�Ϊ�ϸ�Ļ�(��һ�£���Ϊ1)
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
//������������)�ϲ�Ϊ����
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
//�������ɻ�����Ϊ�в���в�(true�����������false�����������
Basis LAC::M_takeBasis(Matrix& matrix, bool _type)
{
	int row_ = matrix.getRow(), column_ = matrix.getColumn();
	if (row_ < 1 || column_ < 1)return Basis();
	Basis  basis_vec;
	if (_type)
	{
		//���������
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
		//���������
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
//��ȡ�ӻ�X����Y�Ĺ��ɾ���P,XP=Y
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
//�����(������)���ж��Ƿ�����
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
//���������ڻ��µ����꣬ʹ��y=B^-1 * a,����BΪbasisƴ�����ľ���a��vec
ContentVec LAC::M_getCoordinate(const ContentVec& vec_a, const Basis& basis_B)
{
	if (!M_isBasis(basis_B))return ContentVec();
	Matrix merged_B_inversed = M_mergeBasis(basis_B);
	if (merged_B_inversed == Matrix())return ContentVec();
	if (merged_B_inversed.getColumn() != vec_a.size())return ContentVec();
	if (merged_B_inversed.getRow() != merged_B_inversed.getColumn())return ContentVec();

	//���B�Ƿ����
	Det judge_det = this->M_takeDet(merged_B_inversed);
	if (D_getValue(judge_det) == 0)return ContentVec();
	else merged_B_inversed = this->M_getInverse(merged_B_inversed);
	Matrix vec_matrix_a(vec_a);
	return (merged_B_inversed * vec_matrix_a).getValueVec();

}
//�������������������
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
//��ȡ������ģ
double LAC::M_mod(ContentVec& vec)
{
	if (vec.empty())return 0;
	if (vec.size() != 1 && vec.at(0).size() != 1)return 0;
	double vec_model = 1;
	for (const auto& row : vec)for (const auto& val : row)vec_model += val * val;
	if (vec_model < 0)return 0;
	return std::sqrt(vec_model);
}
//�Ի�����ʩ��������������������������λ�����Ļ�
Basis LAC::M_SchmidtOrthogonalization(const Basis& basis)
{
	if (!M_isBasis(basis))return Basis();
	//ÿ����������������ʼ����ʩ����������
	Basis orthogonal;//�����������������������
	orthogonal.push_back(basis.at(0));
	for (int i = 1; i < basis.size(); i++)
	{
		ContentVec to_orthog = basis.at(i);
		//��ȥ���������
		for (int j = 0; j < i; j++)
		{
			double upper_num = basis.at(i) * orthogonal.at(j), lower_num = orthogonal.at(j) * orthogonal.at(j);
			double prefactor = 1.0 * upper_num / lower_num;//ÿ����ȥ������ǰ�������
			ContentVec to_minus = orthogonal.at(j);
			to_minus *= prefactor;
			to_orthog = to_orthog - to_minus;
		}
		orthogonal.push_back(to_orthog);
	}
	return orthogonal;
}
//�Ի���ʵ�ν��е�λ��
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

//��������������ֵ

//�ж��Ƿ�Գ�
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
//��ȡ����ļ�
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
//��֤�Ƿ�Ϊ����ֵ
bool LAC::M_isEigenValue(const Matrix& matrix, double ��)
{
	if (!matrix.isSquare() || matrix == Matrix())return false;
	//|��E-A|=0
	Matrix ��E = this->M_generateEleMat(matrix.getRow());
	for (int i = 0; i < matrix.getRow(); i++)
	{
		��E[i][i] *= ��;
	}
	��E -= matrix;
	Det temp_det = this->M_takeDet(��E);
	if (this->D_getValue(temp_det) == 0)return true;
	else return false;

}
//��ȡ����������������������ֵ���������������map(�û�����)
std::map<double, Basis> LAC::M_getEigenVector(Matrix& matrix)
{
	if (matrix == Matrix())return std::map<double, Basis>();
	if (matrix.getRow() != matrix.getColumn())return std::map<double, Basis>();
	if (!this->M_isSymmetric(matrix))return std::map<double, Basis>();

	std::map<double, Basis>eigen_pairs;//�������ֵ���������������map
	std::vector<double>recordings;//�˼�¼

	while (true)
	{
		system("cls");
		std::cout << "Present matrix is below:" << std::endl;
		this->show(matrix);
		if (!recordings.empty())
		{
			std::cout << "Present ��:";
			for (const double& _lambda : recordings)
			{
				std::cout << _lambda << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "Please calculate �� and input them (if 114514 inputed , you will exit):" << std::endl;
		double ��;
		//������������
		while (true)
		{
			std::cin >> ��;
			if (�� == 114514)return eigen_pairs;
			if (!this->M_isEigenValue(matrix, ��))
			{
				//�����������ֵ
				std::cerr << "The value is NOT �� of the matrix ! Please input again!" << std::endl;
				continue;
			}
			auto ret = std::find_if(recordings.begin(), recordings.end(), [&](const double& record_��) {return �� == record_��; });
			if (ret != recordings.end())
			{
				//����ظ�����Ҫ��������
				std::cerr << "The �� is the same with one of those you have found,please input �� again:" << std::endl;
				continue;
			}
			//�Ǧ�,�����������
			system("cls");
			recordings.push_back(��);
			Matrix ��E = this->M_generateEleMat(matrix.getRow());
			for (int i = 0; i < matrix.getRow(); i++)
			{
				��E[i][i] *= ��;
			}
			LinearSystem temp_system(��E - matrix, Matrix(matrix.getRow(), 1));
			ContentVec fundamental_solutions = this->S_solveHomo(temp_system);//����ʱ������
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
				//��Ҫ�ָ�Ϊ����С��������
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
			eigen_pairs.insert(make_pair(��, eigen_vec));//��ţ�������һ��Ѱ����������
			break;
		}
		system("pause");
	}


}
//��ͨ�Խǻ�,����P��diag���û�������
std::pair<Matrix, Matrix> LAC::M_normalDiaglization(Matrix& matrix)
{
	//��ȡ��������
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

	int diag_order = 0;//����diag���ܽ���
	for (auto& kv : eigen_map)
	{
		diag_order += kv.second.size();
	}

	Matrix mat_diag = this->M_generateEleMat(diag_order);//������diag

	//����������ƴ��P
	Basis eigen_vecs;//����������������Ķ��飨˳��ʹ�����diag��Ӧ��������ظ���Ҫ��˳���ŷţ�
	int place_index = 0;//�ŷ�����ֵ������
	for (auto& kv : eigen_map)
	{
		if (kv.second.size() == 1)
		{
			//��������ظ���ֱ�ӷ�
			eigen_vecs.push_back(kv.second.at(0));
			mat_diag[place_index][place_index] = kv.first;
			place_index++;
		}
		else if (kv.second.size() > 1)
		{
			//������ظ���Ҫ��˳���ŷ�
			for (int i = 0; i < kv.second.size(); i++)
			{
				eigen_vecs.push_back(kv.second.at(i));
				mat_diag[place_index][place_index] = kv.first;
				place_index++;
			}
		}
	}

	Matrix mat_P = M_mergeBasis(eigen_vecs);//������P

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
//�����Խǻ�������P��diag���û�������
std::pair<Matrix, Matrix> LAC::M_orthogonalDiaglization(Matrix& matrix)
{
	//��ȡ��������
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

	//����ÿ������ֵ����������ظ���λ����������ظ�����ʩ�����������ٵ�λ��
	for (auto& kv : eigen_map)
	{
		if (kv.second.size() > 1)
		{
			//�ظ���ʩ����������
			kv.second = this->M_SchmidtOrthogonalization(kv.second);
		}
		//��λ��
		this->M_normallize(kv.second);
	}

	int diag_order = 0;//����diag���ܽ���
	for (auto& kv : eigen_map)
	{
		diag_order += kv.second.size();
	}

	Matrix mat_diag = this->M_generateEleMat(diag_order);//������diag

	//����������ƴ��P
	Basis eigen_vecs;//����������������Ķ��飨˳��ʹ�����diag��Ӧ��������ظ���Ҫ��˳���ŷţ�
	int place_index = 0;//�ŷ�����ֵ������
	for (auto& kv : eigen_map)
	{
		if (kv.second.size() == 1)
		{
			//��������ظ���ֱ�ӷ�
			eigen_vecs.push_back(kv.second.at(0));
			mat_diag[place_index][place_index] = kv.first;
			place_index++;
		}
		else if (kv.second.size() > 1)
		{
			//������ظ���Ҫ��˳���ŷ�
			for (int i = 0; i < kv.second.size(); i++)
			{
				eigen_vecs.push_back(kv.second.at(i));
				mat_diag[place_index][place_index] = kv.first;
				place_index++;
			}
		}
	}

	Matrix mat_P = M_mergeBasis(eigen_vecs);//������P

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
//ͨ����ͨ�Խǻ���ȡA^n���û�������
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

//�������еĲ��ֹ���

//�ж��ǲ��ǶԽǾ���
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
//�������еĺ�ͬ�任����������һ��ΪC^T*A*C,�ڶ���ΪC���û�������
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
		Matrix concatenated = this->M_concatenate(matrix, temp_elemat, 3);//����ƴ��

		int trans_round = 1;
		std::vector<Matrix>history;//��ʷ��¼

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
				history.push_back(Matrix(concatenated));//����һ�ݸ�history
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
					i--, j--;//��Ϊ����
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
				history.push_back(Matrix(concatenated));//����һ�ݸ�history
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
				mul_index--;//��Ϊ����
				std::cout << "Input the number to multiply:" << std::endl;
				std::cin >> mul_num;

				for (int i = 0; i < concatenated.getColumn(); i++)
				{
					concatenated[mul_index][i] *= mul_num;//������
					concatenated[i][mul_index] *= mul_num;//������
				}
			}
			else if (choice == 3)//Row exchange and column exchange
			{
				history.push_back(Matrix(concatenated));//����һ�ݸ�history
				int index1, index2;
				std::cout << "Input two index for exchange:" << std::endl;
				std::cin >> index1 >> index2;
				if (index1 <= 0 || index1 > concatenated.getColumn() || index2 <= 0 || index2 > concatenated.getColumn() || index1 == index2)
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				index1--, index2--;//��Ϊ����
				std::swap(concatenated[index1], concatenated[index2]);//�н���
				//�н���
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
				std::pair<Matrix, Matrix>result_pair = this->M_split(concatenated, false, matrix.getColumn());//�����������
				if (!this->M_isDiag(result_pair.first))
				{
					std::cerr << "The upper matrix is NOT diag matrix . Continue transforming?\n1.Yes  0.Exit" << std::endl;
					int choice;
					std::cin >> choice;
					if (choice == 1)
					{
						//������ͬ�任
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
				//�任�ɹ�
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

			trans_round++;//�ִ�+1
			//���������Ȳ�������Ҫ�ڴﵽ��ֵʱ��
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


//����ʽר��

//�������㹤��

//ת��Ϊ����,ע��������premierNum!(��Ϊ�Ծ���Ӱ�죩
Matrix LAC::D_takeMat(const Det& det)
{
	return Matrix(det.getOrder(), det.getOrder(), det.getValueVec());
}
//��ĳһ�л�ĳһ������ĳ�����֣��ڶ����������л��У�true:�У�false:�У�  ��3��������Ҫ�������л��е���������������������
// ��4���ǳ˵�����.  ����ע�⽫prenum_����number����
void LAC::D_numMult(Det& det, bool _type, int index, double number)
{
	int order_ = det.getOrder();
	if (index < 0 || index >= order_)return;
	if (_type)//�г˷�
	{
		for (int j = 0; j < order_; j++)
		{
			det[index][j] *= number;
		}
	}
	else//�г˷�
	{
		for (int i = 0; i < order_; i++)
		{
			det[i][index] += number;
		}
	}
	det.setDet(order_, det.getValueVec(), det.getPreNum() / number);
}
//����ʽת�ã�ע������һ��-1
void LAC::D_transport(Det& det)
{
	int neworder_ = det.getOrder();
	ContentVec tempblock;
	tempblock.resize(neworder_);
	for (int i = 0; i < neworder_; i++)
	{
		tempblock[i].resize(neworder_);
	}
	//��ֵת��
	for (int i = 0; i < det.getRow(); i++)
	{
		for (int j = 0; j < det.getColumn(); j++)
		{
			tempblock[j][i] = det[i][j];
		}
	}
	det.setDet(neworder_, tempblock, det.getPreNum() * (-1));
}
//ֱ�ӻ�ȡ����ʽ��ֵ 
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
	default: // ����������ϵģ�ʹ��������˹չ�����ݹ飩
	{

		std::map<double, double>laplace_map;
		for (int i = 0; i < order_; i++)
		{
			for (int j = 0; j < order_; j++)
			{
				double centre_num = det[i][j];
				//��������һ����ת�ɾ���(���������ı����٣���ȡ����ʽ
				Matrix temp_matrix = this->M_getMinor(i, j, D_takeMat(Det(det)));
				//������ʽת��Ϊ����ʽ
				Det result_det = M_takeDet(temp_matrix);
				//������ʽȡֵ����������ֵ�Ž�laplace_map
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

//����ʽ���ȱ任

//һ������ʽ�����б任���任�ɹ����true:row1+=row2*k
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
//һ������ʽ�����б任���任�ɹ����true:column1+=column2*k
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
//�������ʽ���ȱ任�������û�������
bool LAC::D_elementaryTransformation(Det& det)
{
	int trans_round = 1;
	std::vector<Det>history;//��ʷ��¼
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
				history.push_back(Det(det));//����һ�ݸ�history
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
					i--, j--;//��Ϊ����
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
				history.push_back(Det(det));//����һ�ݸ�history
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
					i--, j--;//��Ϊ����
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
				history.push_back(Det(det));//����һ�ݸ�history
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
				rowindex--;//��Ϊ����
				std::cout << "Input the number to multiply:" << std::endl;
				std::cin >> mul_num;
				for (int i = 0; i < det.getOrder(); i++)
				{
					det[rowindex][i] *= mul_num;
				}
				det.setDet(det.getOrder(), det.getValueVec(), 1.0 * (det.getPreNum()) / mul_num);//����ʽǰ�����ָı�
			}
			else if (choice == 4)//Column number multiply
			{
				history.push_back(Det(det));//����һ�ݸ�history
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
				columnindex--;//��Ϊ����
				std::cout << "Input the number to multiply:" << std::endl;
				std::cin >> mul_num;
				for (int i = 0; i < det.getOrder(); i++)
				{
					det[i][columnindex] *= mul_num;
				}
				det.setDet(det.getOrder(), det.getValueVec(), 1.0 * (det.getPreNum()) / mul_num);//����ʽǰ�����ָı�
			}
			else if (choice == 5)//Row exchange
			{
				history.push_back(Det(det));//����һ�ݸ�history
				int row1, row2;
				std::cout << "Input two row index for exchange:" << std::endl;
				std::cin >> row1 >> row2;
				if (row1 <= 0 || row1 > det.getOrder() || row2 <= 0 || row2 > det.getOrder() || row1 == row2)
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				row1--, row2--;//��Ϊ����
				std::swap(det[row1], det[row2]);
				det.setDet(det.getOrder(), det.getValueVec(), (-1.0) * (det.getPreNum()));//����ʽǰ�����ָı�
			}
			else if (choice == 6)//Column exchange
			{
				history.push_back(Det(det));//����һ�ݸ�history
				int column1, column2;
				std::cout << "Input two column index for exchange:" << std::endl;
				std::cin >> column1 >> column2;
				if (column1 <= 0 || column1 > det.getOrder() || column2 <= 0 || column2 > det.getOrder() || column1 == column2)
				{
					std::cerr << REINPUT_PHRASE << std::endl;
					system("pause");
					continue;
				}
				column1--, column2--;//��Ϊ����
				std::swap(det[column1], det[column2]);
				det.setDet(det.getOrder(), det.getValueVec(), (-1.0) * (det.getPreNum()));//����ʽǰ�����ָı�
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

			trans_round++;//�ִ�+1
			//���������Ȳ�������Ҫ�ڴﵽ��ֵʱ��
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
//���ȱ任������ʽ��ֵ����ֵ�ɹ�֮�󷵻����ֵ ���û�������
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
	//�������ڵ���4����Ҫ���г��ȱ任
	std::cout << "Click to begin transforming." << std::endl;
	system("pause");
	system("cls");

	while (true)
	{
		//��ʼ�任��ֵ
		bool _sign = this->D_elementaryTransformation(det);
		if (!_sign)
		{
			std::cerr << "TRANSFORMATION FAILED!" << std::endl;
			system("pause");
			return 0;
		}

		//�任���֮��
		if (!this->D_isTriangDet(det))//����任֮������������ʽ
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


	//�任֮������������ʽ��������ֵ
	return this->D_getValue_Triang(det);


}

//��������ʽ�й�

//�ж��ǲ�����������ʽ
bool LAC::D_isTriangDet(Det& det)
{
	bool is_upper_triang = true;
	bool is_lower_triang = true;
	int _order = det.getOrder();

	// �ж��Ƿ�Ϊ����������ʽ
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

	// �ж��Ƿ�Ϊ����������ʽ
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

	// ����������ǻ�������֮һ���򷵻�true
	return is_upper_triang || is_lower_triang;
}
//��ȡ��������ʽ��ֵ,����������ĺ���
double LAC::D_getValue_Triang(Det& det)
{
	if (!this->D_isTriangDet(det))return 0;

	double type_judge = 1;
	for (int i = 0; i < det.getOrder(); i++)
	{
		type_judge *= det[i][i];
	}
	//���Ҫ����premierNum
	type_judge *= det.getPreNum();


	return type_judge;
}






//���Է�����ר��

//�������A���ȣ��û�������
int LAC::S_getRank(LinearSystem& system_)
{
	Matrix A = system_.getA();//�õ�A�Ŀ���
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
//�����Է�����--���ȱ任�� (����)���û�������
ContentVec LAC::S_solveHomo(const LinearSystem& system_)
{
	//����η����飨������ǻ�����ϵ����������ϵ �� �� �ţ���
	//���裺
	//1.�ȸ���A������ʽ�ж��Ƿ��з���⣻
	//2.��A���ȱ任��Ϊ�н����λ�������λ��׼�ͣ����жϣ�
	//3.������1���Ѿ��ų�r=row_��������ʲ����ܳ���Ψһ�⣻
	//4.���������δ֪��(r<row_)�������жϳ�X��������δ֪�����±꣬Ȼ����������б任Ϊ������Σ����ա��÷������õ�X�������ֵ��ɵ����飨������ϵ����
	//5.������������ϵ��
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
		int conti;//������õ���һ��������û�гɹ��任ʱ���±任
		while (true)
		{
			system("cls");
			if (system_.getA().isSquare() && this->D_getValue(adet) != 0)//���A�Ƿ��󲢿���������ʽ�ж�
			{
				std::cout << "The coefficient determinant of this system is NOT 0 ��" << std::endl
					<< "There is NO non-zero solution !" << std::endl;
				system("pause");
				return ContentVec();
			}
			else//���Ƿ��󣬻����Ƿ����ǲ���������ʽ����Ҫ�����б任�õ���
			{
				_rank_of_A = S_getRank(A);

				if (_rank_of_A == 0) return ContentVec();
				else if (_rank_of_A != 0 && _rank_of_A != system_.getARow()) {}
				else
				{
					std::cout << "The coefficient determinant of this system is NOT 0 ��" << std::endl
						<< "There is NO non-zero solution !" << std::endl;
					system("pause");
					return ContentVec();
				}
			}
			//��ʱ��Ȼ��0<r<row_
			std::vector<int> free_unknown;//�������δ֪����������������
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
					//��Ҫ�����任Ϊ�������
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
					if (conti == 1)break;//��û�гɹ��任ʱ���±任

					bool _sign = this->M_elementaryRowTransformation(A);
					if (!_sign)
					{
						std::cerr << "TRANSFORMATION FAILED!" << std::endl;
						system("pause");
						return ContentVec();
					}

					//�任֮���ж��ǲ����������
					continue;
				}
				else//�Ѿ����������,ʹ�÷����鷨�㷨
				{
					int num_of_fund = free_unknown.size();//������ϵ������

					ContentVec fundamental_solutions(system_.getAColumn(), std::vector<double>(num_of_fund, 0));//������ϵ�����ŷ�

					ContentVec zero_one_vec(num_of_fund, std::vector<double>(num_of_fund, 0));//0 1 �任�����飬���ŷ�
					for (int i = 0; i < num_of_fund; i++)zero_one_vec[i][i] = 1;

					//�Ƚ�zero_one_vec������ֵ��������ϵ
					for (int i = 0; i < num_of_fund; i++)
					{
						for (int j = 0; j < num_of_fund; j++)
						{
							fundamental_solutions[free_unknown[i]][j] = zero_one_vec[i][j];//����δ֪����������ɻ�����ϵ��������!
						}
					}
					//�����������A���ɵķ�����õ�ʣ���ֵ���Ž�������ϵ
					std::vector<int>rest_col_indexes;//�������Ԫ�ص�������
					std::vector<int>all_col_indexes;//�������������
					for (int i = 0; i < system_.getAColumn(); i++)
					{
						all_col_indexes.push_back(i);
					}
					//ȡrest_col_indexes��free_unknown��all_col_indexes�Ĳ
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

					//������ϵ��ֵ��ɣ�
					system("cls");
					std::cout << "Homo system has been successfullt solved!" << std::endl << "The general solution is below:" << std::endl;
					this->S_showSol(std::make_pair(fundamental_solutions, ContentVec()));
					system("pause");
					return fundamental_solutions;

				}
			}
			if (conti == 1)continue;//��û�гɹ��任ʱ���±任
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
//�����η����飨���firstΪ��Ӧ��η�����Ļ�����ϵ��secondΪ�����ͨ�⣩���û�������
std::pair<ContentVec, ContentVec> LAC::S_solveUnhomo(const LinearSystem& system_)
{
	//���裺
	//1.�Ƚ����������ȱ任Ϊ�н����Σ��ǵ��жϣ���Ȼ���ж�r(A) == r(A, b)��������Ⱦ�ֹ���ڴˣ�
	//2.�����ȣ��ͽ���Ӧ��η�����Ļ�����ϵ��
	//3.Ū����һ��������ؽ⣨�ֶ����۲취�������ж��Ƿ���ϣ������Ͼ������ң�
	//4.�ҵ��˾����������ϵ���ؽ�Ķ��顣
	if (system_.getARow() > system_.getAColumn())
	{
		std::cerr << "Equations are too much!" << std::endl;
		system("pause");
		return std::pair<ContentVec, ContentVec>();
	}
	Matrix A = system_.getA(), B = system_.getB();
	int _rank_of_A;
	Matrix extended = this->M_concatenate(A, B, 1);//�������
	int conti;//������õ���һ��������û�гɹ��任ʱ���±任

	while (true)
	{
		//�����������ȱ任Ϊ�н�����
		system("cls");
		bool _sign = this->M_elementaryRowTransformation(extended);
		if (!_sign)
		{
			std::cerr << "TRANSFORMATION FAILED!" << std::endl;
			system("pause");
			return std::pair<ContentVec, ContentVec>();
		}
		//�жϱ任֮���Ƿ�Ϊ�н�����
		int _type = this->M_typeJudge(extended);
		if (_type != 1 && _type != 2 && _type != 3)
		{
			//�����н����Σ���¯����
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
			if (conti == 1)continue;//��û�гɹ��任ʱ���±任
		}
		else
		{
			//���н����Σ��ж�r(A) == r(A, b)
			//�����һ�п�ʼ�ң�����Ƿ����оͽ��뵹����һ��
			bool is_zerocol = true;//�� A���� �ж��Ƿ�Ϊ0
			bool is_solveable = true;//r(A) == r(A, b)
			for (int i = system_.getARow() - 1; i != -1; i--)
			{
				for (int j = 0; j < system_.getAColumn(); j++)//�� A���� �ж��Ƿ�Ϊ0
				{
					if (extended[i][j] != 0)
					{
						is_zerocol = false;
						break;
					}
				}
				if (is_zerocol)//���A���ж���0���ж�B����
				{
					if (extended[i][system_.getAColumn()] != 0)
					{
						is_solveable = false;
						break;
					}
				}
			}

			//���r(A) ��= r(A, b)��ֱ����ֹ
			if (!is_solveable)
			{
				std::cout << "r(A) is NOT equal to r(A, b) ! The system has NO solutions.Click to exit." << std::endl;
				system("pause");
				return std::pair<ContentVec, ContentVec>();
			}

			//r(A) = r(A, b)������Ӧ��η�����Ļ�����ϵ
			std::pair<Matrix, Matrix>temp_pair = this->M_split(extended, true, system_.getAColumn() - 1);
			LinearSystem temp_system(temp_pair.first, temp_pair.second);
			ContentVec fundamental_solutions = this->S_solveHomo(temp_system);
			if (fundamental_solutions == ContentVec())//���û�н����
			{
				system("cls");
				std::cerr << "You did NOT solve the homosystem." << std::endl;
				system("pause");
				return std::pair<ContentVec, ContentVec>();
			}
			//�ֶ����۲취�õ�һ���ؽ�
			system("cls");
			std::cout << "Present system is below:" << std::endl;
			this->show(temp_system);
			std::cout << "Please observe the linear system and get a particular solution:" << std::endl;
			Matrix particular_solution(system_.getAColumn(), 1);//�ؽ�
			double cinnum;
			while (true)
			{
				for (int i = 0; i < system_.getAColumn(); i++)
				{
					std::cin >> cinnum;
					particular_solution[i][0] = cinnum;
				}
				//��֤�Ƿ�Ϊ�����ؽ�,����֤ԭʼ��A*particular_solution==B
				if (system_.getA() * particular_solution == system_.getB())
				{
					std::cout << "Successfully input ! Click to show the General Solution of the system." << std::endl;
					system("pause");
					break;
				}
				else
				{
					//�����������ؽ⣬��������
					std::cout << "This is NOT one of the particular solutions of the system . Please input again!" << std::endl;
					continue;
				}
			}

			return std::make_pair(fundamental_solutions, particular_solution.getValueVec());

		}
	}

}
//����������ӵ���ʽչʾ��λ����η������ͨ�⣨��⣬���޽⣩����Ҫ�Զ��ж�,���������ͨ���ұ��ؽ⣨���ŵģ�
void LAC::S_showSol(const std::pair<ContentVec, ContentVec>& solutions_pair)
{
	ContentVec general = solutions_pair.first, particular = solutions_pair.second;
	int mid = (general.size() % 2 == 0) ? (general.size() / 2 - 1) : ((general.size() - 1) / 2);//�м��е�����
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

//�����Է�����--����Ĭ���� (����)

//�ж��Ƿ��ʺϿ���Ĭ�������������һ��N*��N+1���ģ�
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
//���ж��ʺϿ���Ĭ���������ȥ����һ�е�����ʽ�����飬��˳�����ֱ���D1,D2,...,Dn,D����Ҫ������������ж�
std::vector<Det> LAC::S_generateRLD(const LinearSystem& system_)
{
	if (S_isCramer(system_))
	{
		std::cout << "The matrix is fit for Law of Cramer . Click to continue." << std::endl;
		system("pause");
		Matrix A = system_.getA(), B = system_.getB();
		Matrix extended = this->M_concatenate(A, B, 1);
		std::vector<Det>upper_dets;//ȥ����һ�е�����ʽ������
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
//�õ�����Ĭ����Ľ⣬��Ҫʹ������������������û�������
ContentVec LAC::S_getCramerSol(LinearSystem& system_)
{
	std::vector<Det>upperdets = this->S_generateRLD(system_);
	if (upperdets == std::vector<Det>())
	{
		std::cout << "The system is NOT fit for Law_of_Cramer . Please give up using it for your solution." << std::endl;
		system("pause");
		return ContentVec();
	}

	ContentVec cramer_solutions(upperdets.size(), std::vector<double>(1, 0));//����Ĭ����Ľ�,���ŷ�
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


