#pragma once
#include "ModelRecipe.h"
#include "boost/noncopyable.hpp"

class ModelRecipeMutantSuicide:public ModelRecipe, boost::noncopyable
{
public:
	ModelRecipeMutantSuicide();
	~ModelRecipeMutantSuicide();
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr) override;
	BaseAnimation* getWalk(Ogre::Entity*) override;
	BaseAnimation* getAttack(Ogre::Entity*) override;
	BaseAnimation* getDie(Ogre::Entity*) override;
	virtual void attachNode(Ogre::SceneNode* node, Ogre::Entity* ent);
private:
	const int m_id;
	static int s_count;
	string m_entityName;
	string m_nodeName;
};
