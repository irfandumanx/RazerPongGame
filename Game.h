#pragma once

#include "APKeyboard.h"
#include "Ball.h"
#include <mutex>

#define STICK_LENGTH 3

class Game {
private:
    int score = 0;
    bool finish = false;
    int* stick = new int[STICK_LENGTH];
    class APKeyboard* apKeyboard;
    static Game* instance;  
    static std::mutex mutex;
public:
    Game();
    ~Game() { delete[] stick; }
    Game(Game& game) = delete;
    //void operator=(const Game&) = delete;
    static Game* getInstance();
    void increaseScore() { score++; }
    int getScore() { return this->score; }
    bool isFinish() { return this->finish; }
    void setFinish(bool finish) { this->finish = finish; }
    int* getStick() { return stick; }
    void isGameOver(class Ball* ball);
    APKeyboard* getKeyboard();
    Ball initBall();
};