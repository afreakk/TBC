#pragma once

#include <SFML/Audio.hpp>

class SoundFactory : public Ogre::Singleton<SoundFactory>
{
public:
	SoundFactory();
	~SoundFactory();
	sf::Music* playMusic(std::string);
	sf::Sound* playSound(std::string filename, std::string soundID);
	sf::Sound* playSound3D(std::string filename, std::string soundID, Ogre::Node* positionalNode);
	void muteMusic(bool mute);
	bool isMusicMuted();
	void update();
	void resetAllSound();
private:
	std::map<std::string, std::unique_ptr<sf::Music>> m_musics;
	std::map<std::string, std::unique_ptr<sf::SoundBuffer>> m_buffers;
	std::map<std::string, std::unique_ptr<sf::Sound>> m_sounds;

    void createNewMusic(std::string);
	void createNewBuffer(std::string);
	void createNewSound(std::string);

	void prepareSound(std::string, std::string);
	void updateSoundPosition(std::string, Ogre::Node* positionalNode);
	std::string fullPath(std::string filename);

	bool m_musicMuted;
};

