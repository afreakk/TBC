#pragma once
#include "boost/noncopyable.hpp"
namespace ParticleUniverse
{
	class ParticleSystem;
}
class ParticleEffect : public boost::noncopyable
{
public:
	ParticleEffect(SceneNode* parentNode, const int id, const Ogre::String & 	name, const Ogre::String & 	templateName, Ogre::SceneManager * 	sceneManager);
	virtual~ParticleEffect();
	virtual void update();
	virtual void activate();
protected:
	const int m_id;
	bool m_added;
	Ogre::SceneManager* m_sMgr;
	SceneNode* m_node;
	ParticleUniverse::ParticleSystem* m_particleSystem;

	void setParticleSystem(bool enabled);
	void stop();
	void destroyThis();
};

