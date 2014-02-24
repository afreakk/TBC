#pragma once
class SimpleShadow
{
public:
	SimpleShadow(Ogre::SceneNode* parentNode);
	void create(const Ogre::Vector3& pos=Vector3::ZERO);
	void setPosition(const Ogre::Vector3& pos);
	void setZ(const Ogre::Real& zPos);
	bool isCreated();
private:
	Ogre::BillboardSet* m_billboardSet;
	std::unique_ptr<Ogre::Billboard> m_billboard;
	Ogre::SceneNode* m_parentNode;
	bool m_isCreated;
};