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
    sf::RectangleShape scoreBackground;
    sf::Text scoreText;
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
    bool moving,returned;
    sf::Vector2f firstPos, secondPos;
    //temp variables to refill and falling diamonds
    bool falling;
    int counter;
    //temp variables to crush diamonds
    sf::Vector2i beginningOfCrush, endOfCrush;
    //score view
    bool finish;
    int moves;
    sf::Text finalText;
    bool finishGameWasPressed;
    //init methods
    void initDiamonds();
    void initGui();
    void initFields();
    
    //methods
    void startGame();
    void scoreView();
    bool refillCheck();
    bool crushCkeck();
    void diamondsRefill();
    void diamondsCrush();
    void moveDiamonds();
    void fallingDiamonds();
    
};

