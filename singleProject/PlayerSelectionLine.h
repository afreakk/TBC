#pragma once
#include "StapledLine.h"
#include "boost/noncopyable.hpp"
class PlayerSelectionLine : public boost::noncopyable
{
public:
	PlayerSelectionLine(Ogre::Node* baseNode, const Ogre::Real& spacing);
	~PlayerSelectionLine();
	void addNode(Ogre::Node* node);
	void update(const Ogre::Real& energyCostScale);
	void updateBack(Ogre::Node* node);
private:
	std::vector<std::unique_ptr<StapledLine>> m_lines;
	std::vector<Ogre::Node*> m_nodes;
	Ogre::Real m_spacing;
};

