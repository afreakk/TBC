#include "stdafx.h"
#include "ContainerLogic.h"
#include "Mutant.h"
#include "LaneSettings.h"



Mutant* ContainerLogic::getClosest(std::list<Mutant*>& list, const Ogre::Real& theta, Mutant* mutant, bool abs, bool higher)
{
	Real closestDistance = numeric_limits<Real>::max();
	Mutant* closestLegalMutant = nullptr;
	for (const auto& itt : list)
	{
		if (itt == mutant)
			continue;
		Real distance = _getDistance(abs,theta,itt,higher);
		auto result = _checkDistance(distance, closestDistance, itt);
		if (result.first)
		{
			if (!result.second)
				return getClosest(list,theta, mutant,abs,higher);
			else
				closestLegalMutant = result.second;
		}
	}
	return closestLegalMutant;
}
Mutant* ContainerLogic::getClosest( std::list<Mutant*>& list,const Ogre::Real& theta, const Ogre::Real& radius, Mutant* mutant, bool abs, bool higher)
{
	Real closestDistance = numeric_limits<Real>::max();
	Mutant* closestLegalMutant = nullptr;
	for (const auto& itt : list)
	{
		if (! float_compare( itt->getPolarCoordinates().radius, radius, LaneSettings::getSingleton().getIncrement() ) || itt == mutant)
			continue;
		Real distance = _getDistance(abs, theta, itt, higher);
		auto result = _checkDistance(distance, closestDistance, itt);
		if (result.first)
		{
			if (!result.second)
				return getClosest(list, theta, radius, mutant, abs, higher);
			else
				closestLegalMutant = result.second;
		}
	}
	return closestLegalMutant;
}
std::pair<bool, Mutant*> ContainerLogic::_checkDistance(const Ogre::Real& distance, Ogre::Real& closestDistance, Mutant* itt)
{
    if (distance > 0.0 && distance < closestDistance)
    {
        closestDistance = distance;
		return{ true, itt };
    }
    else if (float_compare(distance,Real(0.0)))
    {
        itt->setSelectionThetaOffset(EPSILON);
		return{ true, nullptr };
    }
	return{ false, nullptr };
}
Ogre::Real ContainerLogic::_getDistance(bool abs, const Ogre::Real& theta, Mutant* itt, bool higher)
{
	Real distance;
	const Ogre::Real& selectionTheta = itt->getSelectionTheta();
	if (!abs)
		distance = (higher ? selectionTheta : theta) - (higher ? theta : selectionTheta);
	else
		distance = Math::Abs(selectionTheta-theta);
    return distance;
}