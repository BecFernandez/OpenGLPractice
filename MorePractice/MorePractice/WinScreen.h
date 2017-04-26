#pragma once
#include "Screen.h"
#include "Text.h"

class WinScreen : public Screen
{
public:
	WinScreen(const SoundSystemClass * const a_pSounds, const GLSLProgram * const a_pShaders);
	Screen* Update(double a_dDeltaTime);
	void Draw();

private:
	//Text m_winText;
};