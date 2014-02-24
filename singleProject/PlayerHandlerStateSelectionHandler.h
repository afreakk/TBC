#pragma once
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
	Mutant* getCurrentMarkedMutant() const;
	int getEnergyCostOfMarked() const;
	bool isInList(const std::string& elm);
private:
	const std::vector<std::string>& m_attackListConst;
	Mutant* m_currentMarked;
	Mutant* m_prevMarked;
	const Ogre::Real* m_currentTheta;
	int m_energyCostOfCurrentlyMarked;

	void cycleTheta();
};

