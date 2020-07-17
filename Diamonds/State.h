#pragma once
#include "SFML/Graphics.hpp"
#include <stack>
#include <iostream>
#include <map>
class State;

class StateData
{
public:
	StateData() {};

	sf::RenderWindow* window;
	std::stack<State*>* states;
};


class State
{
public:
	State(StateData* state_data);
	virtual ~State();

	void updateMouseposition();
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
	const bool& getQuit() const;
	void endState();

protected:
	StateData* stateData;
	sf::RenderWindow* window;
	std::stack<State*>* states;
	bool quit;

	
	sf::Vector2i mousePos;

};

