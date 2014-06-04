#include "stdafx.h"
#include "BillboardNumber.h"

unsigned BillboardNumber::count = 0;
BillboardNumber::BillboardNumber(SceneNode* node)
: m_parentNode(node->createChildSceneNode(Vector3(0.0,800.0,0.0)))
//, m_numberText(nullptr)
{
}


BillboardNumber::~BillboardNumber()
{
	unMarkNumber();
}

void BillboardNumber::markAs(int number)
{
	if (m_currentNumber == number)
		return;
	m_currentNumber = number;
	unMarkNumber();
//	m_numberText.reset();
//	m_numberText = unique_ptr<MovableText> (  new MovableText("movebletext-#"+boost::lexical_cast<string>(++count), boost::lexical_cast<string>(number),"StarWars",500.0f) ) ;
//	m_parentNode->attachObject(m_numberText.get());
}

void BillboardNumber::unMarkNumber()
{
//	if (m_numberText)
//		m_numberText->detachFromParent();
}

void BillboardNumber::setParentNode(SceneNode* parentNode)
{
	//assert(m_numberText);
	//m_parentNode->detachObject(m_numberText.get());
	m_parentNode = parentNode;
	//m_parentNode->attachObject(m_numberText.get());
}