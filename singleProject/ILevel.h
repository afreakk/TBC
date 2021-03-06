#pragma once
#include "LevelListing.h"
#include "boost/noncopyable.hpp"
class ILevel : public boost::noncopyable
{
public:
	ILevel(LevelID levelID) :m_levelID(levelID)
	{}
	virtual ~ILevel()
	{}
	virtual bool update()=0;
	const LevelID getID()
	{
		return m_levelID;
	}
protected:
	const LevelID m_levelID;
};


