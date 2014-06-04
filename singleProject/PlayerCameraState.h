#pragma once
#include "boost/noncopyable.hpp"
class PlayerCameraState : boost::noncopyable
{
public:
	PlayerCameraState();
	virtual ~PlayerCameraState(){}
	virtual void update()=0;
protected:
	Ogre::Camera* m_camera;
	void setCameraPos(const Ogre::Real& height, const Ogre::Real& distance);
//----
	const Ogre::Vector3& getTiltedLerpedPlayerPos(const Ogre::Real& dt);
private:
	static Ogre::Real m_playerThetaLerp;
	static Ogre::Vector3 m_lerpedPlayerPos;
//----
	Ogre::Real getTiltedPlayerPos();
};

