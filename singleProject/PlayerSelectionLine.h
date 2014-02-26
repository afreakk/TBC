#pragma once
#include "StapledLine.h"
#include "boost/noncopyable.hpp"
#include "BillboardNumber.h"
class PlayerSelectionLine : public boost::noncopyable
{
public:
	PlayerSelectionLine(Ogre::Node* baseNode, const Ogre::Real& spacing);
	~PlayerSelectionLine();
	void addNode(Ogre::Node* node);
	void removeNode(const std::string& name);
	void update(const Ogre::Real& energyCostScale);
	void updateBack(Ogre::Node* node);
private:
	std::vector<std::pair<std::unique_ptr<StapledLine>,std::unique_ptr<BillboardNumber>>> m_lines;
	std::vector<std::pair<std::string,Ogre::Node*> > m_nodes;
	Ogre::Real m_spacing;

	void pushBack(Ogre::Node*);
	std::vector<std::pair<std::string, Ogre::Node*> >::iterator findElement(const std::string& name);
};

