#pragma once
#include "boost/noncopyable.hpp"
class PlayerCameraState : boost::noncopyable
{
public:
	virtual ~PlayerCameraState()
	{
	}
	virtual void update()=0;
};

