#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <math.h>
#include <thread>
#include <tchar.h>
#include <time.h>
#include "Utils.h"
#include "LibraryLoader.h"
#include "Ball.h"

using namespace RKeyboard;
using namespace ChromaSDK::Keyboard;

#define STARTER_KEY 0x0403 //Z tuþu
#define NUMPAD_REPEAT_EFFECT 2

thread* warningThread;

APKeyboard& keyboard = *Game::getInstance()->getKeyboard();
Game& game = *Game::getInstance();

int main() {
	srand(time(NULL));
	memset(APKeyboard::getColorsKeyboard(), 0, KEYBOARD_LENGTH * sizeof(APKeyboard::getColorsKeyboard()[0])); //tuþlarýn renklerini sýfýrlama
	
	LibraryLoader razerSDKLoader;
	razerSDKLoader.init();

	bool isRight = false;
	bool isLeft = false;
	int starterKey = STARTER_KEY;

	int goLeftLights[5] = { 0x0314, 0x0313, 0x0312, 0x0212, 0x0412 };
	int goRightLights[5] = { 0x0312, 0x0313, 0x0314, 0x0214, 0x0414 };

	for (unsigned char i = 0; i < STICK_LENGTH; i++)
	{	
		game.getStick()[i] = starterKey;
		starterKey++;
	}

	game.initBall();

	keyboard.start();


	while (true)
	{
		if (GetAsyncKeyState(VK_LEFT) == -32767) { //sola bastý
			if (game.getStick()[STICK_LENGTH - 1] == 0x040E) keyboard.noRoadWarning(0, goRightLights);
			if (game.getStick()[0] == 0x0402) {
				if (!isLeft && !isRight)
				{
					warningThread = new thread(&APKeyboard::noRoadWarning, keyboard, NUMPAD_REPEAT_EFFECT, goRightLights);
					isLeft = true;
				}
				continue;
			}
			keyboard.removeStickRightLight(game.getStick()[STICK_LENGTH - 1]);
			for (int i = 0; i < STICK_LENGTH; i++) game.getStick()[i]--;

			if (game.getStick()[STICK_LENGTH - 1] == 0x040D) game.getStick()[STICK_LENGTH - 1] = 0x040C;
			isLeft = false;
		}
		else if (GetAsyncKeyState(VK_RIGHT) == -32767) { //saða bastý
			if (game.getStick()[0] == 0x0402) keyboard.noRoadWarning(0, goLeftLights);
			if (game.getStick()[STICK_LENGTH - 1] == 0x040E) {
				if (!isRight && !isLeft)
				{
					warningThread = new thread(&APKeyboard::noRoadWarning, keyboard, NUMPAD_REPEAT_EFFECT, goLeftLights);
					isRight = true;
				}
				continue;
			}
			keyboard.removeStickLeftLight(game.getStick()[0]);
			for (int i = 0; i < STICK_LENGTH; i++) game.getStick()[i]++;
			if (game.getStick()[STICK_LENGTH - 1] == 0x040D) game.getStick()[STICK_LENGTH - 1] = 0x040E;
			isRight = false;
		}
	}
}
