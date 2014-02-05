#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../ModelBehaviour/ModelHandler.h"
class ModelHandlerPlayer:public ModelHandler
{
public:
	ModelHandlerPlayer(PolarCoordinates nwPos);
	~ModelHandlerPlayer();
	bool tumble(const Ogre::Vector3& nextPosition, const Ogre::Real& dt);
	void init()override;
protected:
};

