#pragma once
#include "stdafx.h"
#include "LevelListing.h"
class ILevel : public boost::noncopyable
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


