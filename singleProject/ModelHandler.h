#pragma once
#include "UnitCircleMovement.h"
#include "OgreCore.h"
#include "ModelRecipe.h"
#include "ENUMLERPState.h"
#include "boost/noncopyable.hpp"
class ModelHandler : boost::noncopyable
{
public:
	ModelHandler(ModelRecipe* recipe, PolarCoordinates normalPos);
	virtual ~ModelHandler();
	void normalWalk(const Real& rInc, const NormalDirection& activeDirection);
	LERP_STATE lerpAttack(const Ogre::Vector3&, const Ogre::Real&);
	LERP_STATE lerpWalk(const Ogre::Vector3&, const Ogre::Real&);
	void fallAndDie();
	virtual void init();
	const Vector3 getBonePos() const ;
	const Vector3 getBoneOrientation() const;
protected:
	void updateNormalPos();
	bool lerp(const Ogre::Vector3& nextPosition, const Ogre::Real& dt, ANIMATIONS animation, Real distance, Real animLerpRatio, bool isRecursive=false);
	void parseScript();

	unique_ptr<ModelRecipe> m_crRecipe;
	Entity*const m_entity;
	SceneNode*const m_node;
	PolarCoordinates m_normalPosition;
	Real m_LERPPrecision;
	Real m_startAttackDistance;


	std::map<ANIMATIONS, unique_ptr<BaseAnimation> > m_animations;
	//getsnsets
public:
	virtual Entity*					getEntity() const;
	virtual SceneNode*				getNode() const ;
	virtual const PolarCoordinates&	getNormalPos() ;
	virtual void					setNormalPos(PolarCoordinates newPos);
	virtual const Vector3			getNormalVecPos() const;

};

