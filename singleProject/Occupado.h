#pragma once
class PolarCoordinates;
class BehaviourObject;
const Ogre::Real NormalModeModelSpacing = Math::PI/1024.0;
const Ogre::Real LerpModeSpacing = 200.0;
class Occupado
{
public:
	static bool isOccupiedVelocity(const PolarCoordinates&, const Ogre::Real& velocity);
	static bool isOccupiedWidth(const PolarCoordinates&, const Ogre::Real& width=NormalModeModelSpacing);
	//static Ogre::Vector3 safeTranslate(Ogre::Node* node, const Ogre::Real& velocity);
private:
	//static std::pair<bool,Ogre::Real> hitTest(BehaviourObject* it, const Ogre::Node* node);
	static bool hitTestVelocity(const BehaviourObject* it, const PolarCoordinates& e, const Ogre::Real& aspiringTheta);
	static bool hitTestWidth(const BehaviourObject* it, const PolarCoordinates& e, const Ogre::Real& width);
};

