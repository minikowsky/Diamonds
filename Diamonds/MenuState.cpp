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
	this->background.setFillColor(sf::Color(90,90,90));
	//this->background.setFillColor(sf::Color(25, 163, 255));
	//Buttons
	this->menuButtons["GAME_STATE"] = new Button(sf::Vector2f(150.f,150.f), sf::Vector2f(200.f, 50.f),&this->font,"New Game",30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 150), sf::Color(20, 20, 20, 150),30.f);

	this->menuButtons["SCORES_STATE"] = new Button(sf::Vector2f(150.f, 250.f), sf::Vector2f(200.f, 50.f), &this->font, "Scores", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 150), sf::Color(20, 20, 20, 150),50.f);


	this->menuButtons["EXIT_STATE"] = new Button(sf::Vector2f(150.f, 350.f), sf::Vector2f(200.f, 50.f), &this->font, "Exit", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 150), sf::Color(20, 20, 20, 150),70.f);
}

void MenuState::initFields()
{
	if (!this->font.loadFromFile("Font/arial.ttf"))
	{
		std::cout << " error opening font file " << std::endl;
	}
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
		//std::cout << "Game!\n";
		this->states->push(new GameState(this->stateData));
	}
	//Hall of fame
	if (this->menuButtons["SCORES_STATE"]->isPressed())
	{
		//std::cout << "Scores!\n";
		//this->states->push(new GameState(this->stateData));
	}
	//Exit
	if (this->menuButtons["EXIT_STATE"]->isPressed())
	{
		//std::cout << "Bye!\n";
		this->endState();
	}
}


void MenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	//this->background.setFillColor(sf::Color::White);
	target->draw(this->background);
	this->renderBtns(*target);

	

}

void MenuState::renderBtns(sf::RenderTarget& target)
{
	for (auto& it : this->menuButtons)
	{
		it.second->render(target);

	}
	
}


