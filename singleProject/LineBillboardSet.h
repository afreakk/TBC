#pragma once
#include "boost/noncopyable.hpp"
class LineBillboardSet : public boost::noncopyable
{
public:
	LineBillboardSet();
	LineBillboardSet(Ogre::SceneNode* parentNode);
	LineBillboardSet(LineBillboardSet& other);
	~LineBillboardSet();
	Ogre::Billboard* getBillboard(const Ogre::Vector3& pos=Ogre::Vector3::ZERO);
	bool destroyBillboard(Ogre::Billboard* board);
	Ogre::BillboardSet* getSet()
	{
		return m_billboardSet;
	}
	const Ogre::Real& getDimension()
	{
		return m_dimension;
	}
	void setSceneNode(Ogre::SceneNode* node);
private:
	Ogre::BillboardSet* m_billboardSet;
	std::vector<Ogre::Billboard*> m_billboard;
	Ogre::SceneNode* m_sceneNode;
	Ogre::Real m_dimension;
};