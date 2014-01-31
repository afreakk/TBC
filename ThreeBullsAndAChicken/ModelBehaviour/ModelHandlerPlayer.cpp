#include "stdafx.h"
#include "ModelHandlerPlayer.h"
#include "../OgreCore/OgreCore.h"
#include "ModelRecipePlayer.h"

ModelHandlerPlayer::ModelHandlerPlayer(PolarCoordinates nwPos) 
: ModelHandler(new ModelRecipePlayer(), nwPos)
{
}
ModelHandlerPlayer::~ModelHandlerPlayer()
{
}

