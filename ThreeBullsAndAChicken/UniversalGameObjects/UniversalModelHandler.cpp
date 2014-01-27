#include "stdafx.h"
#include "UniversalModelHandler.h"

using namespace Ogre;


UniversalModelHandler::UniversalModelHandler(CreationRecipes* recipe, PolarCoordinates normalPos)
: m_crRecipe(recipe)
, m_entity(m_crRecipe->initMesh(OgreCore::getSingletonPtr()->getSceneMgr()))
, m_node(m_crRecipe->initNode(OgreCore::getSingletonPtr()->getSceneMgr()))
, m_normalPosition(normalPos)
{
	init();
}
UniversalModelHandler::~UniversalModelHandler()
{
	cout << "UniversalModelHandler destrucotr " << endl;
}

void UniversalModelHandler::init() 
{
	m_node->attachObject(m_entity);
	m_animations[ANIMATIONS::ATTACK]= m_crRecipe->getAttack(m_entity);
	m_animations[ANIMATIONS::WALK]	= m_crRecipe->getWalk(m_entity);
	m_animations[ANIMATIONS::DIE]	= m_crRecipe->getDie(m_entity);
	UnitCircleMovement::normalSetPosition(m_node, m_normalPosition);
}

void UniversalModelHandler::normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection)
{
	enableAnimation(ANIMATIONS::WALK);
	m_animations[ANIMATIONS::WALK]->addTime(Ogre::Math::Abs(rInc)*20.0);
	m_normalPosition.r += rInc;
	UnitCircleMovement::normalSetDirection(m_node, m_normalPosition, activeDirection);
	UnitCircleMovement::normalSetPosition(m_node, m_normalPosition);
}
//private
void UniversalModelHandler::enableAnimation(ANIMATIONS animation)
{
	for (auto& animation : m_animations)
		animation.second->setEnabled(false);
	m_animations[animation]->setEnabled(true);
}
void UniversalModelHandler::fallAndDie(Real dt)
{
	enableAnimation(ANIMATIONS::DIE);
	m_animations[ANIMATIONS::DIE]->setLoop(false);
	m_animations[ANIMATIONS::DIE]->addTime(dt);
}
LERP_STATE UniversalModelHandler::lerpAttack( const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	lerp(nextPosition, dt);
	enableAnimation(ANIMATIONS::ATTACK);
	m_animations[ANIMATIONS::ATTACK]->addTime(dt*10.0);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > 0.05)
		return LERP_STATE::LERP_ATTACK;
	return LERP_STATE::LERP_WALK;

}
LERP_STATE UniversalModelHandler::lerpWalk(const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	lerp(nextPosition, dt);
	enableAnimation(ANIMATIONS::WALK);
	m_animations[ANIMATIONS::WALK]->addTime(dt*10.0);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > 0.125)
		return LERP_STATE::LERP_WALK;
	return LERP_STATE::LERP_ATTACK;
}
void UniversalModelHandler::lerp(const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	m_node->lookAt(nextPosition,Ogre::Node::TransformSpace::TS_WORLD);
	m_node->translate(Vector3(0.0, 0.0, -dt), Ogre::Node::TS_LOCAL);
	updateNormalPos();
}

Ogre::SceneNode* UniversalModelHandler::getNode() const 
{
	return m_node;
}
const PolarCoordinates& UniversalModelHandler::getNormalPos() 
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
void UniversalModelHandler::setNormalPos(PolarCoordinates newPos)
{
	m_normalPosition = newPos;
}
void UniversalModelHandler::updateNormalPos()
{
	vectorToNormal(m_node->getPosition(), m_normalPosition);
}