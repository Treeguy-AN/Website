#include "game.h"
#include <string>

game::game() :
    window(sf::VideoMode(1280, 720), "Realm Fighters")
{
    window.setFramerateLimit(60);

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
{
    return;
}

    text.setFont(font);
    text.setFillColor(sf::Color::White);

    screen = 0;
    auswahl1 = 0;
    auswahl2 = 1;
    welt = 0;
}

void game::run()
{
    while (window.isOpen())
    {
        events();
        update();
        draw();
    }
}

void game::events()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (screen == 0 && event.key.code == sf::Keyboard::Enter)
            {
                screen = 1;
            }
            else if (screen == 1)
            {
                if (event.key.code == sf::Keyboard::A)
                {
                    auswahl1--;
                    if (auswahl1 < 0) auswahl1 = 2;
                }

                if (event.key.code == sf::Keyboard::D)
                {
                    auswahl1++;
                    if (auswahl1 > 2) auswahl1 = 0;
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    auswahl2--;
                    if (auswahl2 < 0) auswahl2 = 2;
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    auswahl2++;
                    if (auswahl2 > 2) auswahl2 = 0;
                }

                if (event.key.code == sf::Keyboard::Enter)
                {
                    setklasse(spieler1, auswahl1, 200.f, 330.f, sf::Color::Blue);
                    setklasse(spieler2, auswahl2, 1000.f, 330.f, sf::Color::Red);
                    worldClock.restart();
                    screen = 2;
                }
            }
            else if (screen == 3)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    spieler1.leben = spieler1.maxleben;
                    spieler2.leben = spieler2.maxleben;
                    spieler1.shape.setPosition(200.f, 330.f);
                    spieler2.shape.setPosition(1000.f, 330.f);
                    welt = 0;
                    worldClock.restart();
                    screen = 2;
                }

                if (event.key.code == sf::Keyboard::Escape)
                {
                    screen = 0;
                }
            }
        }
    }
}

void game::update()
{
    if (screen == 2)
    {
        if (worldClock.getElapsedTime().asSeconds() > 10)
        {
            welt++;
            if (welt > 2) welt = 0;
            worldClock.restart();
        }

        if (spieler1.leben > 0 && spieler2.leben > 0)
        {
            movePlayers();
            attackPlayers();
        }

        if (spieler1.leben <= 0 || spieler2.leben <= 0)
        {
            screen = 3;
        }
    }
}

void game::movePlayers()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) spieler1.shape.move(0.f, -spieler1.speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) spieler1.shape.move(0.f, spieler1.speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) spieler1.shape.move(-spieler1.speed, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) spieler1.shape.move(spieler1.speed, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) spieler2.shape.move(0.f, -spieler2.speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) spieler2.shape.move(0.f, spieler2.speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) spieler2.shape.move(-spieler2.speed, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) spieler2.shape.move(spieler2.speed, 0.f);
}

void game::attackPlayers()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        if (attackClock1.getElapsedTime().asSeconds() > 0.5f)
        {
            sf::FloatRect hitbox = spieler1.shape.getGlobalBounds();
            hitbox.left -= 25.f;
            hitbox.top -= 25.f;
            hitbox.width += 50.f;
            hitbox.height += 50.f;

            if (hitbox.intersects(spieler2.shape.getGlobalBounds()))
            {
                spieler2.leben -= spieler1.schaden;
            }

            attackClock1.restart();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
    {
        if (attackClock2.getElapsedTime().asSeconds() > 0.5f)
        {
            sf::FloatRect hitbox = spieler2.shape.getGlobalBounds();
            hitbox.left -= 25.f;
            hitbox.top -= 25.f;
            hitbox.width += 50.f;
            hitbox.height += 50.f;

            if (hitbox.intersects(spieler1.shape.getGlobalBounds()))
            {
                spieler1.leben -= spieler2.schaden;
            }

            attackClock2.restart();
        }
    }
}

void game::draw()
{
    if (screen == 0) drawTitle();
    else if (screen == 1) drawCharacterSelect();
    else if (screen == 2) drawFight();
    else if (screen == 3) drawEnd();

    window.display();
}

void game::drawTitle()
{
    window.clear(sf::Color::Black);

    text.setCharacterSize(60);
    text.setPosition(390.f, 200.f);
    text.setString("Realm Fighters");
    window.draw(text);

    text.setCharacterSize(28);
    text.setPosition(420.f, 330.f);
    text.setString("Druecke ENTER zum Starten");
    window.draw(text);
}

void game::drawCharacterSelect()
{
    window.clear(sf::Color(30, 30, 30));

    std::string klassen[3] = {"Magier", "Tank", "Assassine"};

    text.setCharacterSize(45);
    text.setPosition(390.f, 70.f);
    text.setString("Charakter Auswahl");
    window.draw(text);

    text.setCharacterSize(30);
    text.setPosition(120.f, 200.f);
    text.setString("Spieler 1\nA / D waehlen\n\nKlasse: " + klassen[auswahl1]);
    window.draw(text);

    text.setPosition(760.f, 200.f);
    text.setString("Spieler 2\nPfeile waehlen\n\nKlasse: " + klassen[auswahl2]);
    window.draw(text);

    text.setPosition(390.f, 560.f);
    text.setString("ENTER = Kampf starten");
    window.draw(text);
}

void game::drawFight()
{
    if (welt == 0) window.clear(sf::Color(40, 120, 40));
    else if (welt == 1) window.clear(sf::Color(120, 70, 20));
    else window.clear(sf::Color(40, 40, 120));

    std::string weltName = "Wald";
    if (welt == 1) weltName = "Wueste";
    if (welt == 2) weltName = "Eiswelt";

    lebensleiste(window, spieler1, 20.f, 20.f);
    lebensleiste(window, spieler2, 960.f, 20.f);

    text.setCharacterSize(22);
    text.setPosition(20.f, 55.f);
    text.setString(
        "Welt: " + weltName + "\n" +
        "Spieler 1: " + spieler1.klasse + " | F = Angriff\n" +
        "Spieler 2: " + spieler2.klasse + " | L = Angriff"
    );
    window.draw(text);

    window.draw(spieler1.shape);
    window.draw(spieler2.shape);
}

void game::drawEnd()
{
    window.clear(sf::Color::Black);

    text.setCharacterSize(50);
    text.setPosition(390.f, 220.f);

    if (spieler1.leben <= 0)
    {
        text.setString("Spieler 2 gewinnt!");
    }
    else
    {
        text.setString("Spieler 1 gewinnt!");
    }

    window.draw(text);

    text.setCharacterSize(28);
    text.setPosition(390.f, 330.f);
    text.setString("ENTER = nochmal spielen");
    window.draw(text);

    text.setPosition(390.f, 380.f);
    text.setString("ESC = zurueck zum Titel");
    window.draw(text);
}