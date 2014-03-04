#pragma once
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
private:
	Gorilla::Screen* m_screen;
	Gorilla::Layer* m_layer;
	Gorilla::Rectangle* m_rect;
};

