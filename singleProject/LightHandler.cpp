#include "stdafx.h"
#include "LightHandler.h"
#include "OgreCore.h"
#include "MainUpdate.h"
#include "UnitCircleMovement.h"
#include "LaneSettings.h"
LightHandler::LightHandler()
: time(0.0)
, m_dirLight(nullptr)
{
	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	m_dirLight = sMgr->createLight("DirectionalLight");
	m_dirLight->setType(Ogre::Light::LT_DIRECTIONAL);
	m_dirLight->setDiffuseColour(Ogre::ColourValue(.95f, .95f, .95f));
	m_dirLight->setSpecularColour(Ogre::ColourValue(.95f, .95f, .95f));
	m_dirLight->setDirection(Ogre::Vector3(-0.9f, -0.9f, -0.0f));
	m_dirLight->setCastShadows(true);
}

LightHandler::~LightHandler()
{
	OgreCore::getSingleton().getSceneMgr()->destroyLight(m_dirLight);
}

void LightHandler::update()
{
}

//-------------------------------------------------\

LightHandlerTwo::LightHandlerTwo()
: time(0.0)
, m_dirLight(nullptr)
{
	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	m_dirLight = sMgr->createLight("DirectionalLight");
	m_dirLight->setType(Ogre::Light::LT_DIRECTIONAL);
	m_dirLight->setDiffuseColour(Ogre::ColourValue(.95f, .95f, .95f));
	m_dirLight->setSpecularColour(Ogre::ColourValue(.95f, .95f, .95f));
	m_dirLight->setDirection(Ogre::Vector3(-0.5f, -0.5f, -0.0f));
	m_dirLight->setCastShadows(true);
}
LightHandlerTwo::~LightHandlerTwo()
{
	OgreCore::getSingleton().getSceneMgr()->destroyLight(m_dirLight);
}
void LightHandlerTwo::update()
{

}