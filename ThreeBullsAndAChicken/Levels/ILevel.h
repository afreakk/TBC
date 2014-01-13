#pragma once
#include "LevelListing.h"
#include "stdafx.h"
class ILevel
{
public:
	ILevel(LevelID levelID) :m_levelID(levelID)
	{
	}
	virtual bool update()=0;
	const LevelID getID()
	{
		return m_levelID;
	}
protected:
	const LevelID m_levelID;
};


