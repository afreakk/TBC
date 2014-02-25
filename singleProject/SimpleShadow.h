#pragma once
class SimpleShadow
{
public:
	SimpleShadow(Ogre::SceneNode* parentNode);
	~SimpleShadow();
	void create();
	void setPosition(const Ogre::Vector3& pos);
	void setZ(const Ogre::Real& zPos);
	bool isCreated();
	void setVisible(bool visible);
private:
	Ogre::BillboardSet* m_billboardSet;
	Ogre::Billboard* m_billboard;
	Ogre::SceneNode* m_sceneNode;
	bool m_isCreated;
};