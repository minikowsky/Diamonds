#include "MenuState.h"

MenuState::MenuState(StateData* state_data)
	:State(state_data)
{
	this->initGui();
	this->initFields();
}

MenuState::~MenuState()
{
	auto it = this->menuButtons.begin();
	for (it = this->menuButtons.begin(); it != this->menuButtons.end(); ++it)
	{
		delete it->second;
	}
}

void MenuState::initGui()
{
	//Background
	this->background.setSize(static_cast<sf::Vector2f>(window->getSize()));
	//std::cout << window->getSize().x << window->getSize().y;
	this->background.setFillColor(sf::Color::Green);
	//Buttons
	this->menuButtons["GAME_STATE"] = new Button(sf::Vector2f(300,100), sf::Vector2f(100.f, 50.f),&this->font,"New Game",30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->menuButtons["HOF_STATE"] = new Button(sf::Vector2f(300, 200), sf::Vector2f(100, 50), &this->font, "Hall Of Fame", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));


	this->menuButtons["EXIT_STATE"] = new Button(sf::Vector2f(300, 300), sf::Vector2f(100, 50), &this->font, "Exit", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MenuState::initFields()
{
	//todo:
}

void MenuState::update()
{
	this->updateMouseposition();
	for (auto& it : this->menuButtons)
	{
		it.second->update(this->mousePos);
	}
	//Game
	if (this->menuButtons["GAME_STATE"]->isPressed())
	{
		std::cout << "Game!\n";
		//this->states->push(new GameState(this->stateData));
	}
	//Hall of fame
	if (this->menuButtons["HOF_STATE"]->isPressed())
	{
		std::cout << "Hall of fame!\n";
		//this->states->push(new GameState(this->stateData));
	}
	//Exit
	if (this->menuButtons["EXIT_STATE"]->isPressed())
	{
		std::cout << "Bye!\n";
		this->endState();
	}
}


void MenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderBtns(*target);


	sf::RectangleShape sh;
	sh.setPosition(1, 1);
	sh.setSize(sf::Vector2f(20, 20));
	sh.setFillColor(sf::Color::White);
	target->draw(sh);

}

void MenuState::renderBtns(sf::RenderTarget& target)
{
	for (auto& it : this->menuButtons)
	{
		it.second->render(target);

	}
}


