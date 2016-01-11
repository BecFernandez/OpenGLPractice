#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include <fmod.hpp>
#include <fmod_errors.h>


//TODO - make this a singleton!
class SoundSystemClass
{
	FMOD::System *m_pSystem;
public:
	SoundSystemClass();
	void createSound(FMOD::Sound **a_pSound, const char* a_pFile);
	void playSound(FMOD::Sound *a_pSound, bool a_bLoop);
	void releaseSound(FMOD::Sound *a_pSound);
};

#endif