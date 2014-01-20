#include "stdafx.h"
#include "UniversalModelHandler.h"
#include "boost\lexical_cast.hpp"

using namespace Ogre;


UniversalModelHandler::UniversalModelHandler(CreationRecipes* recipe)
: m_entity(nullptr), m_node(nullptr)
, m_walkAnim(nullptr), m_attackAnim(nullptr)
, m_crRecipe(recipe)
, m_lerpVal(0.0)
{
}
UniversalModelHandler::~UniversalModelHandler()
{
}

void UniversalModelHandler::playWalkAnim(const Real howMuch)
{
	enableAnimation(m_walkAnim);
	m_walkAnim->addTime(howMuch);
}
void UniversalModelHandler::normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection)
{
	enableAnimation(m_walkAnim);
	m_walkAnim->addTime(Ogre::Math::Abs(rInc)*20.0);
	m_normalPosition.r += rInc;
	UnitCircleMovement::normalSetDirection(m_node, getNormalPos(), activeDirection);
	UnitCircleMovement::normalSetPosition(m_node, getNormalPos());
}
//private
void UniversalModelHandler::enableAnimation(AnimationState* anim)
{
		anim->setEnabled(true);
}
LERP_STATE UniversalModelHandler::lerpAttack(const Ogre::Vector3& lastPosition, const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	lerp(lastPosition, nextPosition, dt);
	enableAnimation(m_attackAnim);
	m_attackAnim->addTime(dt*10.0);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > 0.05)
		return LERP_STATE::LERP_ATTACK;
	return LERP_STATE::LERP_WALK;

}
LERP_STATE UniversalModelHandler::lerpWalk(const Ogre::Vector3& lastPosition, const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	lerp(lastPosition, nextPosition, dt);
	enableAnimation(m_walkAnim);
	m_walkAnim->addTime(dt*10.0);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > 0.125)
		return LERP_STATE::LERP_WALK;
	return LERP_STATE::LERP_ATTACK;
}
void UniversalModelHandler::resetLerp()
{
	m_lerpVal = 0.0;
}
void UniversalModelHandler::lerp(const Ogre::Vector3& lastPosition, const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	/*auto SFDistance = lastPosition.distance(nextPosition);
	if (SFDistance > 0.0)
		m_lerpVal += dt/SFDistance;
	m_node->setPosition(Ogre::Math::lerp(lastPosition, nextPosition,m_lerpVal));
	m_node->lookAt(Ogre::Math::lerp(lastPosition, nextPosition, m_lerpVal+0.1),Ogre::Node::TransformSpace::TS_WORLD);*/
	m_node->lookAt(nextPosition,Ogre::Node::TransformSpace::TS_WORLD);
	m_node->translate(Vector3(0.0, 0.0, -dt), Ogre::Node::TS_LOCAL);
}
void UniversalModelHandler::init(NormalPosition pos) 
{
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();

	m_entity		= m_crRecipe->initMesh(sMgr);

	m_attackAnim	= m_crRecipe->getAttack(m_entity);
	m_walkAnim		= m_crRecipe->getWalk(m_entity);

	m_node			= m_crRecipe->initNode(sMgr);
	m_node->attachObject(m_entity);

	UnitCircleMovement::normalSetPosition(m_node, pos);
	m_normalPosition = pos;
}

Ogre::SceneNode* UniversalModelHandler::getNode() const 
{
	return m_node;
}
const NormalPosition& UniversalModelHandler::getNormalPos() 
{
	return m_normalPosition;
}

const Vector3 UniversalModelHandler::getNormalVecPos() const
{
	return UnitCircleMovement::posFromR(m_normalPosition);
}

Entity* UniversalModelHandler::getEntity() const
{
	return m_entity;
}
void UniversalModelHandler::setNormalPos(NormalPosition newPos)
{
	m_normalPosition = newPos;
}