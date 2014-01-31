#include "stdafx.h"
#include "ModelHandler.h"
#include "../Stats/GlobalVariables.h"

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
	m_animations[ANIMATIONS::ATTACK]= unique_ptr<BaseAnimation>(m_crRecipe->getAttack(m_entity) );
	m_animations[ANIMATIONS::WALK]	= unique_ptr<BaseAnimation>(m_crRecipe->getWalk(m_entity) );
	m_animations[ANIMATIONS::DIE]	= unique_ptr<BaseAnimation>(m_crRecipe->getDie(m_entity) );
	UnitCircleMovement::normalSetPosition(m_node, m_normalPosition);
}

void ModelHandler::normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection)
{
	Real rVel = rInc*GlobalVariables::getSingleton().getSpeed();
	m_animations[ANIMATIONS::WALK]->addTime(Ogre::Math::Abs(rVel)*30.0, m_animations);
	m_normalPosition.r += rVel;
	UnitCircleMovement::normalSetDirection(m_node, m_normalPosition, activeDirection);
	UnitCircleMovement::normalSetPosition(m_node, m_normalPosition);
}
//private
void ModelHandler::fallAndDie(Real dt)
{
	m_animations[ANIMATIONS::DIE]->addTime(dt, m_animations);
}
LERP_STATE ModelHandler::lerpAttack( const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	Real dtVel = dt*GlobalVariables::getSingleton().getSpeed();
	lerp(nextPosition, dtVel);
	m_animations[ANIMATIONS::ATTACK]->addTime(dtVel*2.0, m_animations);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > 0.01)
		return LERP_STATE::LERP_ATTACK;
	return LERP_STATE::LERP_WALK;

}
LERP_STATE ModelHandler::lerpWalk(const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	Real dtVel = dt*GlobalVariables::getSingleton().getSpeed();
	lerp(nextPosition, dtVel);
	m_animations[ANIMATIONS::WALK]->addTime(dtVel*10.0, m_animations);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > 0.225)
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