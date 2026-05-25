#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <filesystem>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 300), "Realm Fighters Launcher");
    window.setFramerateLimit(60);

    sf::RectangleShape installButton(sf::Vector2f(300.f, 70.f));
    installButton.setPosition(150.f, 60.f);
    installButton.setFillColor(sf::Color(120, 30, 30));

    sf::RectangleShape startButton(sf::Vector2f(300.f, 70.f));
    startButton.setPosition(150.f, 170.f);
    startButton.setFillColor(sf::Color(30, 120, 30));

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

                if (installButton.getGlobalBounds().contains(mouseX, mouseY))
                {
                    system("powershell -ExecutionPolicy Bypass -Command \"Invoke-WebRequest -Uri 'https://realm-fighters.com/downloads/realm-fighters.zip' -OutFile 'realm-fighters.zip'; if (!(Test-Path 'RealmFighters')) { New-Item -ItemType Directory -Path 'RealmFighters' }; Expand-Archive -Path 'realm-fighters.zip' -DestinationPath 'RealmFighters' -Force\"");
                }

                if (startButton.getGlobalBounds().contains(mouseX, mouseY))
                {
                    system("start RealmFighters\\realm-fighters.exe");
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(installButton);
        window.draw(startButton);
        window.display();
    }

    return 0;
}