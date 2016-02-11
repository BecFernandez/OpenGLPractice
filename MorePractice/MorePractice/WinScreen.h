#pragma once
#include "Screen.h"
#include "Text.h"

class WinScreen : public Screen
{
public:
	WinScreen(SoundSystemClass *a_pSounds, GLSLProgram *a_pShaders);
	Screen* Update(double a_dDeltaTime);
	void Draw();

private:
	Sprite m_winImage;
	Text m_winText;
};