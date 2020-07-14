#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "App.h"

class Game: public App
{
public:
	Game();
	void start();
	~Game();
private:
	void gameLoop();
	void initializeStuff();
	void update();
	void drawStuff();


};

