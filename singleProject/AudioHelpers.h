#pragma once
namespace sf
{
	class Music;
	class Sound;
}
class IntroLoopListener
{
public:
	IntroLoopListener(const std::string& name);
	void update();
private:
	std::string m_name;
	std::string m_pIntro;
	std::string m_pLoop;
	sf::Music* m_current;
};
class Skritt
{
public:
	Skritt(Ogre::Node* parentNode);
	void playSkritt();
private:
	void increment();

	sf::Sound* m_sound;
	Ogre::Node* m_parentNode;
	std::vector<std::string> m_walkNames;
	unsigned m_soundIdx;
};