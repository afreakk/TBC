#pragma once
class Tooltip
{
public:
	Tooltip(Ogre::SceneNode* parentNode);
	~Tooltip();
	void update();
	void enable(bool v);
private:
	const Ogre::Vector2 m_tooltipSize;
	const Ogre::Vector2 m_rectSize;

	Gorilla::ScreenRenderable* m_screen;
	Gorilla::Layer* m_layer;
	Gorilla::MarkupText* m_markup;
	Gorilla::LineList* m_lineList;
	Ogre::SceneNode*m_node;

};


class TooltipUpdates
{
public:
	static void update();
	static void addTooltip(Tooltip* tooltip);
	static void removeTooltip(Tooltip* tooltip);
private:
	static std::vector< Tooltip*> m_tooltips;
};