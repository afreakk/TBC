#pragma once
namespace Ogre
{
	class Light;
}
class LightHandler
{
public:
	LightHandler();
	~LightHandler();
	void update();
private:
	Ogre::Light* directionalLight;
	Ogre::Real time;
};

