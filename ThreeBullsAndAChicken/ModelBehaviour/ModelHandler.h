#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../OgreCore/OgreCore.h"
#include "../ModelBehaviour/ModelRecipe.h"
enum class LERP_STATE
{
	LERP_WALK,
	LERP_ATTACK
};
enum class ANIMATIONS
{
	WALK,
	ATTACK,
	DIE,
	BLOCK
};
class ModelHandler : boost::noncopyable
{
public:
	ModelHandler(ModelRecipe* recipe, PolarCoordinates normalPos);
	virtual ~ModelHandler();
	void normalWalk(const Real& rInc, const NormalDirection& activeDirection);
	LERP_STATE lerpAttack(const Ogre::Vector3&, const Ogre::Real&);
	LERP_STATE lerpWalk(const Ogre::Vector3&, const Ogre::Real&);
	void fallAndDie(Real dt);
protected:
	void updateNormalPos();
	void lerp(const Ogre::Vector3&, const Ogre::Real&);
	virtual void init();
	void enableAnimation(ANIMATIONS);

	unique_ptr<ModelRecipe> m_crRecipe;
	Entity*const m_entity;
	SceneNode*const m_node;
	PolarCoordinates m_normalPosition;

	std::map<ANIMATIONS, AnimationState*> m_animations;
	//getsnsets
public:
	virtual Entity*					getEntity() const;
	virtual SceneNode*				getNode() const ;
	virtual const PolarCoordinates&	getNormalPos() ;
	virtual void					setNormalPos(PolarCoordinates newPos);
	virtual const Vector3			getNormalVecPos() const;

};

