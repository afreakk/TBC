#include "stdafx.h"
#include "LightHandler.h"
#include "OgreCore.h"
#include "MainUpdate.h"

LightHandler::LightHandler()
: time(0.0)
{

	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	directionalLight = sMgr->createLight("DirectionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(Ogre::ColourValue(.95, .95, .95));
	directionalLight->setSpecularColour(Ogre::ColourValue(.95, .95, .95));
	directionalLight->setDirection(Ogre::Vector3(-0.5, -0.5, -0.5));




}
void LightHandler::update()
{
}

LightHandler::~LightHandler()
{
	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	sMgr->destroyLight(directionalLight);
}
