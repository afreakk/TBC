#include "stdafx.h"
#include "ModelHandlerPlayer.h"
#include "OgreCore.h"
#include "ModelRecipePlayer.h"

#include "GlobalVariables.h"
ModelHandlerPlayer::ModelHandlerPlayer(PolarCoordinates nwPos) 
: ModelHandler(new ModelRecipePlayer(), nwPos,ModelHandlerType::Player)
, m_slowMoParticle(m_node)
, m_teleportParticle(m_node)
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

void ModelHandlerPlayer::teleport()
{
	m_teleportParticle.select(true);
	ModelHandler::normalWalk(m_normalDirection == NormalDirection::dirLeft ? -Math::PI / 64.0f : Math::PI / 64.0f, m_normalDirection);
}