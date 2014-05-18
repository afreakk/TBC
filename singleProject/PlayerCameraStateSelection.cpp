#include "stdafx.h"
#include "PlayerCameraStateSelection.h"
#include "ModelHandlerMutant.h"
#include "MutantContainer.h"
#include "MainUpdate.h"
#include "PlayerContainer.h"
#include "Player.h"
PlayerCameraStateSelection::PlayerCameraStateSelection() 
: m_lookAt(Vector3::ZERO)
{
}


PlayerCameraStateSelection::~PlayerCameraStateSelection()
{
}
#include "UnitCircleMovement.h"
void PlayerCameraStateSelection::update()
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	PolarCoordinates leftOfPlayer = PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates();
	leftOfPlayer.theta -= 0.2f;
	Ogre::Vector3 leftOfPlayerVec = UnitCircleMovement::VectorFromPolar(leftOfPlayer);
	m_camera->setPosition(Math::lerp(m_camera->getPosition(), leftOfPlayerVec*1.2f+Vector3(0,2400,0),dt));
	for (const auto& mutant : MutantContainer::getSingleton().getMutantIt())
	{
		ModelHandlerMutant& mutantModelHandler = static_cast<ModelHandlerMutant&>(mutant->getModelHandler());
		if (mutantModelHandler.isHovered())
		{
			m_lookAt = Math::lerp(m_lookAt, mutant->getModelHandler().getNode()->getPosition(), dt);
		}
	}
	if (!m_lookAt.isZeroLength())
		m_camera->lookAt(m_lookAt);
}
