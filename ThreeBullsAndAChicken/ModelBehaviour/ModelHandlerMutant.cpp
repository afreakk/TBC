#include "stdafx.h"
#include "ModelHandlerMutant.h"

#include "../OgreCore/OgreCore.h"
#include "ModelRecipeMutant.h"
using namespace Ogre;
ModelHandlerMutant::ModelHandlerMutant(PolarCoordinates normalPos) 
: ModelHandler(new ModelRecipeMutant(), normalPos)
, m_selectedTag(m_node)
, m_marked(false)
, m_selected(false)
, m_numberText(nullptr)
{
	markSelected(false);
}
ModelHandlerMutant::~ModelHandlerMutant()
{
	cout << "ModelHandlerMutant destrucotr" << endl;
}

void ModelHandlerMutant::markAs(int number)
{
	m_numberText.reset();
	m_numberText = unique_ptr<MovableText> (  new MovableText("lol", boost::lexical_cast<string>(number),"StarWars",100.0f) ) ;
	auto fontNode = m_node->createChildSceneNode();
	fontNode->setPosition(m_node->getPosition() + Vector3(0, 275, 0));
	fontNode->attachObject(m_numberText.get());
	cout << fontNode->getPosition() << endl;
	cout << m_node->getPosition() << endl;
	m_marked = true;
}

void ModelHandlerMutant::unMarkNumber()
{
	if (m_numberText)
		m_numberText->detachFromParent();
}
void ModelHandlerMutant::markSelected(bool selected)
{
	m_selected = selected;
	if (m_selected)
		m_selectedTag.select();
}