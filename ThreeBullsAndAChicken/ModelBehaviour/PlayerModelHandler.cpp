#include "stdafx.h"
#include "PlayerModelHandler.h"
#include "../OgreCore/OgreCore.h"
#include "PlayerRecipe.h"

PlayerModelHandler::PlayerModelHandler(PolarCoordinates nwPos) 
: UniversalModelHandler(new PlayerRecipe(), nwPos)
,  m_isBlocking(false)
{
}
PlayerModelHandler::~PlayerModelHandler()
{
}

void PlayerModelHandler::init()
{
	UniversalModelHandler::init();
	m_animations[ANIMATIONS::BLOCK] = static_cast<PlayerRecipe*>(m_crRecipe.get())->getBlock(m_entity);
}


void PlayerModelHandler::block(Real dt)
{
	m_isBlocking = true;
	enableAnimation(ANIMATIONS::BLOCK);
	m_animations[ANIMATIONS::BLOCK]->addTime(dt);
}

void PlayerModelHandler::unBlock()
{
	m_isBlocking = false;
}