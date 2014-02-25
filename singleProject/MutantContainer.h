#pragma once
#include "Mutant.h"
#include "MutantHandler.h"
#include "simpleUtils.h"
#include "Messager.h"
struct MutantPair
{
	std::unique_ptr<MutantHandler> handler;
	std::unique_ptr<Mutant> mutant;
	Ogre::Real distance;
	Real time;
	MutantPair(MutantHandler* h, Mutant* m) : handler(h), mutant(m), distance(0.0), time(0.0)
	{}
};
class MutantContainer : public Singleton<MutantContainer> , public Messager <std::string>
{
public:
	MutantContainer();
    ~MutantContainer();
	Mutant* getMutant(const std::string& name);
	MutantHandler* getHandler(const std::string& name);
	void killMutantPlayer(const std::string&);
	void killMutant(const std::string&);
    //replaces mutant names in list with killed if they get killed while list is being operated on.
    void addMutant(MutantHandler* mutantHandler, Mutant* mutant);
	Mutant* getClosestHigherThan(const Ogre::Real& theta, Mutant* mutant);
	Mutant* getClosestLowerThan(const Ogre::Real& theta, Mutant* mutant);
	std::string getClosestMutant(PolarCoordinates pos, NormalDirection direction);
	std::list<Mutant*> getMutantIt() { return m_aliveMutantIteratorList; }
	std::list<MutantHandler*> getHandlerIt() { return m_aliveHandlerIteratorList; }
    void update();
	virtual const std::string message() override;
private:
	Ogre::Real m_despawnTime;
	std::map<std::string, MutantPair*> m_aliveMutants;
	std::list<Mutant*> m_aliveMutantIteratorList;
	std::list<MutantHandler*> m_aliveHandlerIteratorList;

	std::map<std::string, MutantPair*> m_deadMutants;
	std::string m_lastDeadMutant;

	std::vector<std::string> m_executedMutants;
	std::vector<std::string> m_toBeKilled;

	Mutant* getClosest(bool higher, const Ogre::Real& theta, Mutant* mutant);
	void handleDeadMutants();
	void executeDoomedMutants();
	bool checkDistance(const PolarCoordinates& pos, Mutant* mutant , Ogre::Real* closestDistance ,  bool left);
	void moveMutant(const std::string& id);
	void updateAliveMutants();
};
