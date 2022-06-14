#pragma once

#include "APKeyboard.h"
#include "LibraryLoader.h"
#include <thread>
#include <iostream>
#define STICK_LENGTH 3

using namespace std;
using namespace RKeyboard;
using namespace ChromaSDK::Keyboard;

typedef struct {
	int previousBallLocation;
	int currentBallLocation;
} BallLocation;

enum BallDirection {
	CROSS_LEFT_DOWN = 0,
	CROSS_LEFT_UP,
	CROSS_RIGHT_DOWN,
	CROSS_RIGHT_UP,
	STRAIGHT_UP,
	STRAIGHT_DOWN
};

enum BallCollision {
	LEFT_BORDER = 0,
	RIGHT_BORDER,
	TOP_BORDER
};

enum BallCollisionTypeWithStick {
	LEFT = 0,
	MIDDLE,
	RIGHT,
	NO_COLLISION
};

class Ball {
private:
	class thread* threadBall;
	int key;
	const int rightAndLeftBorders[7] = { /*SAÐ TARAF*/ RZKEY::RZKEY_BACKSPACE, RZKEY::RZKEY_ENTER, /* SOL TARAF */ RZKEY::RZKEY_ESC, RZKEY::RZKEY_ENTER, RZKEY::RZKEY_TAB, RZKEY::RZKEY_CAPSLOCK, RZKEY::RZKEY_OEM_1 };
	const int topBorders[11] = { RZKEY::RZKEY_F1, RZKEY::RZKEY_F2, RZKEY::RZKEY_F3, RZKEY::RZKEY_F4, RZKEY::RZKEY_F5, RZKEY::RZKEY_F6, RZKEY::RZKEY_F7, RZKEY::RZKEY_F8, RZKEY::RZKEY_F9, RZKEY::RZKEY_F10, RZKEY::RZKEY_F11 };
	BallLocation ballLocation;
	BallDirection ballDirection;	
	BallDirection findDirection(short value);
	BallCollisionTypeWithStick findCollisionWithStick(short value);
	BallCollision checkCollisionWithBorders();
	BallCollisionTypeWithStick checkCollisionWithStick();
	void updateMyColor();
	void setBallDirectionRelativeToStick(BallCollisionTypeWithStick ballCollisionTypeWithStick);
	void setBallDirectionRelativeToBorderCollision(BallCollision ballCollision);
	void setLocation();
public:
	Ball(BallLocation ballLocation, short value, int key);
	BallLocation getBallLocation() { return this->ballLocation; }
	BallDirection getBallDirection() { return this->ballDirection; }
	int getKey() { return this->key; }
	void setBallLocation(BallLocation ballLocation) { this->ballLocation = ballLocation; }
	void setBallDirection(BallDirection ballDirection) { this->ballDirection = ballDirection; }
	void setKey(int key) { this->key = key; }
	void moveBall();
};