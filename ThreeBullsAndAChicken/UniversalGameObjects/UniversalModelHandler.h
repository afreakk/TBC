#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../OgreCore/OgreCore.h"
#include "../Other/CreationRecipes.h"
enum class LERP_STATE
{
	LERP_WALK,
	LERP_ATTACK
};
class UniversalModelHandler
{
public:
	UniversalModelHandler(CreationRecipes* recipe);
	~UniversalModelHandler();
	virtual void init(NormalPosition pos);
	void normalWalk(const Real& rInc, const NormalDirection& activeDirection);
	void playWalkAnim(const Real);
	void resetLerp();
	LERP_STATE lerpAttack(const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Real&);
	LERP_STATE lerpWalk(const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Real&);
private:
	void lerp(const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Real&);
protected:
	void enableAnimation(AnimationState*);
	CreationRecipes* m_crRecipe;

	NormalPosition m_normalPosition;
	Entity* m_entity;
	SceneNode* m_node;
	Real m_lerpVal;

	AnimationState* m_walkAnim;
	AnimationState* m_attackAnim;
	//getsnsets
public:
	Entity*					getEntity() const;
	SceneNode*				getNode() const ;
	const NormalPosition&	getNormalPos() ;
	void					setNormalPos(NormalPosition newPos);
	const Vector3			getNormalVecPos() const;

};

