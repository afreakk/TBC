#pragma once
#include "PlayerHandlerStateSelectionLine.h"
class Mutant;
class PolarCoordinates;
class PlayerHandlerStateSelectionHandler
{
public:
	PlayerHandlerStateSelectionHandler(Vector3 playerPos, const std::vector<unsigned>& attackList);
	~PlayerHandlerStateSelectionHandler();
	void handleIndex(const OIS::KeyEvent&);
	void changeIndex(int iVel);
	void extremeChangeIndex(int iVel, int move=0);
	void updateMarked(PolarCoordinates currentNode);
	int getMarked()const ;
	int getEnergyCostOfMarked() const;
	void addLine();
private:
	const std::vector<unsigned>& m_attackListConst;
	std::vector<unique_ptr<Mutant>>&  m_mutants;
	int m_markedIndex;
	int m_lastMarkedIndex;
	int m_energyCostOfCurrentlyMarked;
	PlayerHandlerStateSelectionLine m_selectionLine;
	bool isInList(int elm);
};

