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
	directionalLight->setDiffuseColour(Ogre::ColourValue(.5f, .5f, .5f));
	directionalLight->setSpecularColour(Ogre::ColourValue(.95f, .5f, .5f));
	directionalLight->setDirection(Ogre::Vector3(-0.5f, -0.5f, -0.5f));




}
void LightHandler::update()
{
}

LightHandler::~LightHandler()
{
	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	sMgr->destroyLight(directionalLight);
}
