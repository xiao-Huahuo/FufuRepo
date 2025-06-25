#pragma once
#include<vector>
#include<iostream>
#include<map>
#include<string>
#include<thread>
#include<chrono>
typedef std::vector<std::vector<double>> ContentVec;//���������ʽ�Ĺ�ͬ����
typedef double (*Operation1)(double);//һԪ���㺯��ָ��
typedef double (*Operation2)(double, double);//��Ԫ���㺯��ָ��
typedef std::pair<std::string, std::string> MessagePair;//���ֺ�����Ķ���
typedef std::vector<ContentVec> Basis;//���������vector

#define HUMAN_FILE "HumanFile.txt"
#define AdminISTRATOR_FILE "Account_and_Password.txt"
#define ERR_PHRASE "Fault input ! Operation has been withdrawn."
#define REINPUT_PHRASE "Fault input ! Please input again !"
#define EPSILON 1e-3//�����������ֵ
#define MATRIX_FILE "Matrix.txt"
#define DET_FILE "Det.txt"
#define LINEARSYSTEM_FILE "LinearSystem.txt"
#define BASIS_FILE "Basis.txt"


