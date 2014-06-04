#include "stdafx.h"
#include "AudioHelpers.h"
#include "SoundFactory.h"

static std::string audioFileTypeEnding = ".ogg";

//---------------------Sound-Updater----------------------------
std::map<std::string, BaseSound*> SoundUpdater::ms_soundToUpdate;
void SoundUpdater::updateSound()
{
	for (auto& sound : ms_soundToUpdate)
		sound.second->updateSound();
}
void SoundUpdater::addSound(const std::string& id, BaseSound* instance)
{
	ms_soundToUpdate[id] = instance;
}
void SoundUpdater::removeSound(const std::string& id)
{
	ms_soundToUpdate.erase(id);
}

//-----------------------Audio-LOOP-----------------------------
AudioLoopHandler::AudioLoopHandler(const std::string& name, const std::string& introPrefix, const std::string& loopPrefix
	, const std::string& endPrefix)
: m_name(name)
, m_introPrefix(introPrefix)
, m_loopPrefix(loopPrefix)
, m_endPrefix(endPrefix)
{
}

//----------------------Sound-Loop---------------------------------
SoundLoopHandler::SoundLoopHandler(const std::string& name, const std::string& introPrefix, const std::string& loopPrefix
	, const std::string& endPrefix)
: AudioLoopHandler(name, introPrefix, loopPrefix, endPrefix)
, m_current(nullptr)
, m_endSound(nullptr)
, m_endPlayedOnce(false)
{
}
bool SoundLoopHandler::begin()
{
	std::string fileName = m_name + m_introPrefix + audioFileTypeEnding;
	m_current =     SoundFactory::getSingleton().playSound(fileName, fileName);
	m_endPlayedOnce = false;
	return true;
}
bool SoundLoopHandler::loop(bool force)
{
	assert(m_current && " MusicLoopHandler::begin() first");
	std::string fileName = m_name + m_loopPrefix + audioFileTypeEnding;
	if (m_current->getStatus() != sf::Music::Playing || force)
	{
		if (force)
			m_current->stop();
        m_current = SoundFactory::getSingleton().playSound(fileName, fileName);
		return true;
	}
	return false;
}
bool SoundLoopHandler::end(bool force)
{
	assert(m_current && " MusicLoopHandler::begin() first");
	std::string fileName = m_name + m_endPrefix + audioFileTypeEnding;
	if (m_current->getStatus() != sf::Music::Playing || force)
	{
		if (force)
			m_current->stop();
		if (!m_endPlayedOnce)
		{
            m_endSound = SoundFactory::getSingleton().playSound(fileName, fileName);
			m_endPlayedOnce = true;
		}
		return true;
	}
	return false;
}
//-----------------------MUSIC-LOOP-----------------------------
MusicLoopHandler::MusicLoopHandler(const std::string& name, const std::string& introPrefix, const std::string& loopPrefix
	, const std::string& endPrefix)
: AudioLoopHandler(name, introPrefix, loopPrefix, endPrefix)
, m_current(nullptr)
{
}
bool MusicLoopHandler::begin()
{
	m_current =     SoundFactory::getSingleton().playMusic(m_name + m_introPrefix + audioFileTypeEnding);
	return true;
}
bool MusicLoopHandler::loop(bool force)
{
	assert(m_current && " MusicLoopHandler::begin() first");
	if (m_current->getStatus() != sf::Music::Playing || force)
	{
		if (force)
			m_current->stop();
        m_current = SoundFactory::getSingleton().playMusic(m_name + m_loopPrefix + audioFileTypeEnding);
		return true;
	}
	return false;
}
bool MusicLoopHandler::end(bool force)
{
	assert(m_current && " MusicLoopHandler::begin() first");
	if (m_current->getStatus() != sf::Music::Playing || force)
	{
		if (force)
			m_current->stop();
        m_current = SoundFactory::getSingleton().playMusic(m_name + m_endPrefix + audioFileTypeEnding);
		return true;
	}
	return false;
}
//-----------------------FOOTSTEPZ-----------------------------
#include "LevelManager.h"
#include "MainUpdate.h"
std::string Skritt::ms_prefix = "sfx/walk/";
Skritt::Skritt(Ogre::Node* parentNode)
: m_parentNode(parentNode)
{
	for (unsigned i = 0; i < 2; i++)
		m_walkOutdoor.push_back(ms_prefix+"skritt_" + std::to_string(i) + audioFileTypeEnding);
	for (unsigned i = 0; i < 4; i++)
		m_walkMetal.push_back(  ms_prefix+"skrittMetal_" + std::to_string(i) + audioFileTypeEnding);
}
void Skritt::playSkritt()
{
	bool metal = (MainUpdate::getSingleton().getLevelID() == LevelID::LEVEL_ONE);
	const std::string& stepSound = metal ? m_walkMetal[getRandMetalIndex()] : m_walkOutdoor[getRandOutdoorIndex()];
    m_sound = SoundFactory::getSingleton().getSingleton().playSound3D(stepSound, stepSound, m_parentNode);
	m_sound->setVolume(20.f);
}
unsigned Skritt::getRandOutdoorIndex()
{
	return rand() % m_walkOutdoor.size();
}
unsigned Skritt::getRandMetalIndex()
{
	return rand() % m_walkMetal.size();
}