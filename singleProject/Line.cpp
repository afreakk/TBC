#include "stdafx.h"
#include "Line.h"

#include "OgreCore.h"
const Vector3 LINEHEIGHT = Vector3(0.f,0.01f,0.f);
Line::Line(Node* start, Node* end)
: m_start(start)
, m_end(end)
{
	auto mSceneMgr = OgreCore::getSingleton().getSceneMgr();
	myManualObject = mSceneMgr->createManualObject();

	myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material", "General");
	myManualObjectMaterial->setReceiveShadows(true);
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 0, 0, 0.1);


	myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST);
	myManualObject->position(m_start->getPosition()+LINEHEIGHT);
	myManualObject->position(m_end->getPosition()+LINEHEIGHT);
	myManualObject->end();

	OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->attachObject(myManualObject);
}

void Line::newNode(Node* end)
{
	m_end = end;
}

void Line::update()
{
	myManualObject->beginUpdate(0);
	myManualObject->position(m_start->getPosition() + LINEHEIGHT);
	myManualObject->position(m_end->getPosition() + LINEHEIGHT);
	myManualObject->end();
}
Line::~Line()
{
	myManualObject->detachFromParent();
}
