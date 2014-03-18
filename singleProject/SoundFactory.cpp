#include "stdafx.h"
#include "SoundFactory.h"


template<> SoundFactory* Ogre::Singleton<SoundFactory>::msSingleton = 0;
SoundFactory::SoundFactory()
{
}


SoundFactory::~SoundFactory()
{
}


void SoundFactory::playMusic(std::string filename)
{
	if (!m_musics.count(filename))
		createNewMusic(filename);
    m_musics[filename]->play();
}

void SoundFactory::playSound(std::string filename, std::string soundID)
{
	prepareSound(filename, soundID);
	m_sounds[soundID]->play();
}
void SoundFactory::playSound3D(std::string filename, std::string soundID, Ogre::Node* positionalNode)
{
	prepareSound(filename, soundID);
	updateSoundPosition(soundID, positionalNode);
	m_sounds[soundID]->play();
}
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
	if (!m_buffers[filename]->loadFromFile(modifyPath(filename)))
		assert(0);
}
void SoundFactory::createNewMusic(std::string filename)
{
	m_musics[filename] = std::unique_ptr<sf::Music>(new sf::Music());
	if (!m_musics[filename]->openFromFile(modifyPath(filename)))
		assert(0);
}
void SoundFactory::prepareSound(std::string filename, std::string soundID)
{
	if (!m_buffers.count(filename))
		createNewBuffer(filename);
	if (!m_sounds.count(soundID))
		createNewSound(soundID);
	m_sounds[soundID]->setBuffer(*m_buffers[filename]);
}
std::string SoundFactory::modifyPath(std::string filename)
{
	return "../media/audio/"+filename;
}