#include "stdafx.h"
#include "ParticleReferenceContainer.h"

#include "ParticleEffect.h"

template<> ParticleReferenceContainer* Ogre::Singleton<ParticleReferenceContainer>::msSingleton = 0;
ParticleReferenceContainer::ParticleReferenceContainer()
{
}


ParticleReferenceContainer::~ParticleReferenceContainer()
{
}

void ParticleReferenceContainer::addParticle(ParticleEffect * prtEffect)
{
    m_prtEffects.push_back(prtEffect);
}
void ParticleReferenceContainer::removeParticle(ParticleEffect* prtEffect)
{
	std::vector<ParticleEffect*>::iterator deleteIterator = m_prtEffects.end();
    for (auto p = m_prtEffects.begin(); p != m_prtEffects.end(); ++p)
    {
        if (*p == prtEffect)
        {
			deleteIterator = p;
			break;
        }
    }
	if (deleteIterator != m_prtEffects.end())
		m_prtEffects.erase(deleteIterator);
	else
        assert(0);
}
void ParticleReferenceContainer::update()
{
    //todo: when weapon hits mutant and switches hit mutant state to dead "itterator not itterable" for next ->update()
    // for loop works though,, why lol
	for (unsigned i = 0; i < m_prtEffects.size(); i++)
		m_prtEffects[i]->update();
}