#pragma once
#include<vector>
#include<iostream>
#include<map>
#include<string>
#include<thread>
#include<chrono>
typedef std::vector<std::vector<double>> ContentVec;//矩阵和行列式的共同数组
typedef double (*Operation1)(double);//一元运算函数指针
typedef double (*Operation2)(double, double);//二元运算函数指针
typedef std::pair<std::string, std::string> MessagePair;//名字和密码的对组
typedef std::vector<ContentVec> Basis;//存放向量的vector

#define HUMAN_FILE "HumanFile.txt"
#define AdminISTRATOR_FILE "Account_and_Password.txt"
#define ERR_PHRASE "Fault input ! Operation has been withdrawn."
#define REINPUT_PHRASE "Fault input ! Please input again !"
#define EPSILON 1e-3//四舍五入的阈值
#define MATRIX_FILE "Matrix.txt"
#define DET_FILE "Det.txt"
#define LINEARSYSTEM_FILE "LinearSystem.txt"
#define BASIS_FILE "Basis.txt"


