#include "stdafx.h"
#include "LvlOneEnvironment.h"
#include "OgreCore.h"

LvlOneEnvironment::LvlOneEnvironment()
{
	OgreCore::getSingleton().getSceneMgr()->setSkyBox(true, "skytrippy");
	initSnow();
}


LvlOneEnvironment::~LvlOneEnvironment()
{
}

void LvlOneEnvironment::initSnow()
{
/*	m_snowParticles = unique_ptr<SnowInstance>(new SnowInstance());
	for (Real i = 0.0; i < 3.14f*2.0f; i += 0.2f)
	{
		m_snowRenderers.push_back( unique_ptr<WeatherSnow>( new WeatherSnow(i, 0.2f) ) );
	}*/
}

void LvlOneEnvironment::update()
{
	/*for (auto& i : m_snowRenderers)
		i->snowCulling();
	if (m_snowParticles)
	    m_snowParticles->update();*/
	m_lightHandler.update();
}