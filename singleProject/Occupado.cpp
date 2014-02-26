#include "stdafx.h"
#include "Occupado.h"
#include "PolarCoordinates.h"
#include "MutantContainer.h"
#include "PlayerContainer.h"
#include "Player.h"
#include "LaneSettings.h"
const Ogre::Real NormalModeModelSpacing = Math::PI/1024.0;

bool Occupado::isOccupied(PolarCoordinates& e , const Ogre::Real& velocity)
{
	for (auto& it : MutantContainer::getSingleton().getMutantIt())
	{
		if (hitTest(it, e, velocity))
			return true;
	}
	return (hitTest(PlayerContainer::getSingleton().getPlayer(), e, velocity));
}


bool Occupado::hitTest(const BehaviourObject* object, const PolarCoordinates& e, const Ogre::Real& velocity)
{
	if (!float_compare(object->getPolarCoordinates().radius, e.radius, LaneSettings::getSingleton().getIncrement()/Real(2.0)) 
		|| &e == &(object->getPolarCoordinates()))
		return false;
	if (float_compare(object->getPolarCoordinates().theta, e.theta + velocity, NormalModeModelSpacing))
	{
		if (e.theta > object->getPolarCoordinates().theta) {
			if (velocity > 0)
				return false;
		}
		else if (velocity < 0)
            return false;
        return true;
	}
	return false;
}