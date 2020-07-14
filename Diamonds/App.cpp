#include "App.h"

App::App()
{
	this->initFields();
	this->initWindow();
	this->initStateData();
	this->initStates();
}

App::~App()
{
	delete this->window;
}

void App::start()
{
	appLoop();
}

void App::appLoop()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void App::initFields()
{
	this->window = NULL;

	this->font = new sf::Font(); //Default Font for all the Buttons
	if (!font->loadFromFile("Font/arial.ttf"))
	{
		std::cout << " error opening font file " << std::endl;
	}
}

void App::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 800), "Diamonds", sf::Style::Close | sf::Style::Titlebar);
	//icon.loadFromFile();
	//this->window->setIcon(32, 32, icon.getPixelsPtr());
}

void App::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.states = &this->states;
	this->stateData.font = this->font;
}
void App::initStates()
{
	this->states.push(new MenuState(&this->stateData));
}

void App::update()
{
	while (this->window->pollEvent(this->evnt))
	{
		if (this->evnt.type == sf::Event::Closed)
			this->window->close();
	}
}

void App::render()
{
	this->window->clear();
	//if (!this->initStates.empty())
	//	this->initStates.top()->render();
	this->window->display();
}
