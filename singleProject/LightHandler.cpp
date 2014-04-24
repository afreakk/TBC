#include "stdafx.h"
#include "LightHandler.h"
#include "OgreCore.h"
#include "MainUpdate.h"
#include "UnitCircleMovement.h"
#include "LaneSettings.h"
LightHandler::LightHandler()
: time(0.0)
{

	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	auto directionalLight = sMgr->createLight("DirectionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(Ogre::ColourValue(.5f, .5f, .5f));
	directionalLight->setSpecularColour(Ogre::ColourValue(.95f, .5f, .5f));
	directionalLight->setDirection(Ogre::Vector3(-0.0f, -1.0f, -0.0f));

/*-	for (Real i = 0.0f; i < Math::PI*2.0f; i+= 1.5f)
	{
		m_roofLigths.push_back(sMgr->createLight());
		m_roofLigths.back()->setType(Light::LT_POINT);
		m_roofLigths.back()->setDirection(0.0f, -100.0f, 0.0f);
		m_roofLigths.back()->setDiffuseColour(Ogre::ColourValue(.5f, .5f, .5f));
		m_roofLigths.back()->setSpecularColour(Ogre::ColourValue(.5f, .5f, .5f));
		m_roofLigths.back()->setPowerScale(1.0f);
		auto pos = UnitCircleMovement::VectorFromPolar(PolarCoordinates(i, LaneSettings::getSingleton().getLane(1), 500.0f));
		m_roofLigths.back()->setPosition(pos);
	}
    */


}
void LightHandler::update()
{
}

LightHandler::~LightHandler()
{
	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	//sMgr->destroyLight(directionalLight);
}
