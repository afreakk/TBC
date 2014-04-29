
#include "stdafx.h"
#include "LvlTwoEnvironment.h"
#include "OgreCore.h"

LvlTwoEnvironment::LvlTwoEnvironment()
{
	OgreCore::getSingleton().getSceneMgr()->setSkyBox(true, "skytrippy");
	initSnow();
	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	auto dirLight = sMgr->createLight("DirectionalLight");
	dirLight->setType(Ogre::Light::LT_DIRECTIONAL);
	dirLight->setDiffuseColour(Ogre::ColourValue(.5f, .5f, .5f));
	dirLight->setSpecularColour(Ogre::ColourValue(.95f, .5f, .5f));
	dirLight->setDirection(Ogre::Vector3(-1.0f, -1.0f, -0.0f));
}


LvlTwoEnvironment::~LvlTwoEnvironment()
{
}

void LvlTwoEnvironment::initSnow()
{
/*	m_snowParticles = unique_ptr<SnowInstance>(new SnowInstance());
	for (Real i = 0.0; i < 3.14f*2.0f; i += 0.2f)
	{
		m_snowRenderers.push_back( unique_ptr<WeatherSnow>( new WeatherSnow(i, 0.2f) ) );
	}*/
}

void LvlTwoEnvironment::update()
{
	/*for (auto& i : m_snowRenderers)
		i->snowCulling();
	if (m_snowParticles)
	    m_snowParticles->update();*/
}