#ifndef __MAINMENUSCREEN_H__
#define __MAINMENUSCREEN_H__

#include "Screen.h"
#include "GameObject.h"
#include<vector>

class MainMenuScreen : public Screen
{
public:
	MainMenuScreen(const SoundSystemClass * const a_pSounds);
	Screen* Update(const double a_dDeltaTime);
	void Draw();
private:
	GameObject *m_pMainFont;
	GLSLProgram *m_pFontShader;
};

#endif