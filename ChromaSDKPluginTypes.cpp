#include "Chroma/include/ChromaSDKPluginTypes.h"

using namespace ChromaSDK;

FChromaSDKColorFrame1D::FChromaSDKColorFrame1D()
{
	Duration = 1.0f;
}

FChromaSDKColorFrame2D::FChromaSDKColorFrame2D()
{
	Duration = 1.0f;
}

void FChromaSDKScene::ToggleState(unsigned int effect)
{
	if (effect >= 0 && effect < _mEffects.size())
	{
		_mEffects[effect]._mState = !_mEffects[effect]._mState;
	}
}
