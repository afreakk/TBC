#include "stdafx.h"
#include "MutantContainer.h"
#include "ModelHandlerMutant.h"
#include "PlayerGlobalStats.h"
#include "MainUpdate.h"
#include "LaneSettings.h"
template<> MutantContainer* Ogre::Singleton<MutantContainer>::msSingleton = 0;
static const unsigned energyPerMutant = 10;
MutantContainer::MutantContainer()
: m_despawnTime(2.0)
{
}
MutantContainer::~MutantContainer()
{
	/*  should noe be needed now with shared ptrz
	for (auto& i  : m_deadMutants)
	{
        i.second->handler.reset();
        i.second->mutant.reset(); 
	}
	for (auto& i : m_aliveMutants)
	{
        i.second->handler.reset();
        i.second->mutant.reset(); 
	}*/
}

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
	std::shared_ptr<MutantPair> pair = m_aliveMutants[id];
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
	m_aliveMutants[name] = shared_ptr<MutantPair>(new MutantPair( mutantHandler, mutant ));
	m_aliveMutantIteratorList.push_back(mutant);
	m_aliveHandlerIteratorList.push_back(mutantHandler);
}
Mutant* MutantContainer::getClosestHigherThan(const Ogre::Real& theta, Mutant* mutant)
{
	return getClosest(true, theta, mutant);
}
Mutant* MutantContainer::getClosestLowerThan(const Ogre::Real& theta, Mutant* mutant)
{
	return getClosest(false, theta, mutant);
}
Mutant* MutantContainer::getClosest(bool higher, const Ogre::Real& theta, Mutant* mutant)
{
	Real closestDistance = numeric_limits<Real>::max();
	Mutant* closestLegalMutant = nullptr;
	for (const auto& itt : m_aliveMutantIteratorList)
	{
		if (itt == mutant)
			continue;
		Real distance = (higher ? itt->getSelectionTheta() : theta ) - (higher ? theta : itt->getSelectionTheta() );
		if (distance > 0.0 && distance < closestDistance)
		{
			closestDistance = distance;
			closestLegalMutant = itt;
		}
        else if (float_compare(distance,Real(0.0)))
        {
			itt->setSelectionThetaOffset(EPSILON);
			return getClosest(higher, theta, mutant);
        }
	}
	return closestLegalMutant;
}
Mutant* MutantContainer::getClosest(bool higher, const Ogre::Real& theta, const Ogre::Real& radius, Mutant* mutant)
{
	Real closestDistance = numeric_limits<Real>::max();
	Mutant* closestLegalMutant = nullptr;
	for (const auto& itt : m_aliveMutantIteratorList)
	{
		if (! float_compare( itt->getPolarCoordinates().radius, radius, LaneSettings::getSingleton().getIncrement() ) || itt == mutant)
			continue;
		Real distance = (higher ? itt->getSelectionTheta() : theta ) - (higher ? theta : itt->getSelectionTheta() );
		if (distance > 0.0 && distance < closestDistance)
		{
			closestDistance = distance;
			closestLegalMutant = itt;
		}
        else if (float_compare(distance,Real(0.0)))
        {
			itt->setSelectionThetaOffset(EPSILON);
			return getClosest(higher, theta, mutant);
        }
	}
	return closestLegalMutant;
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
		m_deadMutants[it]->handler.reset();
		m_deadMutants[it]->mutant.reset(); 
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

