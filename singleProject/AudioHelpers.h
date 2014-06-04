#pragma once
namespace sf
{
	class Music;
	class Sound;
}
//-----------------------Generic-Sound-Abstrac---------------
class BaseSound
{
public:
	virtual ~BaseSound(){}
	virtual void updateSound() = 0;
};
//-----------------------Sound-Updater-----------------------
class SoundUpdater
{
public:
	static void updateSound();
	static void addSound(const std::string& id, BaseSound* instance);
	static void removeSound(const std::string& id);
	static std::map<std::string, BaseSound*> ms_soundToUpdate;
};
//-----------------------Loop-Handler-------------------------
class AudioLoopHandler
{
public:
	AudioLoopHandler(const std::string& name, const std::string& introPrefix, const std::string& loopPrefix
	, const std::string& endPrefix);
	virtual bool begin() = 0;
	virtual bool loop(bool force) = 0;
	virtual bool end(bool force) = 0;
protected:
	std::string m_name;
	std::string m_introPrefix;
	std::string m_loopPrefix;
	std::string m_endPrefix;
};
//-----------------------MUSIC-LOOP-----------------------------
class MusicLoopHandler : public AudioLoopHandler
{
public:
	MusicLoopHandler(const std::string& name, const std::string& introPrefix, const std::string& loopPrefix
	, const std::string& endPrefix);
	bool begin() override;
	bool loop(bool force=false) override;
	bool end(bool force=false) override;
private:
	sf::Music* m_current;
};
//-----------------------AUDIO-LOOP-----------------------------
class SoundLoopHandler : public AudioLoopHandler
{
public:
	SoundLoopHandler(const std::string& name, const std::string& introPrefix, const std::string& loopPrefix
	, const std::string& endPrefix);
	bool begin() override;
	bool loop(bool force=false) override;
	bool end(bool force=false) override;
private:
	sf::Sound* m_current;
	sf::Sound* m_endSound;
	bool m_endPlayedOnce;
};
//-----------------------FOOTSTEPZ-----------------------------
class Skritt
{
public:
	Skritt(Ogre::Node* parentNode);
	void playSkritt();
private:
	sf::Sound* m_sound;
	Ogre::Node* m_parentNode;
	std::vector<std::string> m_walkOutdoor;
	std::vector<std::string> m_walkMetal;
	static std::string ms_prefix;

	unsigned getRandOutdoorIndex();
	unsigned getRandMetalIndex();
};