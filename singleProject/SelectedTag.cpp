#include "stdafx.h"
#include "SelectedTag.h"
#include "OgreCore.h"
int SelectedTag::m_selectedTagCount = 0;
SelectedTag::SelectedTag(SceneNode* parentNode)
: m_id(++m_selectedTagCount)
, m_node(parentNode->createChildSceneNode())
, m_particleSystem( ParticleUniverse::ParticleSystemManager::getSingleton().createParticleSystem(
"selectedTag"+boost::lexical_cast<string>(m_id), "hwoosh", OgreCore::getSingleton().getSceneMgr() ) )
{
	m_node->attachObject(m_particleSystem);
}


SelectedTag::~SelectedTag()
{
}

void SelectedTag::select()
{
	m_particleSystem->start();
}