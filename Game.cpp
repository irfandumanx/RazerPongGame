#include "Game.h"

std::mutex Game::mutex;
Game* Game::instance{ nullptr };

Game::Game() {
	apKeyboard = new APKeyboard(this);
}
Game* Game::getInstance() {
    std::lock_guard<std::mutex> lock(Game::mutex);
    if (instance == nullptr)
        instance = new Game();
    return instance;
}

void Game::isGameOver(class Ball* ball) {
	if (ball->getBallLocation().currentBallLocation >= 0x0500)
	{
		Game::getInstance()->setFinish(true);
		apKeyboard->showFinishKeyboardEffect();
		exit(0);
	}
}

Ball Game::initBall() {
	//0 - 2(dahil) kat seç
	unsigned char floor = rand() % 3;
	//sýra seç
	short row = rand() % 12;
	short key = (floor * 0x0100) + row + 1;
	int direction = rand() % 6;
	APKeyboard::getColorsKeyboard()[KeyboardUtils::getRazerKeyValue(key)] = ColorUtils::getRGB(ColorUtils::ballColor);

	return Ball::Ball({ 0, key }, direction, key);
}

APKeyboard* Game::getKeyboard() {
	return apKeyboard;
}