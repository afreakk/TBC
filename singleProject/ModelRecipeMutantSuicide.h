#pragma once
#include "ModelRecipe.h"
#include "boost/noncopyable.hpp"

class ModelRecipeMutantSuicide:public ModelRecipe, boost::noncopyable
{
public:
	ModelRecipeMutantSuicide();
	~ModelRecipeMutantSuicide();
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr) override;
	BaseAnimation* getWalk(Ogre::Entity*, Skritt* skritt) override;
	BaseAnimation* getAttack(Ogre::Entity*) override;
	BaseAnimation* getDie(Ogre::Entity*) override;
	BaseAnimation* getPrepare(Ogre::Entity*)override;
	BaseAnimation* getTumble(Ogre::Entity*) override;
	virtual void attachNode(Ogre::SceneNode* node, Ogre::Entity* ent);
	Ogre::SceneNode* createNode() override;
	const std::string& getMaterialName(const std::string& type) override;
private:
	const int m_id;
	static int s_count;
	string m_entityName;
	string m_nodeName;
	string m_materialName;
	string m_hoveredName;
};
