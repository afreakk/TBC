#include "stdafx.h"
#include "ModelHandler.h"
#include "GlobalVariables.h"
#include "MainUpdate.h"
#include "Occupado.h"

using namespace Ogre;


ModelHandler::ModelHandler(ModelRecipe* recipe, PolarCoordinates normalPos, ModelHandlerType type)
: m_crRecipe(recipe)
, m_entity(m_crRecipe->initMesh(OgreCore::getSingletonPtr()->getSceneMgr()))
, m_node(m_crRecipe->createNode())
, m_normalPosition(normalPos)
, m_normalDirection(NormalDirection::dirRight)
, m_hasLerpAttacked(false)
, m_modelHandlerType(type)
{
	parseScript();
}
ModelHandler::~ModelHandler()
{
	SceneNode* parent = m_entity->getParentSceneNode();
	parent->detachObject(m_entity);
	OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_entity->getName());
	parent->removeAndDestroyAllChildren();
	OgreCore::getSingleton().getSceneMgr()->destroySceneNode(parent->getName());
	cout << "ModelHandler destrucotr " << endl;
}

const ModelHandlerType  ModelHandler::getType() const
{
	return m_modelHandlerType;
}
void ModelHandler::parseScript()
{
	ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "ModelHandler");
	m_LERPPrecision = rootNode->findChild("LERPPrecision")->getValueR(0);
	m_startAttackDistance = rootNode->findChild("startAttackDistance")->getValueR(0);

}
bool ModelHandler::tumble(const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	return !lerp(nextPosition, dt, ANIMATIONS::TUMBLE, m_LERPPrecision, GlobalVariables::getSingleton().getLERPAnimTumblekRatio());
}
void ModelHandler::init() 
{
	m_crRecipe->attachNode(m_node, m_entity);
	m_animations[ANIMATIONS::ATTACK]= unique_ptr<BaseAnimation>(m_crRecipe->getAttack(m_entity) );
	m_animations[ANIMATIONS::WALK]	= unique_ptr<BaseAnimation>(m_crRecipe->getWalk(m_entity) );
	m_animations[ANIMATIONS::DIE]	= unique_ptr<BaseAnimation>(m_crRecipe->getDie(m_entity) );
	m_animations[ANIMATIONS::PREPARE] = unique_ptr<BaseAnimation>(m_crRecipe->getPrepare(m_entity));
	m_animations[ANIMATIONS::TUMBLE]	= unique_ptr<BaseAnimation>(m_crRecipe->getTumble(m_entity) );
	UnitCircleMovement::polarSetPosition(m_node, m_normalPosition);
}

bool ModelHandler::normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection)
{
	m_normalDirection = rInc > 0.0f ? NormalDirection::dirRight : ( rInc < 0.0f ?NormalDirection::dirLeft : m_normalDirection );
	assert(m_normalDirection != NormalDirection::None);
	m_animations[ANIMATIONS::WALK]->addTime(Ogre::Math::Abs(rInc)*GlobalVariables::getSingleton().getNormalAnimWalkSpeed(), m_animations);
	if (Occupado::isOccupiedVelocity(m_normalPosition, rInc))
		return false;
	m_normalPosition.theta += rInc;
	UnitCircleMovement::polarSetPosition(m_node, m_normalPosition);
	UnitCircleMovement::polarSetDirection(m_node, m_normalPosition, activeDirection);
	return true;
}

void ModelHandler::fallAndDie()
{
	Real animVel = MainUpdate::getSingleton().getScaledDeltaTime() * GlobalVariables::getSingleton().getAnimDieSpeed();
	m_animations[ANIMATIONS::DIE]->addTime(animVel , m_animations);
}
void ModelHandler::playAnimation(ANIMATIONS type)
{
	m_animations[type]->addTime( scaleTime(800)*GlobalVariables::getSingleton().getLERPAnimAttackRatio(), m_animations);
}
AttackReturn ModelHandler::lerpAttack( const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	if (!m_hasLerpAttacked)
	{
		if (!lerp(nextPosition, dt, ANIMATIONS::ATTACK, m_LERPPrecision+75.0f, GlobalVariables::getSingleton().getLERPAnimAttackRatio()))
			m_hasLerpAttacked = true;
		return AttackReturn::NOT_KILLED;
	}
	else
	{
		if (m_animations[ANIMATIONS::ATTACK]->hasEnded())
		{
			m_hasLerpAttacked = false;
            return AttackReturn::ANIM_ENDED;
		}
		else
		{
			Real dtScaled = scaleTime(dt);
			m_animations[ANIMATIONS::ATTACK]->addTime(dtScaled*GlobalVariables::getSingleton().getLERPAnimAttackRatio(),m_animations);
			return AttackReturn::KILLED;
		}
	}

}
bool ModelHandler::lerpWalk(const Ogre::Vector3& nextPosition, const Ogre::Real& dt, bool allTheWay)
{
	if (lerp(nextPosition, dt, ANIMATIONS::WALK, m_LERPPrecision + (allTheWay ? 0.0f : m_startAttackDistance), GlobalVariables::getSingleton().getLERPAnimWalkRatio()))
		return true;
	return false;
}
Ogre::Real ModelHandler::scaleTime(const Ogre::Real& time)
{
	return time*MainUpdate::getSingleton().getScaledDeltaTime();
}
bool ModelHandler::lerp(const Ogre::Vector3& nextPosition, Ogre::Real dt, const ANIMATIONS& animation, const Real& minDistance, const Real& animLerpRatio, bool isRecursive)
{
	if (!isRecursive)
		dt = scaleTime(dt);
	if (dt > minDistance)
	{
		lerp(nextPosition, dt-minDistance, animation, minDistance, animLerpRatio, true);
		dt = minDistance;
	}
	m_animations[animation]->addTime(dt*animLerpRatio, m_animations);
	m_node->lookAt(nextPosition,Ogre::Node::TransformSpace::TS_WORLD);
	m_node->translate(Vector3(0.0, 0.0, -dt), Ogre::Node::TS_LOCAL);
	if (!isRecursive)
	{
		updateNormalPos();
		if (m_node->getPosition().distance(nextPosition) > minDistance)
			return true;
	}
	return false;
}

const NormalDirection ModelHandler::getNormalDirection() const
{
	return m_normalDirection;
}
Ogre::SceneNode* ModelHandler::getNode() const 
{
	return m_node;
}
const PolarCoordinates& ModelHandler::getPolarCoordinates() 
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
const Vector3 ModelHandler::getBonePos() const
{
	return (*(m_entity->getSkeleton()->getBoneIterator().begin() + 5))->_getDerivedPosition();
}
const Vector3 ModelHandler::getBoneOrientation() const
{
	return (*(m_entity->getSkeleton()->getBoneIterator().begin() + 5))->_getDerivedOrientation().yAxis();
}

