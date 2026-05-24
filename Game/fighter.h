#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct fighter
{
    sf::RectangleShape shape;
    int leben;
    int maxleben;
    int schaden;
    float speed;
    std::string klasse;
};

void setklasse(fighter& spieler, int auswahl, float x, float y, sf::Color farbe);
void lebensleiste(sf::RenderWindow& window, fighter& spieler, float x, float y);