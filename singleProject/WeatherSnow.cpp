#include "stdafx.h"
#include "WeatherSnow.h"
#include "OgreCore.h"
#include "Player.h"
#include "PlayerContainer.h"
#include "LaneSettings.h"

WeatherSnow::WeatherSnow() 
: ParticleEffect(OgreCore::getSingleton().getSceneMgr()->getRootSceneNode(), 0, "snowWeather", "snow", OgreCore::getSingleton().getSceneMgr())
, m_height(0.0f)
{
}


WeatherSnow::~WeatherSnow()
{
}

void WeatherSnow::update()
{ 
	Vector3 snowPos = LaneSettings::getSingleton().getVectorOf(1, PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates().theta, m_height);
	m_node->setPosition(snowPos);
	ParticleEffect::update();
}