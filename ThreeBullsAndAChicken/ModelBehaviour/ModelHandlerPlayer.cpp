#include "stdafx.h"
#include "ModelHandlerPlayer.h"
#include "../OgreCore/OgreCore.h"
#include "ModelRecipePlayer.h"

#include "../Stats/GlobalVariables.h"
ModelHandlerPlayer::ModelHandlerPlayer(PolarCoordinates nwPos) 
: ModelHandler(new ModelRecipePlayer(), nwPos)
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
	Real dtVel = dt*GlobalVariables::getSingleton().getSpeed();
	lerp(nextPosition, dtVel);
	m_animations[ANIMATIONS::TUMBLE]->addTime(dtVel, m_animations);
	auto ADistance = m_node->getPosition().distance(nextPosition);
	if (ADistance < 0.1)
		return true;
	return false;
}