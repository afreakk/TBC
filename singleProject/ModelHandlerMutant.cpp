#include "stdafx.h"
#include "ModelHandlerMutant.h"

#include "OgreCore.h"
#include "ModelRecipeMutant.h"
#include "GlobalVariables.h"
#include "MutantGlobalStats.h"
using namespace Ogre;
ModelHandlerMutant::ModelHandlerMutant(PolarCoordinates normalPos)
: ModelHandler(new ModelRecipeMutant(), normalPos)
, m_selectedTag(m_node)
, m_bloodSplat(m_node, this)
, m_flameThrower(m_node, this)
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
	m_bloodSplat.setDirection(direction);
	m_bloodSplat.activate();
}
void ModelHandlerMutant::fire()
{
	m_flameThrower.activate();
}
void ModelHandlerMutant::setHovered(bool selected)
{
	m_hovered = selected;
	if (m_hovered)
		m_selectedTag.select();
}