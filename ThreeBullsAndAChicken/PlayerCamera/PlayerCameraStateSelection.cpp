#include "stdafx.h"
#include "PlayerCameraStateSelection.h"
#include "../Enemy/EnemyHandler.h"

PlayerCameraStateSelection::PlayerCameraStateSelection()
{
}


PlayerCameraStateSelection::~PlayerCameraStateSelection()
{
}

void PlayerCameraStateSelection::update()
{
	auto mutants = EnemyHandler::getSingleton().getMutants();
	for (auto& mutant : mutants)
	{
		if (mutant.getModelHandler().isSelected())
		{
			m_camera->lookAt(mutant.getModelHandler().getNode()->getPosition());
		}
	}

}
void PlayerCameraStateSelection::init(SceneNode* playerNode)
{
	m_camera = OgreCore::getSingletonPtr()->getCamera();
}
void PlayerCameraStateSelection::exit()
{

}