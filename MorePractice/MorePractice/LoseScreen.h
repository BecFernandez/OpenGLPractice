#pragma once

#include "Screen.h"

class LoseScreen : public Screen
{
public:
	LoseScreen(const SoundSystemClass* const a_pSounds);
	Screen* Update(const double a_dDeltaTime);
	void Draw();

private:
	GameObject *m_pMainFont;
};