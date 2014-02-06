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
	UnitCircleMovement::polarSetPosition(m_node, m_normalPosition);
}

void ModelHandler::normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection)
{
	Real rVel = rInc*GlobalVariables::getSingleton().getSpeed();
	m_animations[ANIMATIONS::WALK]->addTime(Ogre::Math::Abs(rVel)*30.0, m_animations);
	m_normalPosition.r += rVel;
	UnitCircleMovement::polarSetPosition(m_node, m_normalPosition);
	UnitCircleMovement::polarSetDirection(m_node, m_normalPosition, activeDirection);
}
//private
void ModelHandler::fallAndDie(Real dt)
{
	m_animations[ANIMATIONS::DIE]->addTime(dt*GlobalVariables::getSingleton().getSpeed(), m_animations);
}
LERP_STATE ModelHandler::lerpAttack( const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	if(lerp(nextPosition, dt, ANIMATIONS::ATTACK,10.0))
		return LERP_STATE::LERP_ATTACK;
	return LERP_STATE::LERP_WALK;

}
LERP_STATE ModelHandler::lerpWalk(const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	if (lerp(nextPosition, dt, ANIMATIONS::WALK,30.0))
		return LERP_STATE::LERP_WALK;
	return LERP_STATE::LERP_ATTACK;
}
bool ModelHandler::lerp(const Ogre::Vector3& nextPosition, const Ogre::Real& dt, ANIMATIONS animation, Real minDistance)
{
	Real dtVel = dt*GlobalVariables::getSingleton().getSpeed();
	m_animations[animation]->addTime(dtVel, m_animations);
	m_node->lookAt(nextPosition,Ogre::Node::TransformSpace::TS_WORLD);
	m_node->translate(Vector3(0.0, 0.0, -dt), Ogre::Node::TS_LOCAL);
	updateNormalPos();
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance > minDistance)
		return true;
	return false;
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
	return UnitCircleMovement::VectorFromPolar(m_normalPosition);
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
	vectorToPolar(m_node->getPosition(), m_normalPosition);
}