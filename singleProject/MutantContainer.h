#pragma once
#include "Mutant.h"
#include "MutantHandler.h"
#include "simpleUtils.h"
class MutantContainer : public Singleton<MutantContainer>
{
public:
	struct {
		bool operator()(const unique_ptr<MutantHandler>& a, const unique_ptr<MutantHandler>& b)
		{
			return a->distance < b->distance;
		}
	} handlerSort;
	struct {
		bool operator()(const unique_ptr<Mutant>& a, const unique_ptr<Mutant>& b)
		{
			return a->distance < b->distance;
		}
	} mutantSort;
	MutantContainer()
	{

	}
	~MutantContainer()
	{

	}
	void killMutant(unsigned id)
	{
		auto handler = m_handlers.begin() + id;
		auto mutant = m_mutants.begin() + id;
		(*handler)->switchState(MUTANT_HANDLER_STATE::DEAD);
		m_deadHandlers.emplace_back(std::move(*handler));
		m_deadMutants.emplace_back(std::move(*mutant));
	}
	void removeKilledMutants()
	{
		vectorRemoveNulls<unique_ptr<Mutant> > (&m_mutants);
		vectorRemoveNulls<unique_ptr<MutantHandler>  >(&m_handlers);
	}
	void addMutant(MutantHandler* mutantHandler, Mutant* mutant)
	{
		m_handlers.push_back(unique_ptr<MutantHandler>(mutantHandler));
		m_mutants.push_back(unique_ptr<Mutant>(mutant));
	}
	void sortByDistance(Vector3 playerPos)
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
	const std::vector<unique_ptr<Mutant>>& getMutants() const
	{
		return m_mutants;
	}
	std::vector<unique_ptr<Mutant>>& getMutants()
	{
		return m_mutants;
	}
	std::vector<unique_ptr<Mutant>>& getAndSortMutants(Vector3 pos)
	{
		sortByDistance(pos);
		return m_mutants;
	}
	void update()
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
private:
	std::vector<unique_ptr<MutantHandler>> m_handlers;
	std::vector<unique_ptr<Mutant>> m_mutants;

	std::vector<unique_ptr<MutantHandler>> m_deadHandlers;
	std::vector<unique_ptr<Mutant>> m_deadMutants;

};

template<> MutantContainer* Ogre::Singleton<MutantContainer>::msSingleton = 0;