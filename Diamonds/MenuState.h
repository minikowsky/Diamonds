#pragma once
#include "SFML/Graphics.hpp"
#include "State.h"
#include "Button.h"
#include <map>
class MenuState :
    public State
{
public:
    //ctor/dtor
    MenuState(StateData* state_data);
    virtual ~MenuState();
    
    //methods
    void update();
    void render(sf::RenderWindow& target);
    void renderBtns(sf::RenderWindow& target);
private:
    //fields
    sf::RectangleShape background;
    std::map<std::string, Button*> menuButtons;
    sf::Font font;
    //inits
    void initGui();
    void initFields();
    //methods

   
    
};

