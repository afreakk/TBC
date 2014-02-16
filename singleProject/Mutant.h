#pragma once
#include "BehaviourObject.h"
#include "Distancer.h"
#include "Weapon.h"
class Mutant : public BehaviourObject, public Distancer
{
public:
	Mutant(const PolarCoordinates pos, WeaponType weaponType, ModelRecipe* modelRecipe);
	~Mutant();

};

