#pragma once
#include "ModelRecipe.h"
class ModelRecipePlayer : public ModelRecipe
{
public:
	ModelRecipePlayer();
	~ModelRecipePlayer();
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr) override;
	BaseAnimation* getWalk(Ogre::Entity*, Skritt* skritt) override;
	BaseAnimation* getAttack(Ogre::Entity*) override;
	BaseAnimation* getDie(Ogre::Entity*) override;
	BaseAnimation* getTumble(Ogre::Entity*, Skritt* skritt) override;
	BaseAnimation* getIdle(Ogre::Entity*);
	virtual void attachNode(Ogre::SceneNode* node, Ogre::Entity* ent);
	Ogre::SceneNode* createNode() override;
	BaseAnimation* getPrepare(Ogre::Entity*)override;
	const std::string& getMaterialName(const std::string& typ) override;
};

