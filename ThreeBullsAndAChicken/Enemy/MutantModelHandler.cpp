#include "stdafx.h"
#include "MutantModelHandler.h"

#include "../OgreCore/OgreCore.h"
#include "boost/lexical_cast.hpp"
using namespace Ogre;
MutantModelHandler::MutantModelHandler() :UniversalModelHandler("Mutant", "ninja.mesh", "Walk", "Mutant"), m_marked(false)
{
}
MutantModelHandler::~MutantModelHandler()
{
}

void MutantModelHandler::markAs(int number)
{
	m_numberText =  new MovableText(boost::lexical_cast<string>(m_id), boost::lexical_cast<string>(number),"StarWars",100.0f);
	auto fontNode = m_node->createChildSceneNode();
	fontNode->setPosition(m_node->getPosition() + Vector3(0, 275, 0));
	fontNode->attachObject(m_numberText);
	cout << fontNode->getPosition() << endl;
	cout << m_node->getPosition() << endl;
	m_marked = true;
}