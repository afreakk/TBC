#pragma once
class PillarHider
{
public:
	PillarHider(Ogre::SceneNode* envnode);
	~PillarHider();
	void update();
private:
	Ogre::SceneNode* m_environmentNode;
};

