#pragma once
class Mutant;
class ContainerLogic
{
public:
	static Mutant* getClosest(std::list<Mutant*>& list, const Ogre::Real& theta, Mutant* mutant, bool abs, bool higher);
	static Mutant* getClosest(std::list<Mutant*>& list,const Ogre::Real& theta, const Ogre::Real& radius, Mutant* mutant, bool abs, bool higher);
private:
	static Ogre::Real _getDistance(bool abs, const Ogre::Real& theta, Mutant* itt, bool higher);
	static std::pair<bool, Mutant*> _checkDistance(const Ogre::Real& distance, Ogre::Real& closestDistance,  Mutant* itt);
};

