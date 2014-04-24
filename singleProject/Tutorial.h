#pragma once
class Player;
class ModelHandler;
enum class TutorialScript
{
	even_one,
	even_two,
	even_three,
	mov_even_one,
	tutorial_pause_one,
	tumble_even,
	tutorial_pause_two,
	tutorial_pause_two_pt_two,
	even_attack_one,
	even_attack_two,
	even_attack_three,
	even_attack_four,
	pauseKillMutant,
	even_feels_energy,
	even_feels_two,
	even_teleport,
	even_teleport_two,
	even_teleport_actual,
	even_teleportBreak,
	even_fireballWait,
    even_fireball_one,
    even_fireball_two,
    even_fireball_three,
    even_fireball_four,
    even_fireball_five,
    even_fireball_waitForKill,
    even_fireball_end,
    even_fireball_end_pt_two,
    even_fireball_end_pt_three,
    even_frostbolt_wait_root,
    even_frostbolt_one,
    even_frostbolt_two,
    even_frostbolt_killListen,
    even_frostbolt_wait_two,
    even_frostbolt_end,
    suicide_listen,
    suicide_wait,
    suicide_one,
    suicide_two,
    suicide_three,
    suicide_four,
    suicide_listen_two,
    suicide_five,
    suicide_six,
    slowmo_one,
};
class Tutorial
{
public:
	Tutorial();
	~Tutorial();
	void update();
	bool canSpawn();
private:
	Player* m_player;
	TutorialScript m_tooltipIdx;
	bool m_enterReleased;
	bool m_compositorOn;
	std::string m_currentMsg;
	Ogre::Real m_pauseTimer;
	int m_mutantSize;
	bool m_canSpawn;

	void showTooltipSlowMotion(ModelHandler& model,const  std::string& msg);
	void showTooltipNormie(ModelHandler& model,const  std::string& msg);
	void hideTooltip(ModelHandler& model);
	void enterPressed();
	void setCompositor(bool enabled);
	void setSlowmotion(bool slowMotion);

	bool pauseTimer();
	bool mutantSpawned();
	bool mutantDied();
	bool mutantIsClose();

	void genericPress(TutorialScript changeTo, OIS::KeyCode keyCode = OIS::KeyCode::KC_RETURN);
};

