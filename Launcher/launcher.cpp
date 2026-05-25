#include <SFML/Graphics.hpp>
#include <cstdlib>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 300), "Realm Fighters Launcher");
    window.setFramerateLimit(60);

    sf::RectangleShape button(sf::Vector2f(300.f, 80.f));
    button.setPosition(150.f, 110.f);
    button.setFillColor(sf::Color(120, 30, 30));

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                if (button.getGlobalBounds().contains(mouseX, mouseY))
                {
                    system("start RealmFighters\\realm-fighters.exe");
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(button);
        window.display();
    }

    return 0;
}