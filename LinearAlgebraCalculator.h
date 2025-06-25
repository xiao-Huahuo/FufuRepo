#pragma once
#include"AbstractCalculator.h"
#include"LinearSystem.h"
#include<random>
#include<ctime>

class LAC :public AbstractCalculator
{
private:
	//ע�⣺_type��ֵ����
	//1.����2.����ʽ��3.���Է�����
	std::vector<std::shared_ptr<Matrix>>matrixVector_;//��ž��������ָ������
	std::vector<std::shared_ptr<Det>>detVector_;//�������ʽ������ָ������
	std::vector<std::shared_ptr<LinearSystem>>systemVector_;//������Է����������
	std::vector<std::shared_ptr<Basis>>basisVector_;//��Ż�������
	std::string name_;
	std::string password_;
	int persontype_;
public:
	//�����������ϵ�����
	void __Soviet__();

	//����Ͷ�ȡ�������ݽṹ���ļ����Ӻ���
	void saveMatrix();
	void readMatrixFromFile();
	void saveDet();
	void readDetFromFile();
	void saveLinearSystem();
	void readLinearSystemFromFile();
	void saveBasis();
	void readBasisFromFile();

	// �����������ʽ�����Է����顢�����ļ�
	void saveFile();
	// ���ļ��ж�ȡ��������ʽ�����Է����顢��
	void readFile();

	//���캯��������MessagePair�����ֺ�����Ķ��飩
	LAC(const MessagePair& inputPair, int _type);
	~LAC();

	//��ȡprivate�Ľӿ�
	const std::vector<std::shared_ptr<Matrix>>& getMatVec() const;
	const std::vector<std::shared_ptr<Det>>& getDetVec() const;
	const std::vector<std::shared_ptr<LinearSystem>>& getSysVec() const;
	const std::vector<std::shared_ptr<Basis>>& getBasisVec()const;
	//����������С
	int matVecSize() const;
	int detVecSize()const;
	int sysVecSize()const;
	int basisVecSize()const;
	//��������չʾ
	void showMatVec(int index);
	void showDetVec(int index);
	void showSysVec(int index);
	void showBasisVec(int index);
	//��̬�˵�
	void showMenu()override;

	//��̬�Ӳ˵��û���������
	std::tuple<int, int, int, int> showContainerStatement(const std::string& phrase);
	void linearShow();
	std::tuple<ContentVec, int> allocateContent(int _type, int row_, int column_);
	void linearAdd();
	void delFunc(int tuplenum, int _type);
	void linearDelete();
	void linearClear();
	int chooseSearch(int tuplenum, int _type);
	void linearSearch();
	void chooseSort(int tuplenum, int _type);
	void linearSort();
	void linearShuffle();
	//�����Ӳ˵��е�ר�в���
	void linearMatrixFunc();
	void linearDetFunc();
	void linearSystemFunc();
	void linearBasisFunc();

	//չʾ
		//չʾĳ��
	void show(Matrix& matrix);
	void show(Det& det);
	void show(LinearSystem& system);
	void show(Basis& basis);
	//չʾ����
	void show(int _type);


	//���
		//���һ�����󣬿�ѡ������λ������
	bool addItem(Matrix& matrix, int index);
	//���һЩ����
	bool addItem(std::vector<Matrix>& matrixvec, int index);
	//���һ������ʽ����ѡ������λ������
	bool addItem(Det& det, int index);
	//���һЩ����ʽ
	bool addItem(std::vector<Det>& detvec, int index);
	//���һ�����Է����飬��ѡ������λ������
	bool addItem(LinearSystem& system, int index);
	//���һЩ���Է�����
	bool addItem(std::vector<LinearSystem>& systemvec, int index);
	//���һ��������ѡ������λ������
	bool addItem(Basis& basis, int index);
	//���һЩ��
	bool addItem(std::vector<Basis>& basisvec, int index);


	//ɾ��
	bool deleteItem(int _type, int vec_index, int del_number = 1);//ɾ�����ڶ�����������������������������֮���ɾ��������Ĭ��Ϊ1��
	bool clearItem(int _type);//ɾ���������еĶ���
	//��������Ŀն���
	void removeEmpty();

	//����
		//���ң��ҵ����������Ҳ�������-1
		//ע�����Է��������Ǹ���A
	int searchItem(int _type, const ContentVec& blockvec);//��������vector����
	int searchItem(int _type, double first_val);//���ݵ�һ��Ԫ��ֵ����
	int searchItem(int _type, int row, int column);//������������������


	//���������(�Ի�������Ҫ��д���Ĳ���Ϊtrue)
		//����ע�����Է����鰴��A
	bool firstValSort(int _type, bool sort_order);//���ݵ�һ��Ԫ����������ʽ��true������false������
	bool blockSizeSort(int _type, bool sort_order);//���ݴ�С������Ҫ�о�һ���㷨
	bool shuffleItem(int _type);//ϴ��

	//��������
	void castVal(ContentVec& blk);//���������Ȳ���ʱ����������(��������ʽ������)
	void castVal(Basis& basis);//���������Ȳ���ʱ����������(��)

	//�û���������
		//����˵�
	void matrixMainMenu();
	//1.Take Det or Linear System
	void matrixOperation_1(Matrix& temp_matrix, int index);
	//2.Power N
	void matrixOperation_2(Matrix& temp_matrix, int index);
	//3.Multiply a number
	void matrixOperation_3(Matrix& temp_matrix, int index);
	//4.transportortation
	void matrixOperation_4(Matrix& temp_matrix, int index);
	//5.Obtain the minor (��ȡ����ʽ)
	void matrixOperation_5(Matrix& temp_matrix, int index);
	//6.Obtain the adjugate matrix (��ȡ�������)
	void matrixOperation_6(Matrix& temp_matrix, int index);
	//7.Concatenate matrix
	void matrixOperation_7(Matrix& temp_matrix, int index);
	//8.Split matrix
	void matrixOperation_8(Matrix& temp_matrix, int index);
	//9.Elementary row transformation (�����б任)
	void matrixOperation_9(Matrix& temp_matrix, int index);
	//10.Finding the inverse matrix by ERT (�����б任�������)
	void matrixOperation_10(Matrix& temp_matrix, int index);
	//11.Obtain _rank of matrix by ERT (�����б任����)
	void matrixOperation_11(Matrix& temp_matrix, int index);
	//12.multiply a matrix
	void matrixOperation_12(Matrix& temp_matrix, int index);
	//13.Get the inverse matrix directly
	void matrixOperation_13(Matrix& temp_matrix, int index);
	//14.Split matrix into basis(�Ѿ����ɻ�)
	void matrixOperation_14(Matrix& temp_matrix, int index);
	//15.Gain the trace (��ȡ����ļ�)
	void matrixOperation_15(Matrix& temp_matrix, int index);
	//16.Versify the eigen value (�ж��Ƿ�Ϊ����ֵ)
	void matrixOperation_16(Matrix& temp_matrix, int index);
	//17.Find eigen vectors with provided eigen values (�����ṩ������ֵѰ�����е���������)
	void matrixOperation_17(Matrix& temp_matrix, int index);
	//18.Normal diaglization (��ͨ�Խǻ�)
	void matrixOperation_18(Matrix& temp_matrix, int index);
	//19.Orthogonal diaglization (�����Խǻ�)
	void matrixOperation_19(Matrix& temp_matrix, int index);
	//20.Contract diaglization (��ͬ�Խǻ��������ͱ�׼���еĳ��ȱ任��)
	void matrixOperation_20(Matrix& temp_matrix, int index);
	//21.Gain A^n through diaglization (�Խǻ�������ȡA^n)
	void matrixOperation_21(Matrix& temp_matrix, int index);

	//����ʽ�˵�
	void detMainMenu();
	//1.Take Matrix
	void detOperation_1(Det& temp_det, int index);
	//2.Multiply a number on row or column
	void detOperation_2(Det& temp_det, int index);
	//3.transportortation
	void detOperation_3(Det& temp_det, int index);
	//4.Elementary transformation (���ȱ任)
	void detOperation_4(Det& temp_det, int index);
	//5.Finding value of the det by ERT (���ȱ任��ֵ)
	void detOperation_5(Det& temp_det, int index);

	//���Է�����˵�
	void systemMainMenu();
	//1.Get A or B
	void systemOperation_1(LinearSystem& temp_system, int index);
	//2.Solve System by elementary transformation
	void systemOperation_2(LinearSystem& temp_system, int index);
	//3.Solve System (only unhomo) by Law of Cramer(����Ĭ����,���������)
	void systemOperation_3(LinearSystem& temp_system, int index);

	//���˵�
	void basisMainMenu();
	//1.Merge into Matrix
	void basisOperation_1(Basis& temp_basis, int index);
	//2.Gain transition matrix from this to another basis (��ȡ���ɾ���)
	void basisOperation_2(Basis& temp_basis, int index);
	//3.Jugde orthogonal(�ж��Ƿ�����)
	void basisOperation_3(Basis& temp_basis, int index);
	//4.Gain the coordinate with this basis (��������������µ�����)
	void basisOperation_4(Basis& temp_basis, int index);
	//5.Gain metric matrix(��ȡ��������)
	void basisOperation_5(Basis& temp_basis, int index);
	//6.Model a vector(��������ģ)
	void basisOperation_6(Basis& temp_basis, int index);
	//7.Schmidt Orthogonalization(ʩ����������)
	void basisOperation_7(Basis& temp_basis, int index);
	//8.Normalization(��λ��)
	void basisOperation_8(Basis& temp_basis, int index);

	//����ר��

		//�������㹤��
	Det M_takeDet(Matrix& matrix);//ȡ����ʽ
	LinearSystem M_takeLinearSystem(Matrix& matrix);//ȡ���Է����飨��ΪA��
	Matrix M_pow(const Matrix& matrix, int pow);//��������N�η�
	void M_numMult(Matrix& matrix, double number);//����ĳ�����֣��ڶ����ǳ˵�����.
	void M_transport(Matrix& matrix);//����ת��
	Matrix M_getMinor(int index1, int index2, Matrix matrix);//��ȡ����ʽ
	Matrix M_getAdjugate(const Matrix& matrix);//��ȡ�������
	Matrix M_getInverse(Matrix& matrix);//ֱ�ӻ�ȡ�����

	//�����б任�й�
	bool M_onceRowElementaryTransformation(Matrix& matrix, int row1, int row2, double k);//һ�γ����б任���任�ɹ����true:row1+=row2*k
	bool M_onceColumnElementaryTransformation(Matrix& matrix, int column1, int column2, double k);//һ�γ����б任���任�ɹ����true:column1+=column2*k
	int M_typeJudge(Matrix matrix);//�жϳ����б任֮��ľ������������͵ľ���1.�н����ξ���2.������;���3.��׼�;���
	bool M_elementaryRowTransformation(Matrix& matrix);//��γ����б任����
	Matrix M_getInverseByTransformation(Matrix& matrix);//�����б任������󣬱任�ɹ�֮�󷵻������

	//����ƴ������
	Matrix M_concatenate(Matrix& matrix1, Matrix& matrix2, int _type);//����ƴ�ӣ�ǰ����������ƴ�ӵ��������󣬵�������ƴ�ӷ�ʽ��1.A + B; 2.B + A; 3.A����B���棻4.A����B����
	std::pair<Matrix, Matrix> M_split(Matrix& matrix, bool _type, int split_index);//�����֣��ڶ������������ͣ�true�����Ų�false�����Ų�  �����������ǲ�ֵ��л��е�������������������������һ�У����У������棨���ұߣ���

	//��λ�����й�
	Matrix M_generateEleMat(int order);//����һ��order�׵ĵ�λ����
	bool M_isEleMat(Matrix& matrix);//�ж��ǲ��ǵ�λ����

	//���й�
	int S_getRank(Matrix& matrix);//�Է�������г����б任��//�Ծ�����г����б任����(�ı�ԭ������

	//�������
	bool M_isBasis(const Basis& vec);//�������Ƿ�Ϊ�ϸ�Ļ�(��һ�£���Ϊ1)
	Matrix M_mergeBasis(const Basis& basis);//������������)�ϲ�Ϊ����
	Basis  M_takeBasis(Matrix& matrix, bool _type);//�������ɻ�����Ϊ�в���в�(true�����������false�����������
	Matrix M_getTransition(const Basis& basisX, const Basis& basisY);//��ȡ��X��Y�Ĺ��ɾ���P,XP=Y
	bool M_isOrthogonal(const Basis& basis);//�����(������)���ж��Ƿ�����
	ContentVec M_getCoordinate(const ContentVec& vec, const Basis& basis);//���������ڻ��µ����꣬ʹ��y=B^-1 * a,����BΪbasisƴ�����ľ���a��vec
	Matrix M_getMetric(const Basis& basis);//�������������������
	double M_mod(ContentVec& vec);//��ȡ������ģ
	Basis M_SchmidtOrthogonalization(const Basis& basis);//�Ի�����ʩ��������������������������λ�����Ļ�
	void M_normallize(Basis& basis);//�Ի���ʵ�ν��е�λ��

	//��������������ֵ
	bool M_isSymmetric(Matrix& matrix);//�ж��Ƿ�Գ�
	double M_getTrace(Matrix& matrix);//��ȡ����ļ�
	bool M_isEigenValue(const Matrix& matrix, double ��);//��֤�Ƿ�Ϊ����ֵ
	std::map<double, Basis> M_getEigenVector(Matrix& matrix);//��ȡ����������������������ֵ���������������map(�û�����)
	std::pair<Matrix, Matrix> M_normalDiaglization(Matrix& matrix);//��ͨ�Խǻ�,����P��diag
	std::pair<Matrix, Matrix> M_orthogonalDiaglization(Matrix& matrix);//�����Խǻ�������P��diag
	Matrix M_getPowerByDiaglization(Matrix& matrix, int _figure);//ͨ����ͨ�Խǻ���ȡA^n

	//�������еĲ��ֹ���
	bool M_isDiag(Matrix& matrix);//�ж��ǲ��ǶԽǾ���
	std::pair<Matrix, Matrix>M_contractDiaglization(Matrix& matrix);//�������еĺ�ͬ�任����������һ��ΪC^T*A*C,�ڶ���ΪC

	//����ʽר��

		//�������㹤��
	Matrix D_takeMat(const Det& det);//ת��Ϊ����,ע��������premierNum!!!
	void D_numMult(Det& det, bool _type, int index, double number);//��ĳһ�л�ĳһ������ĳ�����֣��ڶ����������л��У�true:�У�false:�У�  ��3��������Ҫ�������л��е�����������������������4���ǳ˵�����.  ����ע�⽫prenum_����number����
	void D_transport(Det& det);//����ʽת�ã�ע������һ��-1
	double D_getValue(Det& det);//ֱ�ӻ�ȡ����ʽ��ֵ

	//����ʽ���ȱ任
	bool D_once_R_elementaryTransformation(Det& det, int row1, int row2, double k);//һ������ʽ�����б任���任�ɹ����true:row1+=row2*k
	bool D_once_C_elementaryTransformation(Det& det, int column1, int column2, double k);//һ������ʽ�����б任���任�ɹ����true:column1+=column2*k
	bool D_elementaryTransformation(Det& det);//�������ʽ���ȱ任����
	double D_getValue_Eletrans(Det& det);//���ȱ任������ʽ��ֵ����ֵ�ɹ�֮�󷵻����ֵ

	//��������ʽ�й�
	bool D_isTriangDet(Det& det);//�ж��ǲ�����������ʽ
	double D_getValue_Triang(Det& det);//��ȡ��������ʽ��ֵ,����������ĺ���


	//���Է�����ר��
	int S_getRank(LinearSystem& system_);//�������A����
	//�����Է�����--���ȱ任��
	ContentVec S_solveHomo(const LinearSystem& system_);//����η����飨������ǻ�����ϵ����
	/*���裺
		1.�ȸ���A������ʽ�ж��Ƿ��з���⣻
		2.��A���ȱ任��Ϊ�н����λ�������λ��׼�ͣ����жϣ�
		3.������1���Ѿ��ų�r=row_��������ʲ����ܳ���Ψһ�⣻
		4.���������δ֪��(r<row_)�������жϳ�X��������δ֪�����±꣬Ȼ����������б任Ϊ������Σ����ա��÷������õ�X�������ֵ��ɵ����飨������ϵ����
		5.������������ϵ��*/
	std::pair<ContentVec, ContentVec> S_solveUnhomo(const LinearSystem& system_);//�����η����飨���firstΪ��Ӧ��η�����Ļ�����ϵ��secondΪ�����ͨ�⣩
	/*���裺
		1.�Ƚ����������ȱ任Ϊ�н����Σ��ǵ��жϣ���Ȼ���ж�r(A) == r(A, b)��������Ⱦ�ֹ���ڴˣ�
		2.�����ȣ��ͽ���Ӧ��η�����Ļ�����ϵ��
		3.Ū����һ��������ؽ⣨�ֶ����۲취�������ж��Ƿ���ϣ������Ͼ������ң�
		4.�ҵ��˾����������ϵ���ؽ�Ķ��顣*/
	void S_showSol(const std::pair<ContentVec, ContentVec>& solutions_pair);//����������ӵ���ʽչʾ��λ����η������ͨ�⣨��⣬���޽⣩����Ҫ�Զ��ж�,���������ͨ���ұ��ؽ⣨���ŵģ�

	//�����Է�����--����Ĭ����
	bool S_isCramer(const LinearSystem& system);//�ж��Ƿ��ʺϿ���Ĭ�������������һ��N*��N+1���ģ�
	std::vector<Det> S_generateRLD(const LinearSystem& system);//���ж��ʺϿ���Ĭ���������ȥ����һ�е�����ʽ�����飬��˳�����ֱ���D1,D2,...,Dn,D����Ҫ������������ж�
	ContentVec S_getCramerSol(LinearSystem& system_);//�õ�����Ĭ����Ľ⣬��Ҫʹ���������������


};
