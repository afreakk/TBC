#include "stdafx.h"
#include "LineBillboardSet.h"
#include "OgreCore.h"

LineBillboardSet::LineBillboardSet(Ogre::SceneNode* parentNode)
: m_billboardSet(OgreCore::getSingleton().getSceneMgr()->createBillboardSet())
, m_sceneNode(parentNode->createChildSceneNode())
, m_dimension(100.0)
{
    m_billboardSet->setBillboardType(BBT_PERPENDICULAR_COMMON);
    m_billboardSet->setCommonUpVector(Vector3(0.0, 0.0, 1.0));
    m_billboardSet->setCommonDirection(Vector3(0, 1, 0));
    m_billboardSet->setDefaultDimensions(m_dimension, m_dimension);
    m_billboardSet->setMaterialName("selectionLine");
    m_sceneNode->attachObject(m_billboardSet);
}

LineBillboardSet::~LineBillboardSet()
{
	for (auto& i : m_billboard)
        m_billboardSet->removeBillboard(i);
    m_sceneNode->detachObject(m_billboardSet);
	OgreCore::getSingleton().getSceneMgr()->destroyBillboardSet(m_billboardSet);
}
Ogre::Billboard* LineBillboardSet::getBillboard(const Ogre::Vector3& pos)
{
	m_billboard.push_back(m_billboardSet->createBillboard(pos));
	return m_billboard.back();
}
bool LineBillboardSet::destroyBillboard(Ogre::Billboard* board)
{
	auto i = std::find(m_billboard.begin(), m_billboard.end(), board);
	if (i != m_billboard.end())
	{
        m_billboardSet->removeBillboard(*i);
		m_billboard.erase(i);
		return true;
	}
    return false;
}