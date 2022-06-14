#include "Ball.h"

Ball::Ball(BallLocation ballLocation, short value, int key) {
	this->ballLocation = ballLocation;
	this->ballDirection = findDirection(value);
	this->key = key;
	threadBall = new thread(&Ball::moveBall, this);
}

BallDirection Ball::findDirection(short value) {
	switch (value)
	{
		case 0: return BallDirection::CROSS_LEFT_DOWN;
		case 1: return BallDirection::CROSS_LEFT_UP;
		case 2: return BallDirection::CROSS_RIGHT_DOWN;
		case 3: return BallDirection::CROSS_RIGHT_UP;
		case 4: return BallDirection::STRAIGHT_UP;
		case 5: return BallDirection::STRAIGHT_DOWN;
		default: std::cerr << "Topun yonunu bulurken hata olustu";
	}
}

BallCollisionTypeWithStick Ball::findCollisionWithStick(short value) {
	unsigned char splitStick = STICK_LENGTH / 2;

	if (value < splitStick) return BallCollisionTypeWithStick::LEFT;
	else if (value >= splitStick && value < splitStick * 2) return BallCollisionTypeWithStick::MIDDLE;
	else if (value >= splitStick * 2) return BallCollisionTypeWithStick::RIGHT;
	else std::cerr << "Topun cubuk ile iliskisinde hata olustu";
}

void Ball::updateMyColor() {
	APKeyboard::getColorsKeyboard()[KeyboardUtils::getRazerKeyValue(ballLocation.previousBallLocation)] = ColorUtils::getRGB(ColorUtils::noneColor);
	APKeyboard::getColorsKeyboard()[KeyboardUtils::getRazerKeyValue(ballLocation.currentBallLocation)] = ColorUtils::getRGB(ColorUtils::ballColor);
}

BallCollision Ball::checkCollisionWithBorders() {
	unsigned char i;
	for (i = 0; i < 2; i++)
	{
		if (ballLocation.currentBallLocation == rightAndLeftBorders[i]) return BallCollision::RIGHT_BORDER;
	}
	for (i = 2; i < sizeof(rightAndLeftBorders) / sizeof(rightAndLeftBorders[0]); i++)
	{
		if (ballLocation.currentBallLocation == rightAndLeftBorders[i]) return BallCollision::LEFT_BORDER;
	}
	for (i = 0; i < sizeof(topBorders) / sizeof(topBorders[0]); i++)
	{
		if (ballLocation.currentBallLocation == topBorders[i]) return BallCollision::TOP_BORDER;
	}
}

BallCollisionTypeWithStick Ball::checkCollisionWithStick() {
	unsigned char i;
	for (i = 0; i < STICK_LENGTH; i++)
	{
		if (ballLocation.currentBallLocation + 0x0100 == Game::getInstance()->getStick()[i]) {
			Game::getInstance()->increaseScore();
			Game::getInstance()->getKeyboard()->showScoreWithKeyboardKeys(Game::getInstance()->getScore());
			return findCollisionWithStick(i);
		}
	}
	return BallCollisionTypeWithStick::NO_COLLISION;
}

void Ball::setBallDirectionRelativeToStick(BallCollisionTypeWithStick ballCollisionTypeWithStick) {
	if (ballCollisionTypeWithStick == BallCollisionTypeWithStick::LEFT) ballDirection = BallDirection::CROSS_LEFT_UP;
	else if (ballCollisionTypeWithStick == BallCollisionTypeWithStick::RIGHT) ballDirection = BallDirection::CROSS_RIGHT_UP;
	else if (ballCollisionTypeWithStick == BallCollisionTypeWithStick::MIDDLE) ballDirection = BallDirection::STRAIGHT_UP;
	else Game::getInstance()->isGameOver(this);
}

void Ball::setBallDirectionRelativeToBorderCollision(BallCollision ballCollision) {
	if (ballCollision == BallCollision::LEFT_BORDER)
	{
		if (ballDirection == BallDirection::CROSS_LEFT_DOWN) ballDirection = BallDirection::CROSS_RIGHT_DOWN;
		else if (ballDirection == BallDirection::CROSS_LEFT_UP) ballDirection = BallDirection::CROSS_RIGHT_UP;
	}
	else if (ballCollision == BallCollision::RIGHT_BORDER) {
		if (ballLocation.currentBallLocation == RZKEY::RZKEY_ENTER) {
			ballLocation.previousBallLocation = RZKEY::RZKEY_ENTER;
			ballLocation.currentBallLocation = 0x030C;
		}
		if (ballDirection == BallDirection::CROSS_RIGHT_DOWN) ballDirection = BallDirection::CROSS_LEFT_DOWN;
		else if (ballDirection == BallDirection::CROSS_RIGHT_UP) ballDirection = BallDirection::CROSS_LEFT_UP;
	}
	else if (ballCollision == BallCollision::TOP_BORDER)
	{
		if (ballDirection == BallDirection::CROSS_RIGHT_UP) ballDirection = BallDirection::CROSS_RIGHT_DOWN;
		else if (ballDirection == BallDirection::CROSS_LEFT_UP) ballDirection = BallDirection::CROSS_LEFT_DOWN;
		else if (ballDirection == BallDirection::STRAIGHT_UP) ballDirection = BallDirection::STRAIGHT_DOWN;
	}
}

void Ball::setLocation() {
	int newKey = 0;
	if (ballDirection == BallDirection::CROSS_LEFT_DOWN) newKey = (key + 0x0100) - 0x0001;
	else if (ballDirection == BallDirection::CROSS_LEFT_UP) newKey = (key - 0x0100) - 0x0001;
	else if (ballDirection == BallDirection::CROSS_RIGHT_DOWN) newKey = (key + 0x0100) + 0x0001;
	else if (ballDirection == BallDirection::CROSS_RIGHT_UP) newKey = (key - 0x0100) + 0x0001;
	else if (ballDirection == BallDirection::STRAIGHT_DOWN) newKey = (key + 0x0100);
	else if (ballDirection == BallDirection::STRAIGHT_UP) newKey = (key - 0x0100);
	setBallLocation({ key, newKey });
	setKey(newKey);
}

void Ball::moveBall() {
	while (true)
	{
		Sleep(300);
		BallCollision collision = checkCollisionWithBorders();
		setBallDirectionRelativeToBorderCollision(collision);

		BallCollisionTypeWithStick ballCollisionTypeWithStick = checkCollisionWithStick();
		setBallDirectionRelativeToStick(ballCollisionTypeWithStick);

		setLocation();
		updateMyColor();
	}
}