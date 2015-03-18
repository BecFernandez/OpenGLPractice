#ifndef __MAINMENUSCREEN_H__
#define __MAINMENUSCREEN_H__

#include "Screen.h"

class MainMenuScreen : public Screen
{
public:
	MainMenuScreen();
	MainMenuScreen(SoundSystemClass *a_pSounds, GLSLProgram *a_pShaders);
	Screen* Update(const double a_dDeltaTime);
	void Draw() const;
private:
	Sprite m_gameTitle;
};

#endif