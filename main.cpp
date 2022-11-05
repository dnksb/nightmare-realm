#include <iostream>
#include <SFML/Graphics.hpp>
#include "field.h"
#include "blocks.h"
#include "ui.h"

void first_level(sf::RenderWindow &window);
void second_level(sf::RenderWindow &window);
sf::Vector2i mousePosition(sf::RenderWindow &window);

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Nightmare Realm");
    Button* start_button = new Button("img/start_button.jpg", {350, 200});
    Button* classic_button = new Button("img/classic_button.jpg", {350, 260});
    Button* exit_button = new Button("img/exit_button.jpg", {350, 320});

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                if(start_button->isPressed(mousePosition(window))) {
                    first_level(window);
                }
                if(classic_button->isPressed(mousePosition(window))) {
                    second_level(window);
                }
                if(exit_button->isPressed(mousePosition(window))) {
                    window.close();
                }
            }
        }
        window.clear();
        window.draw(start_button->getSprite());
        window.draw(classic_button->getSprite());
        window.draw(exit_button->getSprite());
        window.display();
    }

    delete start_button;
    delete classic_button;
    delete exit_button;
    
    return 0;
}

void first_level(sf::RenderWindow &window) {
    Field *field = new Field();
    Button* exit_button = new Button("img/exit_button.jpg", {350, 100});
    Block* win_screen = new Block("img/win_image.jpg");
    win_screen->setPosition({250, 200});
    
    field->generateNewField();

    bool open = true;
    while (open) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if(field->maySwitch(mousePosition(window))) {
                    field->setChouseBlock(mousePosition(window));
                }
                if (exit_button->isPressed(mousePosition(window))) {
                        open = false;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if(field->maySet(mousePosition(window))) {
                    field->switchBlocks(mousePosition(window));
                }
            }
        }
        window.clear();
        if(!field->checkWin()) {
            field->draw(window);
        }
        else {
            window.draw(win_screen->getSprite());
        }
        window.draw(exit_button->getSprite());
        window.display();
    }

    delete field;
    delete exit_button;

    return;
}

void second_level(sf::RenderWindow &window) {

    Field *field = new Field();
    Button* exit_button = new Button("img/exit_button.jpg", {350, 100});
    Block* win_screen = new Block("img/win_image.jpg");
    win_screen->setPosition({250, 200});

    field->classicMode();

    bool open = true;
    while (open) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if(field->maySwitch(mousePosition(window))) {
                    field->setChouseBlock(mousePosition(window));
                }
                if (exit_button->isPressed(mousePosition(window))) {
                        open = false;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if(field->maySet(mousePosition(window))) {
                    field->switchBlocks(mousePosition(window));
                }
            }
        }
        window.clear();
        if(!field->checkWin()) {
            field->draw(window);
        }
        else {
            window.draw(win_screen->getSprite());
        }
        window.draw(exit_button->getSprite());
        window.display();
    }

    delete field;
    delete exit_button;

    return;
}

sf::Vector2i mousePosition(sf::RenderWindow &window) {
    return sf::Mouse::getPosition() - window.getPosition();
}