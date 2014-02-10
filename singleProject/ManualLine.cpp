#include "stdafx.h"
#include "ManualLine.h"
#include "OgreCore.h"
ManualLine::ManualLine()
: m_line(nullptr)
{
    
}
ManualLine::ManualLine(Vector3 fromPoint, Vector3 toPoint, string material)
{
	init(fromPoint, toPoint, material);
}
void ManualLine::init(Ogre::Vector3 fromPoint, Ogre::Vector3 toPoint, string material)
{
    auto mSceneMgr = OgreCore::getSingleton().getSceneMgr();
    m_line = mSceneMgr->createManualObject();

    m_line->begin(material, Ogre::RenderOperation::OT_LINE_LIST);
    m_line->position(fromPoint);
    m_line->position(toPoint);
    m_line->end();

    OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->attachObject(m_line);
}
ManualLine::~ManualLine()
{
	if (!m_line)
		assert(0);
    m_line->detachFromParent();
    OgreCore::getSingleton().getSceneMgr()->destroyManualObject(m_line);
}
void ManualLine::update(Vector3 fromPoint, Vector3 toPoint)
{
	if (!m_line)
		assert(0);
	m_line->beginUpdate(0);
	m_line->position(fromPoint);
	m_line->position(toPoint);
	m_line->end();
}