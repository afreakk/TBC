#pragma once
class PolarCoordinates;
class BehaviourObject;
class Occupado
{
public:
	static bool isOccupiedVelocity(const PolarCoordinates&, const Ogre::Real& velocity);
	static bool isOccupiedWidth(const PolarCoordinates&, const Ogre::Real& width);
	//static Ogre::Vector3 safeTranslate(Ogre::Node* node, const Ogre::Real& velocity);
private:
	//static std::pair<bool,Ogre::Real> hitTest(BehaviourObject* it, const Ogre::Node* node);
	static bool hitTestVelocity(const BehaviourObject* it, const PolarCoordinates& e, const Ogre::Real& aspiringTheta);
	static bool hitTestWidth(const BehaviourObject* it, const PolarCoordinates& e, const Ogre::Real& width);
};

