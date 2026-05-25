#include <SFML/Graphics.hpp>
#include <filesystem>
#include <cstdlib>

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 400), "Realm Fighters Launcher");

    window.setFramerateLimit(60);

    sf::RectangleShape installButton(sf::Vector2f(300.f, 80.f));
    installButton.setPosition(200.f, 100.f);
    installButton.setFillColor(sf::Color(120, 30, 30));

    sf::RectangleShape playButton(sf::Vector2f(300.f, 80.f));
    playButton.setPosition(200.f, 220.f);
    playButton.setFillColor(sf::Color(30, 120, 30));

    bool installiert = false;

    if (std::filesystem::exists("RealmFighters/realm-fighters.exe"))
    {
        installiert = true;
    }

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
                    system(
                        "powershell -ExecutionPolicy Bypass -Command \""
                        "Invoke-WebRequest -Uri 'https://realm-fighters.com/downloads/realm-fighters.zip' -OutFile 'realm-fighters.zip';"
                        "if (!(Test-Path 'RealmFighters')) "
                        "{ New-Item -ItemType Directory -Path 'RealmFighters' };"
                        "Expand-Archive -Path 'realm-fighters.zip' -DestinationPath 'RealmFighters' -Force;"
                        "Remove-Item 'realm-fighters.zip' -Force\""
                    );

                    installiert = true;
                }

                if (playButton.getGlobalBounds().contains(mouseX, mouseY))
                {
                    if (installiert)
                    {
                        system("start RealmFighters\\realm-fighters.exe");
                    }
                }
            }
        }

        window.clear(sf::Color(20, 20, 20));

        window.draw(installButton);

        if (installiert)
        {
            window.draw(playButton);
        }

        window.display();
    }

    return 0;
}