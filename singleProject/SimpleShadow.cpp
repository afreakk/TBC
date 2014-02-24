#include "stdafx.h"
#include "SimpleShadow.h"
#include "OgreCore.h"
SimpleShadow::SimpleShadow(Ogre::SceneNode* parentNode)
: m_billboardSet(OgreCore::getSingleton().getSceneMgr()->createBillboardSet(1))
, m_parentNode(parentNode)
, m_isCreated(false)
{
    m_billboardSet->setBillboardType(BBT_PERPENDICULAR_COMMON);
    m_billboardSet->setCommonUpVector(Vector3(0.0, 0.0, 1.0));
    m_billboardSet->setCommonDirection(Vector3(0, 1, 0));
    m_billboardSet->setDefaultDimensions(400.0, 400.0);
    m_billboardSet->setMaterialName("particleShadow");
    m_parentNode->attachObject(m_billboardSet);
}
void SimpleShadow::setPosition(const Ogre::Vector3& pos)
{
	assert(m_isCreated);
    m_billboard->setPosition(pos);
}
void SimpleShadow::create(const Ogre::Vector3& pos)
{
	m_isCreated = true;
    m_billboard = unique_ptr<Ogre::Billboard>(m_billboardSet->createBillboard(pos));
}

bool SimpleShadow::isCreated()
{
	return m_isCreated;
}