#include "MenuState.h"

MenuState::MenuState(StateData* state_data)
	:State(state_data)
{
	this->initFields();
}

MenuState::~MenuState()
{
}

void MenuState::updateButtons()
{

}

void MenuState::update()
{
	this->updateButtons();
}

void MenuState::renderButtons()
{
}

void MenuState::render()
{
}

void MenuState::initFields()
{
}
