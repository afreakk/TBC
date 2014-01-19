#include "stdafx.h"
#include "MutantModelHandler.h"

#include "../OgreCore/OgreCore.h"
#include "boost/lexical_cast.hpp"
#include "MutantRecipe.h"
using namespace Ogre;
MutantModelHandler::MutantModelHandler() :UniversalModelHandler(new MutantRecipe()), m_marked(false), m_selected(false)
{
	markSelected(false);
}
MutantModelHandler::~MutantModelHandler()
{
}

void MutantModelHandler::markAs(int number)
{
	m_numberText =  new MovableText("lol", boost::lexical_cast<string>(number),"StarWars",100.0f);
	auto fontNode = m_node->createChildSceneNode();
	fontNode->setPosition(m_node->getPosition() + Vector3(0, 275, 0));
	fontNode->attachObject(m_numberText);
	cout << fontNode->getPosition() << endl;
	cout << m_node->getPosition() << endl;
	m_marked = true;
}

void MutantModelHandler::unMarkNumber()
{
	m_numberText->detachFromParent();
	delete m_numberText;
}
void MutantModelHandler::markSelected(bool selected)
{
	m_selected = selected;
	if (m_entity)
	{
		if (selected)
			m_entity->setMaterialName("PlainTexture");
		else
			m_entity->setMaterialName("red");
	}
}