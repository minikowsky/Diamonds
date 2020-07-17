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
	delete this->font;
}


void App::initFields()
{
	this->window = NULL;
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
}
void App::initStates()
{
	this->states.push(new MenuState(&this->stateData));
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

void App::update()
{
	while (this->window->pollEvent(this->evnt))
	{
		if (this->evnt.type == sf::Event::Closed)
			this->window->close();
	}

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update();

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else
	{
		std::cout << "the End";
		this->window->close();
	}
}

void App::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}
