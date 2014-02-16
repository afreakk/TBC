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
	void killMutant(unsigned id);
    // returns -1 if not found
	int getIndexOf(Ogre::SceneNode* node);
    void removeKilledMutants();
    void addMutant(MutantHandler* mutantHandler, Mutant* mutant);
    void sortByDistance(Vector3 playerPos);
    const std::vector<unique_ptr<Mutant>>& getMutants() const;
    std::vector<unique_ptr<Mutant>>& getMutants();
    std::vector<unique_ptr<Mutant>>& getAndSortMutants(Vector3 pos);
	int getClosestMutant(PolarCoordinates pos, NormalDirection direction);
    void update();
private:
	Ogre::Real m_despawnTime;
	std::vector<unique_ptr<MutantHandler>> m_handlers;
	std::vector<unique_ptr<Mutant>> m_mutants;

	std::vector<unique_ptr<mutantCarcas>> m_deadMutant;
	void handleDeadMutants();

};
