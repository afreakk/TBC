#include "stdafx.h"
#include "MutantNumber.h"


MutantNumber::MutantNumber(SceneNode* node)
: m_modelNode(node)
, m_fontNode(m_modelNode->createChildSceneNode())
, m_numberText(nullptr)
, m_marked(false)
{
}


MutantNumber::~MutantNumber()
{
}

void MutantNumber::markAs(int number)
{
	unMarkNumber();
	m_numberText = unique_ptr<MovableText> (  new MovableText("lol", boost::lexical_cast<string>(number),"StarWars",100.0f) ) ;
	m_fontNode->attachObject(m_numberText.get());
	m_marked = true;
}

void MutantNumber::unMarkNumber()
{
	if (m_numberText)
		m_numberText->detachFromParent();
}
