#pragma once
#include "PlayerHandlerStateSelectionLine.h"
class Mutant;
class PolarCoordinates;
class PlayerHandlerStateSelectionHandler
{
public:
	PlayerHandlerStateSelectionHandler(const std::vector<std::string>& attackList);
	~PlayerHandlerStateSelectionHandler();
	void handleIndex(const OIS::KeyEvent&);
	void changeIndex(bool right);
	bool updateMarked(const PolarCoordinates& currentNode);
	const std::string& getMarked()const ;
	int getEnergyCostOfMarked() const;
	void addLine();
	bool isInList(const std::string& elm);
private:
	const std::vector<std::string>& m_attackListConst;
	Mutant* m_currentMarked;
	Mutant* m_prevMarked;
	const Ogre::Real* m_currentTheta;
	int m_energyCostOfCurrentlyMarked;
	PlayerHandlerStateSelectionLine m_selectionLine;

	void cycleTheta();
};

