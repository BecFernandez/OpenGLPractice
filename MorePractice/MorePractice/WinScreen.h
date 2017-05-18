#pragma once
#include "Screen.h"

class WinScreen : public Screen
{
public:
	WinScreen(const SoundSystemClass * const a_pSounds);
	Screen* Update(double a_dDeltaTime);
	void Draw();

private:
	GameObject *m_pMainFont;
};