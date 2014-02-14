#include "stdafx.h"
#include "MutantContainer.h"
#include "PlayerGlobalStats.h"
static const unsigned energyPerMutant = 10;
MutantContainer::MutantContainer()
{}
MutantContainer::~MutantContainer()
{}
void MutantContainer::killMutant(unsigned id)
{
	PlayerGlobalStats::getSingleton().modifyEnergy(energyPerMutant);
    auto handler = m_handlers.begin() + id;
    auto mutant = m_mutants.begin() + id;
	m_handlers[id]->switchState(MUTANT_HANDLER_STATE::DEAD);
    m_deadHandlers.push_back(std::move(*handler));
    m_deadMutants.push_back(std::move(*mutant));
	m_handlers.erase(handler);
	m_mutants.erase(mutant);
}
void MutantContainer::removeKilledMutants()
{
    vectorRemoveNulls<unique_ptr<Mutant> > (&m_mutants);
    vectorRemoveNulls<unique_ptr<MutantHandler>  >(&m_handlers);
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
    std::sort(m_handlers.begin(), m_handlers.end(), handlerSort);
    std::sort(m_mutants.begin(), m_mutants.end(), mutantSort);
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
void MutantContainer::update()
{
    for (auto& handler : m_handlers)
    {
        if (handler)
            handler->update();
    }
    for (auto& mutant : m_mutants)
    {
        if (mutant)
            mutant->update();
    }
    for (auto& deadHandler : m_deadHandlers)
        deadHandler->update();
    for (auto& deadMutant : m_deadMutants)
        deadMutant->update();
}
int MutantContainer::getClosestMutant(PolarCoordinates pos, NormalDirection direction)
{
	Real closesDistance = 100000.0;
	int idx = -1;
	unsigned i = 0;
	keepWithinMax(&pos.r);
	Real rr = 999999999;
    switch (direction)
    {
		case NormalDirection::dirRight:
            for (const auto& mutant : m_mutants)
            {
                PolarCoordinates mutantPos = mutant->getPolarCoordinates();
				keepWithinMax(&mutantPos.r);
                Real distance = mutantPos.r - pos.r;
                if (mutantPos.r> pos.r && distance < closesDistance)
                {
                    idx = i;
                    closesDistance = distance;
					rr = mutantPos.r;

                }
				i++;
            }
			break;
		case NormalDirection::dirLeft:
            for (const auto& mutant : m_mutants)
            {
                PolarCoordinates mutantPos = mutant->getPolarCoordinates();
				keepWithinMax(&mutantPos.r);
                Real distance = pos.r-mutantPos.r;
                if (mutantPos.r < pos.r && distance < closesDistance)
                {
                    idx = i;
                    closesDistance = distance;
					rr = mutantPos.r;
                }
				i++;
            }
			break;
		case NormalDirection::None:
			break;
		default:
			assert(0);
			break;
    }
	std::cout << pos.r << endl;
	std::cout << rr << endl;
	return idx;
}