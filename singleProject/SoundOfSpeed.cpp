#include "stdafx.h"
#include "SoundOfSpeed.h"


SoundOfSpeed::SoundOfSpeed()
: m_soundLoopHandler("sfx/Slowmotion","_Start", "_Midt", "_Slutt")
, m_stateOfSound(CurrentSoundOfSpeed::off)
{
	SoundUpdater::addSound("SoundOfSpeed", this);
}


SoundOfSpeed::~SoundOfSpeed()
{
	SoundUpdater::removeSound("SoundOfSpeed");
}

void SoundOfSpeed::updateValue(const Ogre::Real& newSpeed)
{
	if (newSpeed > 0.75)
		m_stateOfSound = CurrentSoundOfSpeed::end;
	else
		m_stateOfSound = CurrentSoundOfSpeed::start;
}
void SoundOfSpeed::updateSound()
{
	switch (m_stateOfSound)
	{
	case CurrentSoundOfSpeed::off:
		break;
	case CurrentSoundOfSpeed::start:
		m_soundLoopHandler.begin();
		m_stateOfSound = CurrentSoundOfSpeed::mid;
		break;
	case CurrentSoundOfSpeed::mid:
		m_soundLoopHandler.loop();
		break;
	case CurrentSoundOfSpeed::end:
		m_soundLoopHandler.end(true);
        m_stateOfSound = CurrentSoundOfSpeed::off;
		break;
	default:
		break;
	}
}