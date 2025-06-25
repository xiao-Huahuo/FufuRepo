#include"GeneralCalculator.h"
using namespace std;

//构造函数：传入MessagePair（名字和密码的对组）
GC::GC(const MessagePair& inputPair, int _type) :name_(inputPair.first), password_(inputPair.second), persontype_(_type) {}
GC::~GC() {}


//多态菜单
void GC::showMenu() {}
