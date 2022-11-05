#ifndef CONTROLER_H
#define CONTROLER_H
#include "SFML/Graphics.hpp"
#include "blocks.h"
#include <time.h>

class Field{
    private:
        const int field_size = 5;
        Block **block_field;
        Type **type_field;
        int first_lock_column;
        int second_lock_column;
        int amount_red;
        int amount_blue;
        int amount_green;
        int amount_first_column;
        int amount_second_column;
        int chouse_block_x;
        int  chouse_block_y; 
    private:
        void chouseColumn();
        void chouseBlockType(int x, int y);
        void inputFirstColumn(int y);
        void inputSecondColumn(int y);
        void inputClassicFirstColumn(int y);
        void inputClassicSecondColumn(int y);
        int nextRand(int begin, int end);
        void initTypeField();
        void generateTypeField();
        bool isCloseBlock(int x, int y);
        void switchType(int x, int y);
        void switchBlocks(int x, int y);
        bool checkColumn(int x);
        void generateTypeClassic();
    public:
        Field();
        Block **getField();
        Block getBlock(int x, int y);
        void setChouseBlock(sf::Vector2i position);
        void generateNewField();
        bool maySwitch(sf::Vector2i position);
        bool maySet(sf::Vector2i position);
        void switchBlocks(sf::Vector2i position);
        void draw(sf::RenderWindow& window);
        bool checkWin();
        void classicMode();
        ~Field();
};

#endif 