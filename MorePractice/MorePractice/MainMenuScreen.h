#ifndef __MAINMENUSCREEN_H__
#define __MAINMENUSCREEN_H__

#include "Screen.h"
//#include "Text.h"
#include "GameObject.h"
#include<vector>
#include "ComponentPoolHelper.h"

class MainMenuScreen : public Screen
{
public:
	MainMenuScreen(SoundSystemClass *a_pSounds, GLSLProgram *a_pShaders);
	Screen* Update(const double a_dDeltaTime);
	void Draw();
private:
	//Sprite m_gameTitle;
	//Text m_t;
	std::vector<GameObject*> m_gameObjects;

	ComponentPoolHelper m_componentPoolHelper;
};

#endif