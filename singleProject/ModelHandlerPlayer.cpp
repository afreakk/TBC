#include "stdafx.h"
#include "ModelHandlerPlayer.h"
#include "OgreCore.h"
#include "ModelRecipePlayer.h"

#include "GlobalVariables.h"
ModelHandlerPlayer::ModelHandlerPlayer(PolarCoordinates nwPos) 
: ModelHandler(new ModelRecipePlayer(), nwPos,ModelHandlerType::Player)
, m_slowMoParticle(m_node)
, m_teleportParticle(m_node)
, m_isTeleporting(false)
{
}
ModelHandlerPlayer::~ModelHandlerPlayer()
{
}


void ModelHandlerPlayer::init()
{
	ModelHandler::init();
}
void ModelHandlerPlayer::displaySlowMotionParticle(bool enabled)
{
	m_slowMoParticle.select(enabled);
}

void ModelHandlerPlayer::teleportIn()
{
	m_teleportParticle.select(true);
	m_entity->setVisible(false);
	m_isTeleporting = true;
}

void ModelHandlerPlayer::teleportMove()
{
	ModelHandler::normalWalk(m_normalDirection == NormalDirection::dirLeft ? -Math::PI / 32.0f : Math::PI / 32.0f, m_normalDirection,true);
}
void ModelHandlerPlayer::teleportMove(const Ogre::Vector3& to)
{
	ModelHandler::move(to);
}
void ModelHandlerPlayer::teleportOut()
{
	m_teleportParticle.select(true);
	m_entity->setVisible(true);
	m_isTeleporting = false;
}
bool ModelHandlerPlayer::isTeleporting()
{
	return m_isTeleporting;
}