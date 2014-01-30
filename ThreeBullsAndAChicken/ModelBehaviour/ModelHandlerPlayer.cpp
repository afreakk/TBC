#include "stdafx.h"
#include "ModelHandlerPlayer.h"
#include "../OgreCore/OgreCore.h"
#include "ModelRecipePlayer.h"

ModelHandlerPlayer::ModelHandlerPlayer(PolarCoordinates nwPos) 
: ModelHandler(new ModelRecipePlayer(), nwPos)
,  m_isBlocking(false)
{
}
ModelHandlerPlayer::~ModelHandlerPlayer()
{
}

void ModelHandlerPlayer::init()
{
	ModelHandler::init();
	m_animations[ANIMATIONS::BLOCK] = static_cast<ModelRecipePlayer*>(m_crRecipe.get())->getBlock(m_entity);
}


void ModelHandlerPlayer::block(Real dt)
{
	m_isBlocking = true;
	enableAnimation(ANIMATIONS::BLOCK);
	m_animations[ANIMATIONS::BLOCK]->addTime(dt);
}

void ModelHandlerPlayer::unBlock()
{
	m_isBlocking = false;
}