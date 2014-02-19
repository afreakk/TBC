#pragma once
#include "Mutant.h"
#include "MutantHandler.h"
#include "simpleUtils.h"
struct mutantCarcas
{
	unique_ptr<MutantHandler> handler;
	unique_ptr<Mutant> mutant;
	Real time;
	mutantCarcas() : handler(nullptr), mutant(nullptr), time(0.0)
	{}
};
class MutantContainer : public Singleton<MutantContainer>
{
public:
	MutantContainer();
    ~MutantContainer();
	void killMutantPlayer(unsigned id);
	void killMutant(unsigned id);
    // returns -1 if not found
	int getIndexOf(Ogre::SceneNode* node);
    void addMutant(MutantHandler* mutantHandler, Mutant* mutant);
    const std::vector<unique_ptr<Mutant>>& getMutants() const;
    std::vector<unique_ptr<Mutant>>& getMutants();
    std::vector<unique_ptr<Mutant>>& getAndSortMutants(Vector3 pos);
	int getClosestMutant(PolarCoordinates pos, NormalDirection direction);
    void update();
	void compensateThis(std::vector<unsigned>* attackList);
	void unCompensateThis(std::vector<unsigned>* attackList);
private:
	Ogre::Real m_despawnTime;
	std::vector<unique_ptr<MutantHandler>> m_handlers;
	std::vector<unique_ptr<Mutant>> m_mutants;

	std::vector<unique_ptr<mutantCarcas>> m_deadMutant;
	std::vector<unsigned> m_toBeKilled;

	std::vector< std::vector<unsigned>* > m_listsToBeCompensated;

	void handleDeadMutants();
	void checkDistance(const PolarCoordinates& pos, unsigned i, Ogre::Real* closestDistance , int* idx, bool left);
	void moveMutant(unsigned id);
    void sortByDistance(Vector3 playerPos);
	void compensateLists(unsigned killedIndex);
	static void compensateAttackList(unsigned killedIndex, std::vector<unsigned>* toBeKilledList );

};
