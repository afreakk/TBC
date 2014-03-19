#pragma once
class Tooltip
{
public:
	Tooltip(Ogre::SceneNode* parentNode);
	~Tooltip();
	void update();
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
	static void update()
	{
		for (auto& tooltip : m_tooltips)
			tooltip->update();
	}
	static void addTooltip(Tooltip* tooltip)
	{
		m_tooltips.push_back(tooltip);
	}
	static void removeTooltip(Tooltip* tooltip)
	{
		auto it = std::find(m_tooltips.begin(), m_tooltips.end(), tooltip);
		if (it != m_tooltips.end())
			m_tooltips.erase(it);
		else
			assert(0);
	}
private:
	static std::vector< Tooltip*> m_tooltips;
};