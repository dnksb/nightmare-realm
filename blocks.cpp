#include "blocks.h"

Block::Block(std::string filename) {
    this->filename = filename;
    this->texture->loadFromFile(filename);
    this->sprite->setTexture(*texture);
    this->is_define = true;
}

Block::Block(){

}

void Block::setPosition(sf::Vector2f position){
    this->sprite->setPosition(position);
}

sf::Vector2f Block::getPosition(){
    return this->sprite->getPosition();
}

void Block::setTexture(std::string filename){
    this->filename = filename;
    this->texture->loadFromFile(filename);
    this->sprite->setTexture(*texture);
    this->is_define = true;
}

void Block::setType(Type type) {
    this->type_block = type;
}

void Block::setSprite(sf::Sprite *sprite) {
    this->sprite = sprite;
}

Type Block::getType() {
    return this->type_block;
}

void Block::veiw(sf::RenderWindow &window){
    window.draw(*this->sprite);
}

sf::Texture Block::getTexture(){
    return *texture;
}

std::string Block::Texture() {
    return filename;
}

sf::Sprite Block::getSprite(){
    return *sprite;
}

Block::~Block() {
    delete this->sprite;
    delete this->texture;
}

bool Block::isPressed(sf::Vector2i dot) {
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

bool Block::getDefine() {
    return this->is_define;
}
