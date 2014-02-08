#include "stdafx.h"
#include "ParticleReferenceContainer.h"

#include "../UniversalGameObjects/ParticleEffect.h"

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
    for (auto p = m_prtEffects.begin(); p != m_prtEffects.end(); ++p)
    {
        if (*p == prtEffect)
        {
            m_prtEffects.erase(p);
            return;
        }
    }
    assert(0);
}
void ParticleReferenceContainer::update()
{
    for (auto& prtEffect : m_prtEffects)
        prtEffect->update();
}