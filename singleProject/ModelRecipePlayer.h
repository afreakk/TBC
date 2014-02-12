#pragma once
#include "ModelRecipe.h"
class ModelRecipePlayer : public ModelRecipe
{
public:
	ModelRecipePlayer();
	~ModelRecipePlayer();
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr) override;
	Ogre::SceneNode* initNode(Ogre::SceneManager* sMgr) override;
	BaseAnimation* getWalk(Ogre::Entity*) override;
	BaseAnimation* getAttack(Ogre::Entity*) override;
	BaseAnimation* getDie(Ogre::Entity*) override;
	BaseAnimation* getTumble(Ogre::Entity*);
private:
};
