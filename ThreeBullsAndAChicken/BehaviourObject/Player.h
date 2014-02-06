#pragma once
#include "stdafx.h"
#include "../BehaviourObject/BehaviourObject.h"
class Player : public BehaviourObject
{
public:
	Player(PolarCoordinates coordinate);
	~Player();
};

