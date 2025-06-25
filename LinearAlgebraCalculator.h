#pragma once
#include"AbstractCalculator.h"
#include"LinearSystem.h"
#include<random>
#include<ctime>

class LAC :public AbstractCalculator
{
private:
	//注意：_type的值代表：
	//1.矩阵；2.行列式；3.线性方程组
	std::vector<std::shared_ptr<Matrix>>matrixVector_;//存放矩阵的智能指针数组
	std::vector<std::shared_ptr<Det>>detVector_;//存放行列式的智能指针数组
	std::vector<std::shared_ptr<LinearSystem>>systemVector_;//存放线性方程组的数组
	std::vector<std::shared_ptr<Basis>>basisVector_;//存放基的数组
	std::string name_;
	std::string password_;
	int persontype_;
public:
	//人类至高无上的理想
	void __Soviet__();

	//保存和读取各类数据结构到文件的子函数
	void saveMatrix();
	void readMatrixFromFile();
	void saveDet();
	void readDetFromFile();
	void saveLinearSystem();
	void readLinearSystemFromFile();
	void saveBasis();
	void readBasisFromFile();

	// 保存矩阵、行列式、线性方程组、基到文件
	void saveFile();
	// 从文件中读取矩阵、行列式、线性方程组、基
	void readFile();

	//构造函数：传入MessagePair（名字和密码的对组）
	LAC(const MessagePair& inputPair, int _type);
	~LAC();

	//获取private的接口
	const std::vector<std::shared_ptr<Matrix>>& getMatVec() const;
	const std::vector<std::shared_ptr<Det>>& getDetVec() const;
	const std::vector<std::shared_ptr<LinearSystem>>& getSysVec() const;
	const std::vector<std::shared_ptr<Basis>>& getBasisVec()const;
	//返回容器大小
	int matVecSize() const;
	int detVecSize()const;
	int sysVecSize()const;
	int basisVecSize()const;
	//根据索引展示
	void showMatVec(int index);
	void showDetVec(int index);
	void showSysVec(int index);
	void showBasisVec(int index);
	//多态菜单
	void showMenu()override;

	//多态子菜单用户交互函数
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
	//功能子菜单中的专有操作
	void linearMatrixFunc();
	void linearDetFunc();
	void linearSystemFunc();
	void linearBasisFunc();

	//展示
		//展示某个
	void show(Matrix& matrix);
	void show(Det& det);
	void show(LinearSystem& system);
	void show(Basis& basis);
	//展示所有
	void show(int _type);


	//添加
		//添加一个矩阵，可选择插入的位置索引
	bool addItem(Matrix& matrix, int index);
	//添加一些矩阵
	bool addItem(std::vector<Matrix>& matrixvec, int index);
	//添加一个行列式，可选择插入的位置索引
	bool addItem(Det& det, int index);
	//添加一些行列式
	bool addItem(std::vector<Det>& detvec, int index);
	//添加一个线性方程组，可选择插入的位置索引
	bool addItem(LinearSystem& system, int index);
	//添加一些线性方程组
	bool addItem(std::vector<LinearSystem>& systemvec, int index);
	//添加一个基，可选择插入的位置索引
	bool addItem(Basis& basis, int index);
	//添加一些基
	bool addItem(std::vector<Basis>& basisvec, int index);


	//删除
	bool deleteItem(int _type, int vec_index, int del_number = 1);//删除，第二个参数是索引，第三个是索引及之后的删除数量（默认为1）
	bool clearItem(int _type);//删除数组所有的东西
	//清除容器的空东西
	void removeEmpty();

	//查找
		//查找：找到了索引，找不到返回-1
		//注：线性方程组则是根据A
	int searchItem(int _type, const ContentVec& blockvec);//根据内容vector查找
	int searchItem(int _type, double first_val);//根据第一个元素值查找
	int searchItem(int _type, int row, int column);//根据行数和列数查找


	//排序和乱序(对基的排序要填写最后的参数为true)
		//排序，注意线性方程组按照A
	bool firstValSort(int _type, bool sort_order);//根据第一个元素排序，排序方式：true：升序；false：逆序；
	bool blockSizeSort(int _type, bool sort_order);//根据大小排序，需要研究一点算法
	bool shuffleItem(int _type);//洗牌

	//其他工具
	void castVal(ContentVec& blk);//浮点数精度不够时，四舍五入(矩阵行列式方程组)
	void castVal(Basis& basis);//浮点数精度不够时，四舍五入(基)

	//用户交互部分
		//矩阵菜单
	void matrixMainMenu();
	//1.Take Det or Linear System
	void matrixOperation_1(Matrix& temp_matrix, int index);
	//2.Power N
	void matrixOperation_2(Matrix& temp_matrix, int index);
	//3.Multiply a number
	void matrixOperation_3(Matrix& temp_matrix, int index);
	//4.transportortation
	void matrixOperation_4(Matrix& temp_matrix, int index);
	//5.Obtain the minor (获取余子式)
	void matrixOperation_5(Matrix& temp_matrix, int index);
	//6.Obtain the adjugate matrix (获取伴随矩阵)
	void matrixOperation_6(Matrix& temp_matrix, int index);
	//7.Concatenate matrix
	void matrixOperation_7(Matrix& temp_matrix, int index);
	//8.Split matrix
	void matrixOperation_8(Matrix& temp_matrix, int index);
	//9.Elementary row transformation (初等行变换)
	void matrixOperation_9(Matrix& temp_matrix, int index);
	//10.Finding the inverse matrix by ERT (初等行变换求逆矩阵)
	void matrixOperation_10(Matrix& temp_matrix, int index);
	//11.Obtain _rank of matrix by ERT (初等行变换求秩)
	void matrixOperation_11(Matrix& temp_matrix, int index);
	//12.multiply a matrix
	void matrixOperation_12(Matrix& temp_matrix, int index);
	//13.Get the inverse matrix directly
	void matrixOperation_13(Matrix& temp_matrix, int index);
	//14.Split matrix into basis(把矩阵拆成基)
	void matrixOperation_14(Matrix& temp_matrix, int index);
	//15.Gain the trace (获取矩阵的迹)
	void matrixOperation_15(Matrix& temp_matrix, int index);
	//16.Versify the eigen value (判断是否为特征值)
	void matrixOperation_16(Matrix& temp_matrix, int index);
	//17.Find eigen vectors with provided eigen values (根据提供的特征值寻找所有的特征向量)
	void matrixOperation_17(Matrix& temp_matrix, int index);
	//18.Normal diaglization (普通对角化)
	void matrixOperation_18(Matrix& temp_matrix, int index);
	//19.Orthogonal diaglization (正交对角化)
	void matrixOperation_19(Matrix& temp_matrix, int index);
	//20.Contract diaglization (合同对角化，二次型标准化中的初等变换法)
	void matrixOperation_20(Matrix& temp_matrix, int index);
	//21.Gain A^n through diaglization (对角化方法获取A^n)
	void matrixOperation_21(Matrix& temp_matrix, int index);

	//行列式菜单
	void detMainMenu();
	//1.Take Matrix
	void detOperation_1(Det& temp_det, int index);
	//2.Multiply a number on row or column
	void detOperation_2(Det& temp_det, int index);
	//3.transportortation
	void detOperation_3(Det& temp_det, int index);
	//4.Elementary transformation (初等变换)
	void detOperation_4(Det& temp_det, int index);
	//5.Finding value of the det by ERT (初等变换求值)
	void detOperation_5(Det& temp_det, int index);

	//线性方程组菜单
	void systemMainMenu();
	//1.Get A or B
	void systemOperation_1(LinearSystem& temp_system, int index);
	//2.Solve System by elementary transformation
	void systemOperation_2(LinearSystem& temp_system, int index);
	//3.Solve System (only unhomo) by Law of Cramer(克拉默法则,仅仅非齐次)
	void systemOperation_3(LinearSystem& temp_system, int index);

	//基菜单
	void basisMainMenu();
	//1.Merge into Matrix
	void basisOperation_1(Basis& temp_basis, int index);
	//2.Gain transition matrix from this to another basis (获取过渡矩阵)
	void basisOperation_2(Basis& temp_basis, int index);
	//3.Jugde orthogonal(判断是否正交)
	void basisOperation_3(Basis& temp_basis, int index);
	//4.Gain the coordinate with this basis (求向量在这组基下的坐标)
	void basisOperation_4(Basis& temp_basis, int index);
	//5.Gain metric matrix(获取度量矩阵)
	void basisOperation_5(Basis& temp_basis, int index);
	//6.Model a vector(求向量的模)
	void basisOperation_6(Basis& temp_basis, int index);
	//7.Schmidt Orthogonalization(施密特正交化)
	void basisOperation_7(Basis& temp_basis, int index);
	//8.Normalization(单位化)
	void basisOperation_8(Basis& temp_basis, int index);

	//矩阵专有

		//基本计算工具
	Det M_takeDet(Matrix& matrix);//取行列式
	LinearSystem M_takeLinearSystem(Matrix& matrix);//取线性方程组（作为A）
	Matrix M_pow(const Matrix& matrix, int pow);//计算矩阵的N次方
	void M_numMult(Matrix& matrix, double number);//数乘某个数字，第二个是乘的数字.
	void M_transport(Matrix& matrix);//矩阵转置
	Matrix M_getMinor(int index1, int index2, Matrix matrix);//获取余子式
	Matrix M_getAdjugate(const Matrix& matrix);//获取伴随矩阵
	Matrix M_getInverse(Matrix& matrix);//直接获取逆矩阵

	//初等行变换有关
	bool M_onceRowElementaryTransformation(Matrix& matrix, int row1, int row2, double k);//一次初等行变换，变换成功输出true:row1+=row2*k
	bool M_onceColumnElementaryTransformation(Matrix& matrix, int column1, int column2, double k);//一次初等列变换，变换成功输出true:column1+=column2*k
	int M_typeJudge(Matrix matrix);//判断初等行变换之后的矩阵是哪种类型的矩阵：1.行阶梯形矩阵；2.行最简型矩阵；3.标准型矩阵。
	bool M_elementaryRowTransformation(Matrix& matrix);//多次初等行变换函数
	Matrix M_getInverseByTransformation(Matrix& matrix);//初等行变换求逆矩阵，变换成功之后返回逆矩阵

	//矩阵拼接与拆分
	Matrix M_concatenate(Matrix& matrix1, Matrix& matrix2, int _type);//矩阵拼接，前两个参数是拼接的两个矩阵，第三个是拼接方式：1.A + B; 2.B + A; 3.A上面B下面；4.A下面B上面
	std::pair<Matrix, Matrix> M_split(Matrix& matrix, bool _type, int split_index);//矩阵拆分，第二个参数是类型：true：横着拆；false：竖着拆；  第三个参数是拆分的行或列的索引（是索引！！！）从这一行（或列）的下面（或右边）拆。

	//单位矩阵有关
	Matrix M_generateEleMat(int order);//生成一个order阶的单位矩阵
	bool M_isEleMat(Matrix& matrix);//判断是不是单位矩阵

	//秩有关
	int S_getRank(Matrix& matrix);//对方程组进行初等行变换求//对矩阵进行初等行变换求秩(改变原来矩阵）

	//基与矩阵
	bool M_isBasis(const Basis& vec);//鉴定基是否为合格的基(行一致，列为1)
	Matrix M_mergeBasis(const Basis& basis);//将基（列向量)合并为矩阵
	Basis  M_takeBasis(Matrix& matrix, bool _type);//将矩阵拆成基，分为行拆和列拆(true拆成列向量，false拆成行向量）
	Matrix M_getTransition(const Basis& basisX, const Basis& basisY);//获取从X到Y的过渡矩阵P,XP=Y
	bool M_isOrthogonal(const Basis& basis);//传入基(列向量)，判断是否正交
	ContentVec M_getCoordinate(const ContentVec& vec, const Basis& basis);//求列向量在基下的坐标，使用y=B^-1 * a,其中B为basis拼起来的矩阵，a是vec
	Matrix M_getMetric(const Basis& basis);//传入基，传出度量矩阵
	double M_mod(ContentVec& vec);//获取向量的模
	Basis M_SchmidtOrthogonalization(const Basis& basis);//对基进行施密特正交化，传出正交（不单位化）的基
	void M_normallize(Basis& basis);//对基的实参进行单位化

	//特征向量与特征值
	bool M_isSymmetric(Matrix& matrix);//判断是否对称
	double M_getTrace(Matrix& matrix);//获取矩阵的迹
	bool M_isEigenValue(const Matrix& matrix, double λ);//验证是否为特征值
	std::map<double, Basis> M_getEigenVector(Matrix& matrix);//获取所有特征向量，返回特征值和特征向量对组的map(用户交互)
	std::pair<Matrix, Matrix> M_normalDiaglization(Matrix& matrix);//普通对角化,传出P和diag
	std::pair<Matrix, Matrix> M_orthogonalDiaglization(Matrix& matrix);//正交对角化，传出P和diag
	Matrix M_getPowerByDiaglization(Matrix& matrix, int _figure);//通过普通对角化获取A^n

	//二次型中的部分功能
	bool M_isDiag(Matrix& matrix);//判断是不是对角矩阵
	std::pair<Matrix, Matrix>M_contractDiaglization(Matrix& matrix);//二次型中的合同变换法，传出第一个为C^T*A*C,第二个为C

	//行列式专有

		//基本计算工具
	Matrix D_takeMat(const Det& det);//转变为矩阵,注：忽略了premierNum!!!
	void D_numMult(Det& det, bool _type, int index, double number);//对某一行或某一列数乘某个数字，第二个参数是行或列：true:行，false:列；  第3个参数是要操作的行或列的索引（索引！！！）；第4个是乘的数字.  ！！注意将prenum_除以number！！
	void D_transport(Det& det);//行列式转置，注意数乘一个-1
	double D_getValue(Det& det);//直接获取行列式的值

	//行列式初等变换
	bool D_once_R_elementaryTransformation(Det& det, int row1, int row2, double k);//一次行列式初等行变换，变换成功输出true:row1+=row2*k
	bool D_once_C_elementaryTransformation(Det& det, int column1, int column2, double k);//一次行列式初等列变换，变换成功输出true:column1+=column2*k
	bool D_elementaryTransformation(Det& det);//多次行列式初等变换函数
	double D_getValue_Eletrans(Det& det);//初等变换求行列式的值，求值成功之后返回这个值

	//三角行列式有关
	bool D_isTriangDet(Det& det);//判断是不是三角行列式
	double D_getValue_Triang(Det& det);//获取三角行列式的值,包含了上面的函数


	//线性方程组专有
	int S_getRank(LinearSystem& system_);//方程组的A求秩
	//解线性方程组--初等变换法
	ContentVec S_solveHomo(const LinearSystem& system_);//解齐次方程组（输出的是基础解系）；
	/*步骤：
		1.先根据A的行列式判断是否有非零解；
		2.将A初等变换化为行阶梯形或行最简形或标准型，并判断；
		3.由于在1中已经排除r=row_的情况，故不可能出现唯一解；
		4.如果有自由未知量(r<row_)，则先判断出X里面自由未知量的下标，然后继续初等行变换为行最简形，按照“好方法”得到X所有项的值组成的数组（基础解系）；
		5.输出这个基础解系。*/
	std::pair<ContentVec, ContentVec> S_solveUnhomo(const LinearSystem& system_);//解非齐次方程组（输出first为相应齐次方程组的基础解系，second为非齐次通解）
	/*步骤：
		1.先将增广矩阵初等变换为行阶梯形（记得判断），然后判断r(A) == r(A, b)，如果不等就止步于此；
		2.如果相等，就解相应齐次方程组的基础解系；
		3.弄出来一个非齐次特解（手动，观察法），并判断是否符合，不符合就重新找；
		4.找到了就输出基础解系和特解的对组。*/
	void S_showSol(const std::pair<ContentVec, ContentVec>& solutions_pair);//以列向量相加的形式展示齐次或非齐次方程组的通解（或解，或无解），需要自动判断,传入是左边通解右边特解（竖着的）

	//解线性方程组--克拉默法则
	bool S_isCramer(const LinearSystem& system);//判断是否适合克拉默法则（增广矩阵是一个N*（N+1）的）
	std::vector<Det> S_generateRLD(const LinearSystem& system);//在判断适合克拉默法则后生成去除这一列的行列式的数组，按顺序来分别是D1,D2,...,Dn,D；需要根据增广矩阵判断
	ContentVec S_getCramerSol(LinearSystem& system_);//得到克拉默法则的解，需要使用上面的两个函数


};
