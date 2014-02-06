#include "stdafx.h"
#include "ModelHandlerMutant.h"

#include "../OgreCore/OgreCore.h"
#include "ModelRecipeMutant.h"
#include "../Stats/GlobalVariables.h"
#include "../Stats/MutantGlobalStats.h"
using namespace Ogre;
ModelHandlerMutant::ModelHandlerMutant(PolarCoordinates normalPos)
: ModelHandler(new ModelRecipeMutant(), normalPos)
, m_selectedTag(m_node)
, m_bloodSplat(m_node)
, m_flameThrower(m_node)
, m_number(m_node)
, m_hovered(false)
{
	setHovered(false);
}
ModelHandlerMutant::~ModelHandlerMutant()
{
	cout << "ModelHandlerMutant destrucotr" << endl;
}

void ModelHandlerMutant::damage(Vector3 direction)
{
	m_bloodSplat.activate(GlobalVariables::getSingleton().getSpeed(),direction);
}
void ModelHandlerMutant::fire()
{
	m_flameThrower.activate(GlobalVariables::getSingleton().getSpeed());
}
void ModelHandlerMutant::setHovered(bool selected)
{
	m_hovered = selected;
	if (m_hovered)
		m_selectedTag.select();
}