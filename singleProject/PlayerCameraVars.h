#pragma once
#include "OgreSingleton.h"
struct PlayerCameraNormalVars
{
	Ogre::Real distance;
	Ogre::Real height;
	PlayerCameraNormalVars()
		:distance(0)
		, height(0)
	{}
};
struct PlayerCameraLERPVars
{
	Ogre::Real distance;
	Ogre::Real height;
	Ogre::Real spinSpeed;
};
class PlayerCameraVars : public Ogre::Singleton<PlayerCameraVars>
{
public:
	PlayerCameraVars();
	~PlayerCameraVars();
	PlayerCameraNormalVars getPlayerCameraNormal()
	{
		return m_playerCameraNormal;
	}
	PlayerCameraLERPVars getPlayerCameraLERP()
	{
		return m_playerCameraLerp;
	}
private:
	void parseScript();
	PlayerCameraNormalVars m_playerCameraNormal;
	PlayerCameraLERPVars m_playerCameraLerp;
};

