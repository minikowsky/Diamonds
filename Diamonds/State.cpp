#include "State.h"

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->states = state_data->states;
	this->quit = false;
}

State::~State()
{

}

void State::updateMouseposition()
{
	this->mousePos = sf::Mouse::getPosition(*this->window);
	//std::cout << mousePos.x << " " << mousePos.y << "\n";
	
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}


