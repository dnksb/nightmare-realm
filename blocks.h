#ifndef BLOCKS_H
#define BLOCKS_H
#include "SFML/Graphics.hpp"
#include <iostream>

enum Type {
    FREE_BLOCK = 1, 
    LOCK_BLOCK, 
    BLUE_BLOCK, 
    RED_BLOCK, 
    GREEN_BLOCK
};

class Block{
    protected:
        bool is_define = false;
        sf::Texture *texture = new sf::Texture();
        sf::Sprite *sprite = new sf::Sprite();
        Type type_block = FREE_BLOCK;
        std::string filename;
    public:
        Block();
        explicit Block(std::string filename);
        void setTexture(std::string filename);
        void setPosition(sf::Vector2f position);
        void setSprite(sf::Sprite *sprite);
        sf::Vector2f getPosition();
        sf::Texture getTexture();
        std::string Texture();
        sf::Sprite *Sprite();
        sf::Sprite getSprite();
        void setType(Type type);
        Type getType();
        void veiw(sf::RenderWindow &window);
        virtual bool isPressed(sf::Vector2i dot);
        bool getDefine();
        virtual ~Block();
};

#endif