#pragma once
#include "SFML/Graphics.hpp"
#include <stack>
class State;

class StateData
{
public:
	StateData() {};

	sf::RenderWindow* window;
	std::stack<State*>* states;
	sf::Font* font;
};


class State
{
public:
	State(StateData* state_data);
	virtual ~State();

	virtual void update() = 0;
	virtual void render() = 0;


protected:
	StateData* stateData;
	sf::RenderWindow* window;
	std::stack<State*>* states;
	sf::Font* font;

};

