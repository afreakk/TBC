#include "stdafx.h"
#include "LvlOneEnvironment.h"
#include "OgreCore.h"

LvlOneEnvironment::LvlOneEnvironment()
{
	OgreCore::getSingleton().getSceneMgr()->setSkyBox(true, "skytrippy");
}


LvlOneEnvironment::~LvlOneEnvironment()
{
}

void LvlOneEnvironment::update()
{
	m_lightHandler.update();
}