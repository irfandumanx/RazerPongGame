#include "APKeyboard.h"


APKeyboard::APKeyboard(Game* gameInstance) {
	this->instance = gameInstance;
}

void APKeyboard::showScoreWithKeyboardKeys(int score) {
	short tempScore = score;
	unsigned char index = 0;
	unsigned char bit;
	Color color(0, 0, 0);
	while (tempScore)
	{
		bit = tempScore & 1;
		if (bit == 1) color.changeColor(77, 195, 255);
		else color.changeColor(0, 0, 0);;

		tempScore >>= 1;
		setKeyboardRGB(scoreKeys, index, color);
		index++;
	}
}

void APKeyboard::keyboardAnimation() {
	while (true)
	{
		if (!instance->isFinish())
		{
			for (int i = 0; i < STICK_LENGTH; i++)
			{
				int key = instance->getStick()[i];
				colorsKeyboard()[KeyboardUtils::getRazerKeyValue(key)] = ColorUtils::getRGB(ColorUtils::stickColor);
			}
		}
		ChromaAnimationAPI::SetCustomColorFlag2D((int)EChromaSDKDevice2DEnum::DE_Keyboard, colorsKeyboard());
		ChromaAnimationAPI::SetEffectKeyboardCustom2D((int)EChromaSDKDevice2DEnum::DE_Keyboard, colorsKeyboard());
	}
}

void APKeyboard::clearNumpad(int* array) {
	short size = sizeof(array) / array[0];
	for (int i = 0; i < size; i++)
	{
		int razerKey = KeyboardUtils::getRazerKeyValue(array[i]);
		colorsKeyboard()[razerKey] = ColorUtils::getRGB(ColorUtils::noneColor);
	}
}

void APKeyboard::noRoadWarning(int repeat, int* array) {
	if (repeat == 0) {
		clearNumpad(array);
		return;
	}
	else {
		for (int i = 0; i < 5; i++)
		{
			int razerKey = KeyboardUtils::getRazerKeyValue(array[i]);
			colorsKeyboard()[razerKey] = ColorUtils::getRGB(ColorUtils::warnColor);
			Sleep(125);
		}
		Sleep(150);
		for (int i = 0; i < 5; i++)
		{
			int razerKey = KeyboardUtils::getRazerKeyValue(array[i]);
			colorsKeyboard()[razerKey] = ColorUtils::getRGB(ColorUtils::noneColor);
			Sleep(50);
		}
		return noRoadWarning(repeat - 1, array);
	}
}
void APKeyboard::removeStickRightLight(int key) {
	colorsKeyboard()[KeyboardUtils::getRazerKeyValue(key)] = ColorUtils::getRGB(ColorUtils::noneColor);
}

void APKeyboard::removeStickLeftLight(int key) {
	colorsKeyboard()[KeyboardUtils::getRazerKeyValue(key)] = ColorUtils::getRGB(ColorUtils::noneColor);
}

void APKeyboard::showFinishKeyboardEffect() {
	int willEffectKeys[] = { RZKEY::RZKEY_ESC, RZKEY::RZKEY_OEM_1, RZKEY::RZKEY_TAB, RZKEY::RZKEY_CAPSLOCK, RZKEY::RZKEY_LSHIFT, RZKEY::RZKEY_LCTRL };
	unsigned char size = sizeof(willEffectKeys) / sizeof(willEffectKeys[0]);
	memset(instance->getStick(), 0, STICK_LENGTH * sizeof(instance->getStick()[0])); //tuþlarýn renklerini sýfýrlama
	memset(colorsKeyboard(), 0, KEYBOARD_LENGTH * sizeof(colorsKeyboard()[0])); //tuþlarýn renklerini sýfýrlama

	while (true) {
		for (unsigned char i = 0; i < size; i++)
		{
			colorsKeyboard()[KeyboardUtils::getRazerKeyValue(willEffectKeys[i])] = ColorUtils::getRGB(ColorUtils::orangeColor);
		}
		Sleep(75);
		for (unsigned char i = 0; i < size; i++)
		{
			colorsKeyboard()[KeyboardUtils::getRazerKeyValue(willEffectKeys[i])] = ColorUtils::getRGB(ColorUtils::noneColor);
			willEffectKeys[i]++;
		}
		if (willEffectKeys[1] == (RZKEY::RZKEY_NUMPAD_SUBTRACT + 1)) break;
	}

	Sleep(150);

	while (true) {
		for (unsigned char i = 0; i < size; i++)
		{
			colorsKeyboard()[KeyboardUtils::getRazerKeyValue(willEffectKeys[i])] = ColorUtils::getRGB(ColorUtils::orangeColor);
		}
		Sleep(75);
		for (unsigned char i = 0; i < size; i++)
		{
			colorsKeyboard()[KeyboardUtils::getRazerKeyValue(willEffectKeys[i])] = ColorUtils::getRGB(ColorUtils::noneColor);
			willEffectKeys[i]--;
		}

		if (willEffectKeys[1] == (RZKEY::RZKEY_OEM_1 - 1)) break;
	}
}