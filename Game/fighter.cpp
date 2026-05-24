#include "fighter.h"

void setklasse(fighter& spieler, int auswahl, float x, float y, sf::Color farbe)
{
    spieler.shape.setPosition(x, y);
    spieler.shape.setFillColor(farbe);

    if (auswahl == 0)
    {
        spieler.klasse = "Magier";
        spieler.maxleben = 80;
        spieler.leben = 80;
        spieler.schaden = 15;
        spieler.speed = 5.f;
        spieler.shape.setSize(sf::Vector2f(50.f, 50.f));
    }
    else if (auswahl == 1)
    {
        spieler.klasse = "Tank";
        spieler.maxleben = 130;
        spieler.leben = 130;
        spieler.schaden = 8;
        spieler.speed = 3.5f;
        spieler.shape.setSize(sf::Vector2f(65.f, 65.f));
    }
    else
    {
        spieler.klasse = "Assassine";
        spieler.maxleben = 70;
        spieler.leben = 70;
        spieler.schaden = 20;
        spieler.speed = 6.5f;
        spieler.shape.setSize(sf::Vector2f(45.f, 45.f));
    }
}

void lebensleiste(sf::RenderWindow& window, fighter& spieler, float x, float y)
{
    sf::RectangleShape hintergrund(sf::Vector2f(300.f, 25.f));
    hintergrund.setPosition(x, y);
    hintergrund.setFillColor(sf::Color(80, 80, 80));

    float breite = 300.f * spieler.leben / spieler.maxleben;

    if (breite < 0)
    {
        breite = 0;
    }

    sf::RectangleShape leben(sf::Vector2f(breite, 25.f));
    leben.setPosition(x, y);
    leben.setFillColor(sf::Color::Green);

    window.draw(hintergrund);
    window.draw(leben);
}