#include "stdafx.h"
#include "LightHandler.h"
#include "../OgreCore/OgreCore.h"

LightHandler::LightHandler()
{
	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	sMgr->setAmbientLight(Ogre::ColourValue(0.1f, 0.01f, 0.01f, 1.0f));

	Ogre::Light* directionalLight = sMgr->createLight("DirectionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, .25));
	directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, .25));
	directionalLight->setDirection(Ogre::Vector3(-1, -1, -1));

}


LightHandler::~LightHandler()
{
}
