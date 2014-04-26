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
	std::vector<Ogre::Light*> m_roofLigths;
	Ogre::Real time;
	Ogre::Light* m_dirLight;
};

