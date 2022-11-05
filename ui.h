#ifndef UI_H
#define UI_H
#include "SFML/Graphics.hpp"
#include "blocks.h"
#include <iostream>

class Button : public Block{
    private:
        sf::RectangleShape *rect;
    public:
        Button(std::string filename, sf::Vector2f position);
        Button();
        ~Button() override;
        bool isPressed(sf::Vector2i dot) override;
};

#endif 