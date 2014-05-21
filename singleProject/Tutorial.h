#pragma once
#include "AudioHelpers.h"
#include "TutorialEnums.h"
class Player;
class ModelHandler;
class Tutorial
{
public:
	Tutorial();
	~Tutorial();
	void update();
	bool canSpawn();
	bool plzChangeLevel();
	static TutorialScript getTooltipIdx();
	static void setTooltipIdx(TutorialScript newIdx);
private:
	Player* m_player;
	static TutorialScript m_tooltipIdx;
	bool m_enterReleased;
	bool m_compositorOn;
	std::string m_currentMsg;
	Ogre::Real m_pauseTimer;
	int m_mutantSize;
	bool m_canSpawn;
	bool m_changeLevel;
	IntroLoopListener m_music;
	OIS::KeyCode m_keyToClick;

	void showTooltipSlowMotion(ModelHandler& model,const  std::string& msg);
	void showTooltipNormie(ModelHandler& model,const  std::string& msg);
	void hideTooltip(ModelHandler& model);
	void enterPressed();
	void setCompositor(bool enabled);
	void setSlowmotion(bool slowMotion);

	bool pauseTimer(Ogre::Real time=2.0f);
	bool mutantSpawned();
	bool mutantDied();
	bool mutantIsClose();
	bool allKilled();

	void genericPress(TutorialScript changeTo, OIS::KeyCode keyCode = OIS::KeyCode::KC_RETURN);
};

