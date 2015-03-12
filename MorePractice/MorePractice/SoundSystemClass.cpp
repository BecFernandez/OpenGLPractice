#include "SoundSystemClass.h"

SoundSystemClass::SoundSystemClass()
{
	//creating up the fmod system, I assume
	if(FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		return;
	}

	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);

	//if there are no audio drivers then exit
	if(driverCount == 0)
	{
		return;
	}

	//initialising fmod with 36 channels
	//apparently each channel holds ONE sound
	m_pSystem->init(36, FMOD_INIT_NORMAL, 0);
}

void SoundSystemClass::createSound(FMOD::Sound **a_pSound, const char * a_pFile)
{
	//this might need to be updated = followed tut from older fmod version
	m_pSystem->createSound(a_pFile, FMOD_DEFAULT, 0, a_pSound);
}

void SoundSystemClass::playSound(FMOD::Sound *a_pSound, bool a_bLoop = false)
{
	if(!a_bLoop)
	{
		a_pSound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		a_pSound->setMode(FMOD_LOOP_NORMAL);
		//using -1 apparently means unlimited looping
		a_pSound->setLoopCount(-1);
	}

	m_pSystem->playSound(a_pSound, 0, false, 0);
}

void SoundSystemClass::releaseSound(FMOD::Sound *a_pSound)
{
	a_pSound->release();
}