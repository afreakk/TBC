#pragma once
#include "AudioHelpers.h"
enum class CurrentSoundOfSpeed
{
    off,
    start,
    mid,
    end,
};
class SoundOfSpeed : public BaseSound
{
public:
	SoundOfSpeed();
	~SoundOfSpeed();
	void updateValue(const Ogre::Real& newSpeed);
	void updateSound() override;
private:
	SoundLoopHandler m_soundLoopHandler;
	CurrentSoundOfSpeed m_stateOfSound;
};

