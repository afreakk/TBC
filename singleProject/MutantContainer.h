#pragma once
#include "Mutant.h"
#include "MutantHandler.h"
#include "simpleUtils.h"
class MutantContainer : public Singleton<MutantContainer>
{
public:
    //sort by distance 
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
    //end sortbydistance
	MutantContainer();
    ~MutantContainer();
	void killMutant(unsigned id);
    void removeKilledMutants();
    void addMutant(MutantHandler* mutantHandler, Mutant* mutant);
    void sortByDistance(Vector3 playerPos);
    const std::vector<unique_ptr<Mutant>>& getMutants() const;
    std::vector<unique_ptr<Mutant>>& getMutants();
    std::vector<unique_ptr<Mutant>>& getAndSortMutants(Vector3 pos);
	int getClosestMutant(PolarCoordinates pos, NormalDirection direction);
    void update();
private:
	std::vector<unique_ptr<MutantHandler>> m_handlers;
	std::vector<unique_ptr<Mutant>> m_mutants;

	std::vector<unique_ptr<MutantHandler>> m_deadHandlers;
	std::vector<unique_ptr<Mutant>> m_deadMutants;

};

template<> MutantContainer* Ogre::Singleton<MutantContainer>::msSingleton = 0;