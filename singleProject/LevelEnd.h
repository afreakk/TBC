#pragma once
#include "ILevel.h"
class LevelEnd : public ILevel
{
public:
	LevelEnd();
	~LevelEnd();
	virtual bool update() override;
private:
	Gorilla::Rectangle* m_rBackground;
	Gorilla::Screen* m_screen;
	Gorilla::Layer* m_layer;
	Ogre::Real m_time;
};

