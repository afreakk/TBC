#pragma once
#include "stdafx.h"
class PlayerCameraState : boost::noncopyable
{
public:
	virtual ~PlayerCameraState()
	{
	}
	virtual void update()=0;
};

