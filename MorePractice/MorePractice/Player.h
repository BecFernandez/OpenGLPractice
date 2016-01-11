#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Sprite.h"
#include <vector>
#include "Bullet.h"
#include "SoundSystemClass.h"

class Player : public Sprite
{
private:
	//player should only move forward and rotate
	float m_fSpeed;
	std::vector<Bullet*> *m_pBullets;
	float m_fFireCoolDown;
	float m_fPower;
	FMOD::Sound *m_pLaser;

public:
	Player(const float a_fPower, const glm::vec3 a_position, const glm::vec4 a_colour, const unsigned int a_uiWidth, const unsigned int a_uiHeight,
		const char *a_szTexName, std::vector<Bullet*> *a_pBullets, SoundSystemClass a_sounds);
	void Update(const double a_dDeltaTime, SoundSystemClass a_sounds);
	void Draw(const GLuint VBO, const GLuint IBO, GLSLProgram *shader) const;
	float GetPower() const { return m_fPower; }
};

#endif