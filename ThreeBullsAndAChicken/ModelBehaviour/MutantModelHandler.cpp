#include "stdafx.h"
#include "MutantModelHandler.h"

#include "../OgreCore/OgreCore.h"
#include "MutantRecipe.h"
using namespace Ogre;
MutantModelHandler::MutantModelHandler(PolarCoordinates normalPos) 
: UniversalModelHandler(new MutantRecipe(), normalPos)
, m_selectedTag(m_node)
, m_marked(false)
, m_selected(false)
, m_numberText(nullptr)
{
	markSelected(false);
}
MutantModelHandler::~MutantModelHandler()
{
	cout << "MutantModelHandler destrucotr" << endl;
}

void MutantModelHandler::markAs(int number)
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

void MutantModelHandler::unMarkNumber()
{
	if (m_numberText)
	{
		m_numberText->detachFromParent();
		m_numberText = nullptr;
	}
}
void MutantModelHandler::markSelected(bool selected)
{
	m_selected = selected;
	if (m_entity)
	{
		if (selected)
		{
			m_entity->setMaterialName("PlainTexture");
			m_selectedTag.select();
		}
		else
		{
			m_entity->setMaterialName("red");
		}
	}
}