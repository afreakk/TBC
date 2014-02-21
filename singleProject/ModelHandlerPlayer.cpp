#include "stdafx.h"
#include "ModelHandlerPlayer.h"
#include "OgreCore.h"
#include "ModelRecipePlayer.h"

#include "GlobalVariables.h"
ModelHandlerPlayer::ModelHandlerPlayer(PolarCoordinates nwPos) 
: ModelHandler(new ModelRecipePlayer(), nwPos,ModelHandlerType::Player)
{
}
ModelHandlerPlayer::~ModelHandlerPlayer()
{
}


void ModelHandlerPlayer::init()
{
	ModelHandler::init();
	m_animations[ANIMATIONS::TUMBLE]	= unique_ptr<BaseAnimation>(static_cast<ModelRecipePlayer*>(m_crRecipe.get())->getTumble(m_entity) );
}
bool ModelHandlerPlayer::tumble(const Ogre::Vector3& nextPosition, const Ogre::Real& dt)
{
	return !lerp(nextPosition, dt, ANIMATIONS::TUMBLE, m_LERPPrecision, GlobalVariables::getSingleton().getLERPAnimTumblekRatio());
}