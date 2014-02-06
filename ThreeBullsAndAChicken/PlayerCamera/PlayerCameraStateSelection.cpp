#include "stdafx.h"
#include "PlayerCameraStateSelection.h"
#include "../ModelBehaviour/ModelHandlerMutant.h"
#include "../Containers/MutantContainer.h"
#include "../GameLevels/MainUpdate.h"
PlayerCameraStateSelection::PlayerCameraStateSelection() 
: m_mutants(MutantContainer::getSingleton().getMutants())
, m_camera(OgreCore::getSingleton().getCamera())
, m_lookAt(Vector3::ZERO)
{
}


PlayerCameraStateSelection::~PlayerCameraStateSelection()
{
}

void PlayerCameraStateSelection::update()
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	for (const auto& mutant : m_mutants)
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
