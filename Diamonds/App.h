#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include "State.h"
#include <map>
#include "MenuState.h"

class App
{
public:
	//Ctor/dtor
	App();
	virtual ~App();
	void start();
private:
	//methods
	void appLoop();
	void initFields();
	void initWindow();
	void initStateData();
	void initStates();
	
	void update();
	void render();
	
	//fields
	sf::RenderWindow *window;
	std::stack<State*> states;
	sf::Event evnt;
	sf::Font* font;
	sf::Image icon;
	StateData stateData;
	

};

