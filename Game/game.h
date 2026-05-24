#pragma once
#include <SFML/Graphics.hpp>
#include "fighter.h"

class game
{
public:
    game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;

    fighter spieler1;
    fighter spieler2;

    int screen;
    int auswahl1;
    int auswahl2;
    int welt;

    sf::Clock attackClock1;
    sf::Clock attackClock2;
    sf::Clock worldClock;

    void events();
    void update();
    void draw();

    void drawTitle();
    void drawCharacterSelect();
    void drawFight();
    void drawEnd();

    void movePlayers();
    void attackPlayers();
};