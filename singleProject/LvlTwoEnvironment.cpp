
#include "stdafx.h"
#include "LvlTwoEnvironment.h"
#include "OgreCore.h"

LvlTwoEnvironment::LvlTwoEnvironment()
{
	OgreCore::getSingleton().getSceneMgr()->setSkyBox(true, "skytrippy");
	initSnow();
}


LvlTwoEnvironment::~LvlTwoEnvironment()
{
}

void LvlTwoEnvironment::initSnow()
{
	m_snowParticles = unique_ptr<SnowInstance>(new SnowInstance());
	for (Real i = 0.0; i < 3.14f*2.0f; i += 0.2f)
	{
		m_snowRenderers.push_back( unique_ptr<WeatherSnow>( new WeatherSnow(i, 0.2f) ) );
	}
}

void LvlTwoEnvironment::update()
{
	m_lightHandler.update();
	for (auto& i : m_snowRenderers)
		i->snowCulling();
	if (m_snowParticles)
	    m_snowParticles->update();
}