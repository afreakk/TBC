#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../OgreCore/OgreCore.h"
class UniversalModelHandler
{
public:
	UniversalModelHandler(string entityName, string fileName, string walkAnimName, string nodeName);
	~UniversalModelHandler();
	void init(NormalPosition pos);
	void normalWalk(const Real& rInc, const NormalDirection& activeDirection);
	SceneNode* getNode() const ;
	const NormalPosition& getNormalPos() const ;
	Entity* getEntity() const;
protected:
	Entity* initMesh(SceneManager* sMgr);
	SceneNode* initPlayerNode(SceneManager* sMgr, Entity* playerEntity);

	NormalPosition m_normalPosition;

	Entity* m_entity;
	SceneNode* m_node;
	AnimationState* m_animationState;

	string m_entityName;
	const string m_fileName;
	const string m_walkAnimationName;
	string m_nodeName;

	const int m_id;
	static int s_count;
};

