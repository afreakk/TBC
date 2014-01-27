#pragma once
#include "stdafx.h"
#include "../Enemy/Mutant.h"
class MutantHandler : public boost::noncopyable
{
public:
	MutantHandler( PolarCoordinates pos, SceneNode* playerNode );
	~MutantHandler();
	void update();
	const Mutant& getMutant() const
	{
		return m_mutant;
	}
	Mutant& getMutant() 
	{
		return m_mutant;
	}
private:
	Mutant m_mutant;
};


