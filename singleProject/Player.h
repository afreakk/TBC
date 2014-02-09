#pragma once
#include "BehaviourObject.h"
class Player : public BehaviourObject
{
public:
	Player(PolarCoordinates coordinate);
	~Player();
};

