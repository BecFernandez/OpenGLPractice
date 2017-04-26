#pragma once

#include "Screen.h"
#include "Text.h"

class LoseScreen : public Screen
{
public:
	LoseScreen(const SoundSystemClass* const a_pSounds, const GLSLProgram * const a_pShaders);
	Screen* Update(const double a_dDeltaTime);
	void Draw();

private:
	//Text m_loseText;
};