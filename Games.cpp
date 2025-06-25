#include"Games.h"

using namespace std;

//构造函数：传入MessagePair（名字和密码的对组）
GMS::GMS(const MessagePair& inputPair, int _type) :name_(inputPair.first), password_(inputPair.second), persontype_(_type) {}
GMS::~GMS() {}


//多态菜单
void GMS::showMenu()
{
    std::cout << "=========================GAMES===========================" << std::endl;
    std::cout << "\t1.Snake" << std::endl;
    std::cout << "\t0.Exit" << std::endl;
}





Snake::Snake() :snake_length_(5), score_(0), gameover_(false), direction_('r') {}
Snake::~Snake() {};
void Snake::setupSnake() {
    srand(time(0));
    food_.x = Xorigin + rand() % (kWIDTH / 2);
    food_.y = Yorigin + rand() % (kHEIGHT / 2);

    snake_[0].x = kWIDTH / 2;
    snake_[0].y = kHEIGHT / 2;

    for (int i = 1; i < snake_length_; ++i) {
        snake_[i].x = snake_[0].x - i;
        snake_[i].y = snake_[0].y;
    }
}
void Snake::drawSnake() {
    system("cls");
    for (int i = 0; i < kWIDTH + 2; i++) std::cout << BOARDER;
    std::cout << std::endl;

    for (int i = 0; i < kHEIGHT; i++) {
        for (int j = 0; j < kWIDTH; j++) {
            if (j == 0) std::cout << BOARDER;
            bool print = false;
            for (int k = 0; k < snake_length_; k++) {
                if (snake_[k].x == j && snake_[k].y == i) {
                    std::cout << SnakeBODY;
                    print = true;
                    break;
                }
            }
            if (!print && food_.x == j && food_.y == i) std::cout << FOOD;
            else if (!print) std::cout << " ";
            if (j == kWIDTH - 1) std::cout << BOARDER;
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < kWIDTH + 2; i++) std::cout << BOARDER;
    std::cout << std::endl;
    std::cout << "Score: " << score_ << std::endl;
}
void Snake::manipulateSnake() {
    if (_kbhit()) {
        char c = _getch();
        switch (c) {
        case 'a': direction_ = 'l'; break;
        case 'd': direction_ = 'r'; break;
        case 'w': direction_ = 'u'; break;
        case 's': direction_ = 'd'; break;
        }
    }
}
void Snake::logics() {
    Point prev = snake_[0];
    Point prev2;

    switch (direction_) {
    case 'l': prev2 = { prev.x - 1, prev.y }; break;
    case 'r': prev2 = { prev.x + 1, prev.y }; break;
    case 'u': prev2 = { prev.x, prev.y - 1 }; break;
    case 'd': prev2 = { prev.x, prev.y + 1 }; break;
    }

    // Move the snake_
    for (int i = snake_length_; i > 0; i--) {
        snake_[i] = snake_[i - 1];
    }
    snake_[0] = prev2;

    // Check collision with food_
    if (snake_[0].x == food_.x && snake_[0].y == food_.y) {
        score_ += 10;
        snake_length_++;
        food_ = { rand() % kWIDTH, rand() % kHEIGHT };
    }

    // Check collision with wall
    if (snake_[0].x < 0 || snake_[0].x >= kWIDTH || snake_[0].y < 0 || snake_[0].y >= kHEIGHT) {
        gameover_ = true;
    }

    // Check collision with self
    for (int i = 1; i < snake_length_; i++) {
        if (snake_[0].x == snake_[i].x && snake_[0].y == snake_[i].y) gameover_ = true;
    }
}
void Snake::playSnake()
{
    setupSnake();
    while (!gameover_) {
        drawSnake();
        manipulateSnake();
        logics();
        //this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "Game Over! Your score_ is " << score_ << std::endl;
}
void Snake::resetGame()
{
    snake_length_ = 5;
    score_ = 0;
    gameover_ = false;
    direction_ = 'r'; // 'r' for right, 'l' for left, 'u' for up, 'd' for down

}




