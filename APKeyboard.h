#pragma once
#include <iostream>
#include "Color.h"
#include <thread>
#include "Utils.h"
#include "Game.h"
#define KEYBOARD_LENGTH 132

using namespace std;
using namespace ChromaSDK::Keyboard;

class APKeyboard {
private: 
    class Game* instance;
    class thread* threadOfAnimation;
    const int scoreKeys[9] = { RZKEY::RZKEY_PAGEDOWN, RZKEY::RZKEY_END, RZKEY::RZKEY_DELETE, RZKEY::RZKEY_PAGEUP, RZKEY::RZKEY_HOME, RZKEY::RZKEY_INSERT, RZKEY::RZKEY_PAUSE, RZKEY::RZKEY_SCROLL, RZKEY::RZKEY_PRINTSCREEN };
    static int* colorsKeyboard()
    {
        static int* colorsInKeyboard = new int[KEYBOARD_LENGTH];
        return colorsInKeyboard;
    }
public:
    APKeyboard& operator=(const APKeyboard& other) { return *this; };
    APKeyboard(Game* gameInstance);
    ~APKeyboard() { }
	static int* getColorsKeyboard() { return colorsKeyboard(); }
    void setKeyboardRGB(const int* array, int index, Color color) { colorsKeyboard()[KeyboardUtils::getRazerKeyValue(array[index])] = ColorUtils::getRGB(color); }
    void showScoreWithKeyboardKeys(int score);
	void keyboardAnimation();
    void start() { this->threadOfAnimation = new thread(&APKeyboard::keyboardAnimation, this); }
    void clearNumpad(int* array);
    void noRoadWarning(int repeat, int* array);
    void removeStickRightLight(int key);
    void removeStickLeftLight(int key);
    void showFinishKeyboardEffect();
};