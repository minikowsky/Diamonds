#include "State.h"

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->states = state_data->states;
	this->font = state_data->font;
}

State::~State()
{

}


