#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../OgreCore/OgreCore.h"
#include "../Other/CreationRecipes.h"
class UniversalModelHandler
{
public:
	UniversalModelHandler(CreationRecipes* recipe);
	~UniversalModelHandler();
	void init(NormalPosition pos);
	void normalWalk(const Real& rInc, const NormalDirection& activeDirection);
	void playWalkAnim(const Real);
protected:
	void enableAnimation(AnimationState*);
	CreationRecipes* m_crRecipe;

	NormalPosition m_normalPosition;
	Entity* m_entity;
	SceneNode* m_node;
	string m_materialName;

	AnimationState* m_walkAnim;
	AnimationState* m_attackAnim;
	//getsnsets
public:
	string					getMaterial() const;
	Entity*					getEntity() const;
	SceneNode*				getNode() const ;
	const NormalPosition&	getNormalPos() ;
	void					setNormalPos(NormalPosition newPos);
	const Vector3			getNormalVecPos() const;

};

