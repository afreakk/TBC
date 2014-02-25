#include "stdafx.h"
#include "SimpleShadow.h"
#include "OgreCore.h"
SimpleShadow::SimpleShadow(Ogre::SceneNode* parentNode)
: m_billboardSet(OgreCore::getSingleton().getSceneMgr()->createBillboardSet(1))
, m_sceneNode(parentNode->createChildSceneNode())
, m_isCreated(false)
{
    m_billboardSet->setBillboardType(BBT_PERPENDICULAR_COMMON);
    m_billboardSet->setCommonUpVector(Vector3(0.0, 0.0, 1.0));
    m_billboardSet->setCommonDirection(Vector3(0, 1, 0));
    m_billboardSet->setDefaultDimensions(400.0, 400.0);
    m_billboardSet->setMaterialName("particleShadow");
    m_sceneNode->attachObject(m_billboardSet);
}
SimpleShadow::~SimpleShadow()
{
	m_sceneNode->detachObject(m_billboardSet);
	m_billboardSet->removeBillboard(m_billboard);
	OgreCore::getSingleton().getSceneMgr()->destroyBillboardSet(m_billboardSet);
}
void SimpleShadow::setPosition(const Ogre::Vector3& pos)
{
	assert(m_isCreated);
    m_sceneNode->setPosition(pos);
}
void SimpleShadow::create()
{
	m_isCreated = true;
    m_billboard = m_billboardSet->createBillboard(Vector3::ZERO);
}

bool SimpleShadow::isCreated()                 
{
	return m_isCreated;
}
void SimpleShadow::setVisible(bool visible)
{
	m_billboardSet->setVisible(visible);
}