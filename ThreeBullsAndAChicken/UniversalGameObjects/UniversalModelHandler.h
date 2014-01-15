#pragma once
#include "Ogre.h"
#include "../Other/UnitCircleMovement.h"
class UniversalModelHandler
{
public:
	UniversalModelHandler(string entityName, string fileName, string walkAnimName, string nodeName);
	~UniversalModelHandler();
	void init(NormalPosition pos);
	void normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection);
	Ogre::SceneNode* getNode();
	const NormalPosition& getNormalPos();
protected:
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr);
	Ogre::SceneNode* initPlayerNode(Ogre::SceneManager* sMgr, Ogre::Entity* playerEntity);

	NormalPosition m_normalPosition;

	Ogre::Entity* m_entity;
	Ogre::SceneNode* m_node;
	Ogre::AnimationState* m_animationState;

	const string m_entityName;
	const string m_fileName;
	const string m_walkAnimationName;
	const string m_nodeName;
};

