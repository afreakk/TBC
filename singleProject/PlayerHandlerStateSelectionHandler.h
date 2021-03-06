#pragma once
#include "ENUMNormalDirection.h"
class Mutant;
class PolarCoordinates;
class PlayerHandlerStateSelectionHandler
{
public:
	PlayerHandlerStateSelectionHandler(const std::vector<std::string>& attackList);
	~PlayerHandlerStateSelectionHandler();
	void handleKeys(const OIS::KeyEvent&);
	bool updateMarked(const Vector3& markedVec3);
	const std::string& getMarked()const ;
	Mutant* getCurrentMarkedMutant() const;
	int getEnergyCostOfMarked() const;
	bool isInList(const std::string& elm);
private:
	const std::vector<std::string>& m_attackListConst;
	Mutant* m_currentMarked;
	Mutant* m_prevMarked;
	int m_energyCostOfCurrentlyMarked;
	int m_laneIdx;

	void changeMarkedMutant(bool right, bool horizontal=true, bool up=false);
	const Ogre::Real getTheta(Mutant* currentMarked,NormalDirection directionOverflow=NormalDirection::None) const;
	Mutant* getNewMarkedMutant(bool right, Mutant* currentMarked, bool horizontal, unsigned mutantWasInListCount=0,NormalDirection directionOverflow=NormalDirection::None
		, unsigned spunAroundCount=0);
	void changeLaneIdx(bool up);

      
};

