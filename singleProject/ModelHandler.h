#pragma once
#include "UnitCircleMovement.h"
#include "OgreCore.h"
#include "ModelRecipe.h"
#include "ENUMLERPState.h"
#include "boost/noncopyable.hpp"
#include "Tooltip.h"
#include "AudioHelpers.h"
enum class AttackReturn
{
    NOT_KILLED,
    KILLED,
    ANIM_ENDED
};
enum class ModelHandlerType
{
    Player,
    Mutant
};
class ModelHandler : boost::noncopyable
{
public:
	ModelHandler(ModelRecipe* recipe, PolarCoordinates normalPos, ModelHandlerType type);
	virtual ~ModelHandler();
	bool normalWalk(const Real& rInc, const NormalDirection& activeDirection, bool noScale=false);
	AttackReturn lerpAttack(const Ogre::Vector3&, const Ogre::Real&);
	bool lerpWalk(const Ogre::Vector3&, const Ogre::Real&, bool allTheWay=false );
	void fallAndDie();
	virtual void init();
	const Vector3 getBonePos() const ;
	const Vector3 getBoneOrientation() const;
	const NormalDirection getNormalDirection() const;
	Ogre::Real scaleTime(const Ogre::Real& time, bool rad = false);
	void playAnimation(ANIMATIONS);
	bool tumble(const Ogre::Vector3& nextPosition, const Ogre::Real& dt);
	void freeze();
	void tooltip(const std::string& msg, const std::string& caption);
	void hideTooltip();
	void move(const Ogre::Vector3& to);
protected:
	void updateNormalPos();
	bool lerp(const Ogre::Vector3& nextPosition, Ogre::Real dt, const ANIMATIONS& animation, const Real& minDistance, const Real& animLerpRatio, bool isRecursive=false);
	void parseScript();

	unique_ptr<ModelRecipe> m_crRecipe;
	Entity*const m_entity;
	SceneNode*const m_node;
	PolarCoordinates m_normalPosition;
	Real m_LERPPrecision;
	Real m_startAttackDistance;
	NormalDirection m_normalDirection;
	bool m_hasLerpAttacked;
	ModelHandlerType m_modelHandlerType;
	Ogre::Real m_freezeTimer;
	TwoDTooltip m_tooltip;
	Skritt m_skritt;


	std::map<ANIMATIONS, unique_ptr<BaseAnimation> > m_animations;
	//getsnsets
public:
	virtual Entity*					getEntity() const;
	virtual SceneNode*				getNode() const ;
	virtual const PolarCoordinates&	getPolarCoordinates() ;
	virtual void					setNormalPos(PolarCoordinates newPos);
	virtual const Vector3			getNormalVecPos() const;
	virtual const ModelHandlerType  getType() const;

};

