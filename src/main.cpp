#include <iostream>

#include <SFML/Graphics.hpp>
#include "grappa/interface/Interface.h"
#include "grappa/interface/Button.h"
#include "grappa/interface/PictureBox.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "test");

    sf::Texture catTexture;
    sf::Font    font;
    catTexture .loadFromFile("assets/cat.jpg");
    font       .loadFromFile("assets/aposiopesis.ttf");

    auto interface = gr::Interface(sf::FloatRect(0, 0, 500, 500))
        .addRelative<gr::PictureBox>("picture", sf::FloatRect(0, 0, 1, 1), catTexture)
            .addRelative<gr::Button>("button", sf::FloatRect(0, 0, 1, 1))
                .addClickFunction(
                    [] (auto& but) {
                        if(but.wasJustClicked()) {
                            std::cout << "hello world!" << std::endl;
                        }
                    }
                )
            .getParent()
        .getParent();

    while(window.isOpen()) {

        sf::Event e;
        if(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed ||
               e.type == sf::Event::KeyPressed) {
                window.close();
            }
            interface.handleEvent(e);
        }

        interface.update(window);

        window.clear();
        window.draw(interface);
        window.display();
    }

    return 0;
}
