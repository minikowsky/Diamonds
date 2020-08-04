#pragma once
#include "State.h"
#include <vector>
#include "Diamond.h"
#include <string>
#include <cmath>
#include <algorithm>
class GameState :
    public State
{
public:
    //ctor/dtor
    GameState(StateData* state_data);
    virtual ~GameState();

    //methods
    void update();
    void updateTime();
    void updateDiamonds();
    void render(sf::RenderTarget* target=NULL);
    void renderDiamonds(sf::RenderTarget& target);
private:
    //fields
    sf::RectangleShape background;
    sf::RectangleShape timerBackground;
    sf::Text timerText;
    std::vector<sf::Texture> diamondTextures;
    std::vector<std::vector<Diamond*> >vecDiamonds;
    sf::Font *font;
    sf::Clock dtClock;
    sf::Time time;
    std::string remainingTime;
    int score;
    bool start;

    //temp variables to moving diamonds
    bool firstDiamondToChange;
    bool secondDiamondToChange;
    int firstI, firstJ, secondI, secondJ;
    bool moving;
    sf::Vector2f firstPos, secondPos;
    //init methods
    void initDiamonds();
    void initGui();
    void initFields();
    
    //methods
    void startGame();
    bool refillCheck();
    bool crushCkeck();
    void diamondsRefill();
    void diamondsCrush();
    void moveDiamonds();
};

