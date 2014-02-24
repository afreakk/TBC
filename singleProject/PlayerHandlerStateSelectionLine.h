#pragma once
#include "DynamicTubes.h"
namespace Ogre
{
class SeriesOfTubes;
class SceneNode;
}
class PlayerHandlerStateSelectionLine
{
public:
	PlayerHandlerStateSelectionLine();
	~PlayerHandlerStateSelectionLine();
	void setNewTarget(Ogre::SceneNode* index);
	void addEnemy();
	void update();
private:
	std::unique_ptr<Ogre::SeriesOfTubes> m_tubeObj;
	Ogre::SceneNode* m_tubeParentNode;
	DynamicTubes m_path;
	bool m_addHim;
};

