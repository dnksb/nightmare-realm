#include "ui.h"

Button::Button(std::string filename, sf::Vector2f position) {
    this->texture->loadFromFile(filename);
    this->sprite->setTexture(*texture);
    this->sprite->setPosition(position);
}

Button::Button() {

}

bool Button::isPressed(sf::Vector2i dot) {
    sf::Vector2f temp_position = sprite->getPosition();
    sf::Vector2u temp_scale = texture->getSize();
    if(temp_position.x > dot.x || temp_scale.x + temp_position.x < dot.x){
        return false;
    }
    if(temp_position.y > (dot.y - 30) || temp_scale.y + temp_position.y < (dot.y - 30)){
        return false;
    }
    return true;
}

Button::~Button() {
}
