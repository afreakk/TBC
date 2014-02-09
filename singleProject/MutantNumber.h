#pragma once
#include "MovableText.h"
class MutantNumber
{
public:
	MutantNumber(SceneNode* node);
	~MutantNumber();
	void markAs(int number);
	void unMarkNumber();
private:
	SceneNode* m_modelNode;
	SceneNode* m_fontNode;
	bool m_marked;
	unique_ptr<MovableText> m_numberText;
};

