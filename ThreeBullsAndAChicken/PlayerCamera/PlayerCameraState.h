#pragma once
#include "stdafx.h"
class PlayerCameraState
{
public:
	virtual void update()=0;
	virtual void init(SceneNode*) = 0;
	virtual void exit() = 0;
};

