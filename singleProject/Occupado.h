#pragma once
class PolarCoordinates;
class BehaviourObject;
class Occupado
{
public:
	static bool isOccupied(PolarCoordinates&, const Ogre::Real& velocity);
private:
	static bool hitTest(const BehaviourObject* it, const PolarCoordinates& e, const Ogre::Real& aspiringTheta);
};

