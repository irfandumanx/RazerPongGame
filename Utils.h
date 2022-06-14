#pragma once
#include "LibraryLoader.h"
#include "Color.h"
namespace ColorUtils {
	inline Color warnColor(255, 0, 0);
	inline Color noneColor(0, 0, 0);
	inline Color stickColor(255, 255, 255);
	inline Color orangeColor(230, 138, 0);
	inline Color ballColor(128, 0, 128);
	inline Color scoreColor(77, 195, 255);
	inline int getRGB(Color& color) { return ChromaAnimationAPI::GetRGB(color.getR(), color.getG(), color.getB()); }
}

namespace KeyboardUtils {
	inline int getRazerKeyValue(int key) { return 22 * HIBYTE(key) + LOBYTE(key); }
}