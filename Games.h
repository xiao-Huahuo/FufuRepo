#pragma once
#include"AbstractCalculator.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<graphics.h>
#include<conio.h>
#include<chrono>
#include<thread>
#include"GlobalFile.h"

//贪吃蛇的宏定义
#define BOARDER "*"
#define SnakeBODY "o"
#define FOOD "@"
#define Xorigin 10
#define Yorigin 5
const int kWIDTH = 50;
const int kHEIGHT = 20;

class Point { public:int x, y; };

                    class GMS :public AbstractCalculator
                    {
                    private:
                        std::string name_;
                        std::string password_;
                        int persontype_;
                    public:

                        //构造函数：传入MessagePair（名字和密码的对组）
                        GMS(const MessagePair& inputPair, int _type);
                        ~GMS();


                        //多态菜单
                        void showMenu()override;
                    };

                    class Snake
                    {
                    public:
                        Point snake_[100];
                        int snake_length_;
                        Point food_;
                        int score_;
                        bool gameover_;
                        char direction_; // 'r' for right, 'l' for left, 'u' for up, 'd' for down

                        Snake();
                        ~Snake();
                        void setupSnake();
                        void drawSnake();
                        void manipulateSnake();
                        void logics();
                        void playSnake();
                        void resetGame();
                    };
