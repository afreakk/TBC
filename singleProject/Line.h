#pragma once
#include "ManualLine.h"
class Line 
{
public:
	Line(Node* start, Node* end, string materialName);
	void newNode(Node* end);
	void update();
	~Line();
private:
	Node* m_start;
	Node* m_end;
	ManualLine m_line;
};

