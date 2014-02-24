#include "stdafx.h"
#include "PlayerHandlerStateSelectionLine.h"
#include "MutantContainer.h"
#include "PlayerContainer.h"
#include "Player.h"
#include "Tubes.h"
#include "OgreCore.h"
static unsigned PlayerSelectionLineCount = 0;
PlayerHandlerStateSelectionLine::PlayerHandlerStateSelectionLine()
: m_tubeParentNode(OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode())
, m_addHim(true)
{
	m_path.create(PlayerContainer::getSingleton().getPlayer()->getNode());
	/*m_tubeObj = unique_ptr<SeriesOfTubes>(new SeriesOfTubes(OgreCore::getSingleton().getSceneMgr(), 8, 10.0, 16, 16, 20.0));
	m_tubeObj->addPoint(m_currentNode);
	m_tubeObj->addPoint(m_currentNode);
	m_tubeObj->setSceneNode(m_tubeParentNode);
	m_tubeObj->setOffset(Vector3(0.0, 225.0, 0.0));
	m_tubeObj->createTubes("SelectionTube"+ ++PlayerSelectionLineCount,"BaseWhite",false,true);*/
}

void PlayerHandlerStateSelectionLine::setNewTarget(Ogre::SceneNode* node)
{
    
	if (m_addHim)
	{
        m_path.insertNode(node);
		m_addHim = false;
	}
	m_path.refreshLatestNode(node);
//	m_tubeObj->updateLatestPoint(m_currentNode = node);
}

void PlayerHandlerStateSelectionLine::addEnemy()
{
	m_addHim = true;
//	m_tubeObj->addPoint(m_currentNode);
}
void PlayerHandlerStateSelectionLine::update()
{
	m_path.update();
//	m_tubeObj->_update();
}
PlayerHandlerStateSelectionLine::~PlayerHandlerStateSelectionLine()
{
}
