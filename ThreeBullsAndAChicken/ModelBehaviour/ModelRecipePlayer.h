#pragma once
#include "stdafx.h"
#include "../ModelBehaviour/ModelRecipe.h"
class ModelRecipePlayer : public ModelRecipe
{
public:
	ModelRecipePlayer();
	~ModelRecipePlayer();
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr) override;
	Ogre::SceneNode* initNode(Ogre::SceneManager* sMgr) override;
	Ogre::AnimationState* getWalk(Ogre::Entity*) override;
	Ogre::AnimationState* getAttack(Ogre::Entity*) override;
	Ogre::AnimationState* getDie(Ogre::Entity*) override;
	Ogre::AnimationState* getBlock(Ogre::Entity*);
private:
};

