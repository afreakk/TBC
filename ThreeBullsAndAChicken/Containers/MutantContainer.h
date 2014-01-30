#pragma once
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourObjectHandler/MutantHandler.h"
class MutantContainer : public Singleton<MutantContainer>
{
public:
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
	void addMutant(MutantHandler* mutantHandler, Mutant* mutant)
	{
		m_handlers.push_back(unique_ptr<MutantHandler>(mutantHandler));
		m_mutants.push_back(unique_ptr<Mutant>(mutant));
	}
	const std::vector<unique_ptr<Mutant>>& getMutants() const
	{
		return m_mutants;
	}
	std::vector<unique_ptr<Mutant>>& getMutants()
	{
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