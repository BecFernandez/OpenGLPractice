#pragma once

#include "Screen.h"
#include "Text.h"

class LoseScreen : public Screen
{
public:
	LoseScreen(SoundSystemClass* a_pSounds, GLSLProgram *a_pShaders);
	Screen* Update(const double a_dDeltaTime);
	void Draw();

private:
	Sprite m_loseImage;
	Text m_loseText;
};