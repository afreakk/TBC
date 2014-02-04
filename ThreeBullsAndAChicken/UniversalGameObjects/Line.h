#pragma once
#include "stdafx.h"
#include "boost/noncopyable.hpp"
class Line 
{
public:
	Line(Node* start, Node* end);
	void newNode(Node* end);
	void update();
	~Line();
private:
	Ogre::ManualObject* myManualObject;
	Ogre::MaterialPtr myManualObjectMaterial;
	Node* m_start;
	Node* m_end;
};

