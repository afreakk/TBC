#pragma once
#include "OgreSingleton.h"
class ParticleEffect;
class ParticleReferenceContainer : public Ogre::Singleton<ParticleReferenceContainer>
{
public:
	ParticleReferenceContainer();
	~ParticleReferenceContainer();
	void addParticle(ParticleEffect * prtEffect);
    void removeParticle(ParticleEffect* prtEffect);
    void update();
private:
	std::vector<ParticleEffect* > m_prtEffects;

};

