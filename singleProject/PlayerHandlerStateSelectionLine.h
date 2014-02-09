#pragma once
class Line;
class PlayerHandlerStateSelectionLine
{
public:
	PlayerHandlerStateSelectionLine();
	~PlayerHandlerStateSelectionLine();
	void setNewTarget(unsigned index);
	void addEnemy();
	void update();
private:
	std::vector<unique_ptr<Line>> m_lines;
	Node* m_currentNode;
	unsigned m_index;
};

