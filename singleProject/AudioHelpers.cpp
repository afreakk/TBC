#include "stdafx.h"
#include "AudioHelpers.h"
#include "SoundFactory.h"
bool MuteIntroLoop = false;
IntroLoopListener::IntroLoopListener(const std::string& name)
: m_name(name)
, m_pIntro("_intro.ogg")
, m_pLoop("_loop.ogg")
, m_current(SoundFactory::getSingleton().playMusic(m_name+m_pIntro))
{
}
void IntroLoopListener::update()
{
    if (m_current->getStatus() != sf::Music::Playing)
        m_current = SoundFactory::getSingleton().playMusic(m_name + m_pLoop);
}


Skritt::Skritt(Ogre::Node* parentNode)
: m_parentNode(parentNode)
{
	for (int i = 0; i < 6; i++)
		m_walkNames.push_back("sfx/skritt_" + std::to_string(i) + ".ogg");
}

void Skritt::playSkritt()
{
    increment();
    m_sound = SoundFactory::getSingleton().getSingleton().playSound3D(m_walkNames[m_soundIdx],m_walkNames[m_soundIdx], m_parentNode);
	m_sound->setVolume(50.f);
}
void Skritt::increment()
{
	m_soundIdx = rand() % m_walkNames.size();
}