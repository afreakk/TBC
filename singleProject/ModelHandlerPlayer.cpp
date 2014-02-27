#include "stdafx.h"
#include "ModelHandlerPlayer.h"
#include "OgreCore.h"
#include "ModelRecipePlayer.h"

#include "GlobalVariables.h"
ModelHandlerPlayer::ModelHandlerPlayer(PolarCoordinates nwPos) 
: ModelHandler(new ModelRecipePlayer(), nwPos,ModelHandlerType::Player)
, m_slowMoParticle(m_node)
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