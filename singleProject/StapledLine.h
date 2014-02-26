#pragma once
#include "LineBillboardSet.h"
#include "boost/noncopyable.hpp"
class StapledLine  : public boost::noncopyable
{
public:
	StapledLine(Ogre::SceneNode* sceneNode, const Ogre::Real& spacing);
	~StapledLine();
	void setLine(const Ogre::Vector3& from, const Ogre::Vector3& to);
	void setColourScale(const Ogre::Real& scale);
	Ogre::Node* getParentNode();
	void setParentSceneNode(Ogre::SceneNode* sceneNode);
private:
	LineBillboardSet m_set;
	Ogre::Node* m_parentNode;
	std::vector<Ogre::Billboard*> m_billboards;
	unsigned m_numLines;
	Ogre::Real m_colourScale;
	Ogre::Real m_spacing;

	void refresh(unsigned numLines);
	void destroyBillboards(unsigned numLines);
	void getBillboards(unsigned count);
};

