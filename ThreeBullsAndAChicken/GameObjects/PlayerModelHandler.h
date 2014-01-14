#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

class PlayerModelHandler
{
public:
	PlayerModelHandler();
	~PlayerModelHandler();
	void init(const Ogre::Real& r, const Ogre::Real& d, const Ogre::Real& h);
	void normalTranslate(const Ogre::Real& rInc);
	Ogre::SceneNode* getNode();
private:
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr);
	Ogre::SceneNode* initPlayerNode(Ogre::SceneManager* sMgr, Ogre::Entity* playerEntity);
	void normalSetPosition();

	Ogre::Entity* m_playerEntity;
	Ogre::SceneNode* m_playerNode;
	Ogre::Real m_rad;
	Ogre::Real m_dist;
	Ogre::Real m_height;
};

