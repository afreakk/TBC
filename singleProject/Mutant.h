#pragma once
#include "BehaviourObject.h"
#include "Distancer.h"
class Mutant : public BehaviourObject, public Distancer
{
public:
	Mutant(const PolarCoordinates pos);
	~Mutant();

};

