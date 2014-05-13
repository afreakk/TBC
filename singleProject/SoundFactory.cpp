#include "stdafx.h"
#include "SoundFactory.h"
#include "OgreCore.h"


template<> SoundFactory* Ogre::Singleton<SoundFactory>::msSingleton = 0;
SoundFactory::SoundFactory()
: m_musicMuted(false)
{
}


SoundFactory::~SoundFactory()
{
}


void SoundFactory::resetAllSound()
{
	for (auto& music : m_musics)
		music.second.reset();
	m_musics.clear();
	for (auto& buffer : m_buffers)
		buffer.second.reset();
	m_buffers.clear();
	for (auto& sound : m_sounds)
		sound.second.reset();
	m_sounds.clear();

    //reset the fuck out of the sound 
}
void SoundFactory::muteMusic(bool mute)
{
	m_musicMuted = mute;
	if (!m_musicMuted)
	{
		for (auto& m : m_musics)
			m.second->setVolume(100);
	}
	else
	{
		for (auto& m : m_musics)
			m.second->setVolume(0);
	}
}
bool SoundFactory::isMusicMuted()
{
	return m_musicMuted;
}
sf::Music* SoundFactory::playMusic(std::string filename)
{
	if (!m_musics.count(filename))
		createNewMusic(filename);
	m_musics[filename]->play();
	if (m_musicMuted)
	    m_musics[filename]->setVolume(0);
	return m_musics[filename].get();
}

sf::Sound* SoundFactory::playSound(std::string filename, std::string soundID)
{
	prepareSound(filename, soundID);
	m_sounds[soundID]->play();
	return m_sounds[soundID].get();
}
sf::Sound* SoundFactory::playSound3D(std::string filename, std::string soundID, Ogre::Node* positionalNode)
{
	prepareSound(filename, soundID);
	updateSoundPosition(soundID, positionalNode);
	m_sounds[soundID]->play();
	return m_sounds[soundID].get();
}
// --- priv
void SoundFactory::updateSoundPosition(std::string soundID, Ogre::Node* positionalNode)
{
	m_sounds[soundID]->setPosition(positionalNode->getPosition().x,positionalNode->getPosition().y, positionalNode->getPosition().z);
}
void SoundFactory::createNewSound(std::string filename)
{
	m_sounds[filename] = std::unique_ptr<sf::Sound>(new sf::Sound());
}
void SoundFactory::createNewBuffer(std::string filename)
{
	m_buffers[filename] =std::unique_ptr<sf::SoundBuffer>(new  sf::SoundBuffer());
	if (!m_buffers[filename]->loadFromFile(fullPath(filename)))
		assert(0);
}
void SoundFactory::createNewMusic(std::string filename)
{
	m_musics[filename] = std::unique_ptr<sf::Music>(new sf::Music());
	if (!m_musics[filename]->openFromFile(fullPath(filename)))
		assert(0);
}
void SoundFactory::prepareSound(std::string filename, std::string soundID)
{
	if (!m_buffers.count(filename))
		createNewBuffer(filename);
	if (!m_sounds.count(soundID))
		createNewSound(soundID);
	if(m_sounds[soundID]->getBuffer() != m_buffers[filename].get())
	    m_sounds[soundID]->setBuffer(*m_buffers[filename]);
}
std::string SoundFactory::fullPath(std::string filename)
{
	return "../media/audio/"+filename;
}
void SoundFactory::update()
{
	auto& cPos = OgreCore::getSingleton().getCamera()->getPosition();
	auto& cDir = OgreCore::getSingleton().getCamera()->getDirection();
	sf::Listener::setPosition(cPos.x, cPos.y, cPos.z);
	sf::Listener::setDirection(cDir.x, cDir.y, cDir.z);
}
