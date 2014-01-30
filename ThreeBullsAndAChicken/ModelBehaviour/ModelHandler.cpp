#include "stdafx.h"
#include "ModelHandler.h"

using namespace Ogre;


ModelHandler::ModelHandler(ModelRecipe* recipe, PolarCoordinates normalPos)
: m_crRecipe(recipe)
, m_entity(m_crRecipe->initMesh(OgreCore::getSingletonPtr()->getSceneMgr()))
, m_node(m_crRecipe->initNode(OgreCore::getSingletonPtr()->getSceneMgr()))
, m_normalPosition(normalPos)
{
	init();
}
ModelHandler::~ModelHandler()
{
	cout << "ModelHandler destrucotr " << endl;
}

void ModelHandler::init() 
{
	m_node->attachObject(m_entity);
	m_animations[ANIMATIONS::ATTACK]= m_crRecipe->getAttack(m_entity);
	m_animations[ANIMATIONS::WALK]	= m_crRecipe->getWalk(m_entity);
	m_animations[ANIMATIONS::DIE]	= m_crRecipe->getDie(m_entity);
	UnitCircleMovement::normalSetPosition(m_node, m_normalPosition);
}

void ModelHandler::normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection)
{
	enableAnimation(ANIMATIONS::WALK);
	m_animations[ANIMATIONS::WALK]->addTime(Ogre::Math::Abs(rInc)*30.0);
	m_normalPosition.r += rInc;
	UnitCircleMovement::normalSetDirection(m_node, m_normalPosition, activeDirection);
	UnitCircleMovement::normalSetPosition(m_node, m_normalPosition);
}
//private
void ModelHandler::enableAnimation(ANIMATIONS animation)
{
	for (auto& animation : m_animations)
		animation.second->setEnabled(false);
	m_animations[animation]->setEnabled(true);
}
void ModelHandler::fallAndDie(Real dt)
{
	enableAnimation(ANIMATIONS::DIE);
	m_animations[ANIMATIONS::DIE]->setLoop(false);
	m_animations[ANIMATIONS::DIE]->addTime(dt);
}
LERP_STATE ModelHandler::lerpAttack( const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	lerp(nextPosition, dt);
	enableAnimation(ANIMATIONS::ATTACK);
	m_animations[ANIMATIONS::ATTACK]->addTime(dt*10.0);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > 0.05)
		return LERP_STATE::LERP_ATTACK;
	return LERP_STATE::LERP_WALK;

}
LERP_STATE ModelHandler::lerpWalk(const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	lerp(nextPosition, dt);
	enableAnimation(ANIMATIONS::WALK);
	m_animations[ANIMATIONS::WALK]->addTime(dt*10.0);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > 0.125)
		return LERP_STATE::LERP_WALK;
	return LERP_STATE::LERP_ATTACK;
}
void ModelHandler::lerp(const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	m_node->lookAt(nextPosition,Ogre::Node::TransformSpace::TS_WORLD);
	m_node->translate(Vector3(0.0, 0.0, -dt), Ogre::Node::TS_LOCAL);
	updateNormalPos();
}

Ogre::SceneNode* ModelHandler::getNode() const 
{
	return m_node;
}
const PolarCoordinates& ModelHandler::getNormalPos() 
{
	return m_normalPosition;
}

const Vector3 ModelHandler::getNormalVecPos() const
{
	return UnitCircleMovement::posFromR(m_normalPosition);
}

Entity* ModelHandler::getEntity() const
{
	return m_entity;
}
void ModelHandler::setNormalPos(PolarCoordinates newPos)
{
	m_normalPosition = newPos;
}
void ModelHandler::updateNormalPos()
{
	vectorToNormal(m_node->getPosition(), m_normalPosition);
}