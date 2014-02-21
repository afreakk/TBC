#include "stdafx.h"
#include "MutantContainer.h"
#include "ModelHandlerMutant.h"
#include "PlayerGlobalStats.h"
#include "MainUpdate.h"
template<> MutantContainer* Ogre::Singleton<MutantContainer>::msSingleton = 0;
static const unsigned energyPerMutant = 10;
MutantContainer::MutantContainer()
: m_despawnTime(2.0)
{
}
MutantContainer::~MutantContainer()
{}


const std::string MutantContainer::message()
{
	return m_lastDeadMutant;
}
Mutant* MutantContainer::getMutant(const std::string& name)
{
	auto t = m_aliveMutants.find(name);
	if (t == m_aliveMutants.end())
		return nullptr;
	return t->second->mutant.get();
}
MutantHandler* MutantContainer::getHandler(const std::string& name)
{
	auto t = m_aliveMutants.find(name);
	if (t == m_aliveMutants.end())
		return nullptr;
	return t->second->handler.get();
}
void MutantContainer::killMutantPlayer(const std::string& name)
{
	PlayerGlobalStats::getSingleton().modifyEnergy(energyPerMutant);
	killMutant(name);
}
void MutantContainer::killMutant(const std::string& name)
{
	m_toBeKilled.push_back(name);
}
void MutantContainer::moveMutant(const std::string& id)
{
	MutantPair* pair = m_aliveMutants[id];
	pair->handler->switchState(MUTANT_HANDLER_STATE::DEAD);
	pair->mutant->setDead(true);
	m_deadMutants[id] = pair;
	m_aliveMutantIteratorList.erase( std::find( m_aliveMutantIteratorList.begin(), m_aliveMutantIteratorList.end(), pair->mutant.get() ) );
	m_aliveHandlerIteratorList.erase( std::find( m_aliveHandlerIteratorList.begin(), m_aliveHandlerIteratorList.end(), pair->handler.get() ) );
	m_aliveMutants.erase(id);
	m_lastDeadMutant = id;
	notifySubscribers();

}
void MutantContainer::addMutant(MutantHandler* mutantHandler, Mutant* mutant)
{
	std::string name = mutant->getNode()->getName();
	m_aliveMutants[name] = new MutantPair( mutantHandler, mutant );
	m_aliveMutantIteratorList.push_back(mutant);
	m_aliveHandlerIteratorList.push_back(mutantHandler);
}
Mutant* MutantContainer::getClosestHigherThan(const Ogre::Real& theta)
{
	return getClosest(true, theta);
}
Mutant* MutantContainer::getClosestLowerThan(const Ogre::Real& theta)
{
	return getClosest(false, theta);
}
Mutant* MutantContainer::getClosest(bool higher, const Ogre::Real& theta)
{
	Real closestDistance = 100000.0;
	Mutant* mutPtr = nullptr;
	for (const auto& itt : m_aliveMutantIteratorList)
	{
		Real distance = (higher ? itt->getPolarCoordinates().theta : theta ) - (higher ? theta : itt->getPolarCoordinates().theta );
		if (distance > 0.0 && distance < closestDistance)
		{
			closestDistance = distance;
			mutPtr = itt;
		}
	}
	return mutPtr;
}
void MutantContainer::update()
{
	updateAliveMutants();
	if (m_toBeKilled.size()>0)
		executeDoomedMutants();
	if (m_deadMutants.size()>0)
		handleDeadMutants();
}

void MutantContainer::updateAliveMutants()
{
	for (auto& itt : m_aliveHandlerIteratorList)
	{
        itt->update();
	}
	for (auto& itt : m_aliveMutantIteratorList)
	{
		itt->update();
	}
}
void MutantContainer::executeDoomedMutants()
{
	for (const auto& it : m_toBeKilled)
	{
		if (std::find(m_executedMutants.begin(), m_executedMutants.end(), it) != m_executedMutants.end())
			continue;
		m_executedMutants.push_back(it);
        moveMutant(it);
	}
    m_toBeKilled.clear();
}
void MutantContainer::handleDeadMutants()
{
	std::vector<std::string> toDespawn;
    for (auto& deadMut : m_deadMutants)
    {
        deadMut.second->handler->update();
        deadMut.second->mutant->update();
        deadMut.second->time += MainUpdate::getSingleton().getScaledDeltaTime();
		if (deadMut.second->time > m_despawnTime)
			toDespawn.push_back(deadMut.first);
    }
	for (const auto& it : toDespawn)
	{
//		m_deadMutants[it]->handler.reset();
		// m_deadMutants[it]->mutant.reset(); test when project is in better condition
        m_deadMutants.erase(it);
	}
}
std::string MutantContainer::getClosestMutant(PolarCoordinates pos, NormalDirection direction)
{
	bool left;
    switch (direction)
    {
		case NormalDirection::dirRight:
			left = false;
			break;
		case NormalDirection::dirLeft:
			left = true;
			break;
		case NormalDirection::None:
			assert(0);
			break;
		default:
			assert(0);
			break;
    }
	Real closesDistance = 100000.0;
	std::string idx = "NONE";
	keepWithinMax(&pos.theta);
    for (auto& itt : m_aliveMutantIteratorList)
    {
        if (checkDistance(pos, itt, &closesDistance, left))
            idx = itt->getNode()->getName();
    }
	return idx;
}

bool MutantContainer::checkDistance(const PolarCoordinates& pos, Mutant* mutant , Ogre::Real* closestDistance ,  bool left)
{
    PolarCoordinates mutantPos = mutant->getPolarCoordinates();
    bool skipDistanceCheck = (static_cast<ModelHandlerMutant&>(mutant->getModelHandler()).getWeaponType() == WeaponType::SUICIDE_BOMB);
	if (hitTestSide(left ? mutantPos : pos, left ? pos : mutantPos, closestDistance, skipDistanceCheck))
		return true;
	return false;
}

