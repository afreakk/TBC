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
			handler->update();
		for (auto& mutant : m_mutants)
			mutant->update();
	}
private:
	std::vector<unique_ptr<MutantHandler>> m_handlers;
	std::vector<unique_ptr<Mutant>> m_mutants;

};

template<> MutantContainer* Ogre::Singleton<MutantContainer>::msSingleton = 0;