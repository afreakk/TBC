#pragma once
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
private:
	Gorilla::Screen* m_screen;
	Gorilla::Layer* m_layer;
	Gorilla::Rectangle* m_rBackground;
	Gorilla::Rectangle* m_rPlay;
	Gorilla::Rectangle* m_rOptions;
	Gorilla::Rectangle* m_rQuit;
};

