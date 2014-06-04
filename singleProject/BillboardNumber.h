#pragma once
#include "MovableText.h"
class BillboardNumber
{
public:
	BillboardNumber(SceneNode* node);
	~BillboardNumber();
	void markAs(int number);
	void unMarkNumber();
	void setParentNode(SceneNode* parentNode);
private:
	SceneNode* m_parentNode;
//	unique_ptr<MovableText> m_numberText;
	int m_currentNumber;
	static unsigned count;
};

