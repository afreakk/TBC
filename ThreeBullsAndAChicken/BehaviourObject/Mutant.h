#pragma once
#include "stdafx.h"
#include "../BehaviourObject/BehaviourObject.h"
#include "../Templates/Distancer.h"
class Mutant : public BehaviourObject, public Distancer
{
public:
	Mutant(const PolarCoordinates pos);
	~Mutant();

};

