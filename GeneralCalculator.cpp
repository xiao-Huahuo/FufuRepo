#include"GeneralCalculator.h"
using namespace std;

//���캯��������MessagePair�����ֺ�����Ķ��飩
GC::GC(const MessagePair& inputPair, int _type) :name_(inputPair.first), password_(inputPair.second), persontype_(_type) {}
GC::~GC() {}


//��̬�˵�
void GC::showMenu() {}
