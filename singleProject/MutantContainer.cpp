#include "stdafx.h"
#include "MutantContainer.h"
#include "PlayerGlobalStats.h"
#include "MainUpdate.h"
template<> MutantContainer* Ogre::Singleton<MutantContainer>::msSingleton = 0;
static const unsigned energyPerMutant = 10;
MutantContainer::MutantContainer()
: m_despawnTime(2.0)
{
	m_listsToBeCompensated.push_back(&m_toBeKilled);
}
MutantContainer::~MutantContainer()
{}
void MutantContainer::killMutantPlayer(unsigned id)
{
	PlayerGlobalStats::getSingleton().modifyEnergy(energyPerMutant);
	killMutant(id);
}
void MutantContainer::killMutant(unsigned id)
{
	m_toBeKilled.push_back(id);
}
void MutantContainer::moveMutant(unsigned id)
{
    auto handler = m_handlers.begin() + id;
    auto mutant = m_mutants.begin() + id;
	(*handler)->switchState(MUTANT_HANDLER_STATE::DEAD);
	m_deadMutant.emplace_back(new mutantCarcas());
	m_deadMutant.back()->handler = std::move(*handler);
	m_deadMutant.back()->mutant = std::move(*mutant);
	m_handlers.erase(handler);
	m_mutants.erase(mutant);
	compensateLists(id);
}
void MutantContainer::addMutant(MutantHandler* mutantHandler, Mutant* mutant)
{
    m_handlers.push_back(unique_ptr<MutantHandler>(mutantHandler));
    m_mutants.push_back(unique_ptr<Mutant>(mutant));
}
void MutantContainer::sortByDistance(Vector3 playerPos)
{
    std::vector<unsigned> indexes;
    for (unsigned i = 0; i < m_mutants.size(); i++)
    {
        auto distance = m_mutants[i]->getNode()->getPosition().distance(playerPos);
        m_mutants[i]->distance = distance;
        m_handlers[i]->distance = distance;
    }
	std::sort(m_handlers.begin(), m_handlers.end(), [](const unique_ptr<MutantHandler>& a, const unique_ptr<MutantHandler>& b) 
		-> bool	{		return a->distance < b->distance;	});
	std::sort(m_mutants.begin(), m_mutants.end(), [](const unique_ptr<Mutant>& a, const unique_ptr<Mutant>& b) 
		-> bool	{		return a->distance < b->distance;	});
}
const std::vector<unique_ptr<Mutant>>& MutantContainer::getMutants() const
{
    return m_mutants;
}
std::vector<unique_ptr<Mutant>>& MutantContainer::getMutants()
{
    return m_mutants;
}
std::vector<unique_ptr<Mutant>>& MutantContainer::getAndSortMutants(Vector3 pos)
{
    sortByDistance(pos);
    return m_mutants;
}
int MutantContainer::getIndexOf(Ogre::SceneNode* node)
{
	int idx = -1;
	unsigned i = 0;
	for (const auto& mutant : m_mutants)
	{
		if (mutant->getNode() == node)
            idx = i;
		i++;
	}
	return idx;
}
void MutantContainer::update()
{
	for (unsigned i = 0; i < m_handlers.size(); i++)
	{
        m_handlers[i]->update();
	}
	for (unsigned i = 0; i< m_mutants.size(); i++)
	{
		m_mutants[i]->update();
	}
	if (m_toBeKilled.size()>0)
	{
        for (auto it : m_toBeKilled)
            moveMutant(it);
		m_toBeKilled.clear();
	}
	if (m_deadMutant.size() > 0)
		handleDeadMutants();
}

void MutantContainer::compensateThis(std::vector<unsigned>* attackList)
{
    m_listsToBeCompensated.push_back(attackList);
}
void MutantContainer::unCompensateThis(std::vector<unsigned>* attackList)
{
	auto m = std::find(m_listsToBeCompensated.begin(), m_listsToBeCompensated.end(), attackList);
	if (m != m_listsToBeCompensated.end())
		m_listsToBeCompensated.erase(m);
}
void MutantContainer::compensateLists(unsigned killedIndex)
{
	for (auto it : m_listsToBeCompensated)
		compensateAttackList(killedIndex, it);
}   
void MutantContainer::handleDeadMutants()
{
    int toDespawn = -1;
    unsigned i = 0;
    for (auto& deadMut : m_deadMutant)
    {
        deadMut->handler->update();
        deadMut->mutant->update();
        deadMut->time += MainUpdate::getSingleton().getDeltaTime();
        if (deadMut->time > m_despawnTime)
            toDespawn = i;
        i++;
    }
    if (toDespawn != -1)
        m_deadMutant.erase(m_deadMutant.begin() + toDespawn);
}
#include "ModelHandlerMutant.h"
int MutantContainer::getClosestMutant(PolarCoordinates pos, NormalDirection direction)
{
	Real closesDistance = 100000.0;
	int idx = -1;
	keepWithinMax(&pos.r);
    switch (direction)
    {
		case NormalDirection::dirRight:
			for (unsigned i = 0; i < m_mutants.size(); i++)
				checkDistance(pos, i, &closesDistance, &idx,false);
			break;
		case NormalDirection::dirLeft:
			for (unsigned i = 0; i < m_mutants.size(); i++)
				checkDistance(pos, i, &closesDistance, &idx,true);
			break;
		case NormalDirection::None:
			break;
		default:
			assert(0);
			break;
    }
	return idx;
}

void MutantContainer::checkDistance(const PolarCoordinates& pos, unsigned i, Ogre::Real* closestDistance , int* idx, bool left)
{
	Mutant* mutant = m_mutants[i].get();
    PolarCoordinates mutantPos = mutant->getPolarCoordinates();
    bool skipDistanceCheck = (static_cast<ModelHandlerMutant&>(mutant->getModelHandler()).getWeaponType() == WeaponType::SUICIDE_BOMB);
    if (hitTestSide(left?mutantPos:pos,left?pos:mutantPos,closestDistance, skipDistanceCheck))
        *idx = i;
}

void MutantContainer::compensateAttackList(unsigned killedIndex, std::vector<unsigned>* toBeKilledList )
{
	for (auto& itt : *toBeKilledList)
	{
		if (killedIndex < itt)
			itt--;
	}
}