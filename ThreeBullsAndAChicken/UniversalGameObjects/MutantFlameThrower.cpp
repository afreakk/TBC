#include "stdafx.h"
#include "MutantFlameThrower.h"
#include "../OgreCore/OgreCore.h"

int MutantFlameThrower::m_flameThrowerCount = 0;
MutantFlameThrower::MutantFlameThrower(SceneNode* parentNode)
: ParticleEffect(parentNode, ++m_flameThrowerCount, "flameThrower", "mutantflamethrower", OgreCore::getSingleton().getSceneMgr())
{
	m_node->setPosition(0, 75, 0);
}


MutantFlameThrower::~MutantFlameThrower()
{
}

