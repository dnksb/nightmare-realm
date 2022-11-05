#include "field.h"

Field::Field() {
    srand(time(NULL));
    block_field = new Block*[field_size];
    for (int i = 0; i < field_size; i++)
    {
        block_field[i] = new Block[field_size];
        for (int j = 0; j < field_size; j++) {
            block_field[i][j].setPosition({
                (float)(250.0 + (60 * i)), 
                (float)(200.0 + (60 * j))});
        }
    }

    type_field = new Type *[field_size];
    for (int i = 0; i < field_size; i++) {
        type_field[i] = new Type[field_size];
        for (int j = 0; j < field_size; j++) {
            type_field[i][j] = FREE_BLOCK;
        }
    }
}

int Field::nextRand(int begin, int end) {
    return (rand() % (end - begin + 1) + begin);
}

void Field::chouseColumn() {
    first_lock_column = nextRand(1, 3);
    second_lock_column = nextRand(1, 3);
    if (first_lock_column == second_lock_column) {
        if (second_lock_column == 3) {
            second_lock_column = 1;
        }
        else if (second_lock_column == 1){
            second_lock_column = 3;
        }
        else {
            second_lock_column += 1;
        }
    }
}

void Field::chouseBlockType(int x, int y) {
    int num_type = nextRand(3, 5);
    switch (num_type)
    {
    case 3:
        if(amount_blue > 0) {
            type_field[y][x] = BLUE_BLOCK;
            amount_blue--;
            break;
        }
    case 4:
        if (amount_red > 0) {
            type_field[y][x] = RED_BLOCK;
            amount_red--;
            break;
        }
    case 5:
        if (amount_green > 0) {
            type_field[y][x] = GREEN_BLOCK;
            amount_green--;
            break;
        }
    default:
        if ( amount_blue > 0) {
            type_field[y][x] = BLUE_BLOCK;
            amount_blue--;
            break;
        }
        else if (amount_red > 0) {
            type_field[y][x] = RED_BLOCK;
            amount_red--;
            break;
        }
        break;
    }
}

void Field::inputFirstColumn(int y) {
    if(amount_first_column > 0) {
        if(nextRand(1, 2) == 2) {
            type_field[first_lock_column][y] = LOCK_BLOCK;
            amount_first_column--;
        }
        if(5 - y == amount_first_column) {
            type_field[first_lock_column][y] = LOCK_BLOCK;
            amount_first_column--;
        }
    }
}

void Field::inputSecondColumn(int y) {
    if(amount_second_column > 0) {
        if(nextRand(1, 2) == 2) {
            type_field[second_lock_column][y] = LOCK_BLOCK;
            amount_second_column--;
        }
        if(5 - y == amount_second_column) {
            type_field[second_lock_column][y] = LOCK_BLOCK;
            amount_second_column--;
        }
    }
}

void Field::inputClassicFirstColumn(int y) {
    if(amount_first_column > 0) {
        if (y == 0 || y == 2 || y == 4) {
            type_field[first_lock_column][y] = LOCK_BLOCK;
            amount_first_column--;
        }
    }
}

void Field::inputClassicSecondColumn(int y) {
    if(amount_second_column > 0) {
        if (y == 0 || y == 2 || y == 4) {
            type_field[second_lock_column][y] = LOCK_BLOCK;
            amount_second_column--;
        }
    }
}

void Field::generateTypeField() {

    chouseColumn();

    amount_first_column = 3;
    amount_second_column = 3;
    amount_red = 5;
    amount_blue = 5;
    amount_green = 5;

    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            if(j == first_lock_column) {
                inputFirstColumn(i);
            }
            else if(j == second_lock_column) {
                inputSecondColumn(i);
            }
            else {
                chouseBlockType(i, j);
            }
        }
    }
}

bool Field::maySwitch(sf::Vector2i position) {
    for (int i = 0; i < field_size; i++)
    {
        for (int  j = 0; j < field_size; j++)
        {
            if(block_field[i][j].isPressed(position)) {
                if (block_field[i][j].getType() == LOCK_BLOCK) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Field::maySet(sf::Vector2i position) {
    for (int i = 0; i < field_size; i++)
    {
        for (int  j = 0; j < field_size; j++)
        {
            if(block_field[i][j].isPressed(position)) {
                if (block_field[i][j].getType() == FREE_BLOCK) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    return false;
}

Block Field::getBlock(int x, int y) {
    return block_field[x][y];
}

void Field::generateNewField() {
    generateTypeField();

    chouse_block_x = -1;
    chouse_block_y = -1;
    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            switch (type_field[i][j])
            {
            case FREE_BLOCK:
                block_field[i][j].setTexture("img/free_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            case LOCK_BLOCK:
                block_field[i][j].setTexture("img/lock_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            case BLUE_BLOCK:
                block_field[i][j].setTexture("img/blue_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            case RED_BLOCK:
                block_field[i][j].setTexture("img/red_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            case GREEN_BLOCK:
                block_field[i][j].setTexture("img/green_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            default:
                break;
            }
        }
    }
}

void Field::draw(sf::RenderWindow &window) {
    for (int i = 0; i < field_size; i++) {
            for (int j = 0; j < field_size; j++) {
                window.draw(block_field[i][j].getSprite());
            }       
        }
}

bool Field::isCloseBlock(int x, int y) {
    if(x + 1 == chouse_block_x || x - 1 == chouse_block_x) {
        return (y == chouse_block_y) ? true : false;
    }
    if(y + 1 == chouse_block_y || y - 1 == chouse_block_y) {
        return (x == chouse_block_x) ? true : false;
    }
    else {
        return false;
    }
}

void Field::switchBlocks(int x, int y) {
    std::string tmp_filename = block_field[y][x].Texture();
    block_field[y][x].setTexture(block_field[chouse_block_y][chouse_block_x].Texture());
    block_field[chouse_block_y][chouse_block_x].setTexture(tmp_filename);
    Type tmp_type = block_field[y][x].getType();
    block_field[y][x].setType(block_field[chouse_block_y][chouse_block_x].getType());
    block_field[chouse_block_y][chouse_block_x].setType(tmp_type);
}

void Field::switchType(int x, int y) {
    Type tmp = type_field[y][x];
    type_field[y][x] = type_field[chouse_block_y][chouse_block_x];
    type_field[chouse_block_y][chouse_block_x] = tmp;
}

void Field::switchBlocks(sf::Vector2i position) {
    for (int i = 0; i < field_size; i++)
    {
        for (int  j = 0; j < field_size; j++)
        {
            if(block_field[i][j].isPressed(position)) {
                if(isCloseBlock(j, i) && chouse_block_x != -1 && chouse_block_y != -1) {
                    switchBlocks(j, i);
                    switchType(j, i);
                    chouse_block_x = -1;
                    chouse_block_y = -1;
                }
            }
        }
    }
}

void Field::setChouseBlock(sf::Vector2i position) {
    for (int i = 0; i < field_size; i++)
    {
        for (int  j = 0; j < field_size; j++)
        {
            if(block_field[i][j].isPressed(position)) {
                chouse_block_x = j;
                chouse_block_y = i;
            }
        }
    }
}

bool Field::checkColumn(int x) {
    for (int y = 1; y < field_size; y++)
    {
        if(block_field[x][y].Texture() != block_field[x][0].Texture()) {
            return false;
        }
    }
    return true;
}

bool Field::checkWin() {
    if(checkColumn(0) && checkColumn(4)) {
        if(checkColumn(1) || checkColumn(2) || checkColumn(3)) {
            return true;
        }
    }
    return false;
}

void Field::generateTypeClassic() {

    first_lock_column = 1;
    second_lock_column = 3;
    amount_first_column = 3;
    amount_second_column = 3;
    amount_red = 5;
    amount_blue = 5;
    amount_green = 5;

    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            if(j == first_lock_column) {
                inputClassicFirstColumn(i);
            }
            else if(j == second_lock_column) {
                inputClassicSecondColumn(i);
            }
            else {
                chouseBlockType(i, j);
            }
        }
    }
}

void Field::classicMode() {
    generateTypeClassic();

    chouse_block_x = -1;
    chouse_block_y = -1;
    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            switch (type_field[i][j])
            {
            case FREE_BLOCK:
                block_field[i][j].setTexture("img/free_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            case LOCK_BLOCK:
                block_field[i][j].setTexture("img/lock_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            case BLUE_BLOCK:
                block_field[i][j].setTexture("img/blue_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            case RED_BLOCK:
                block_field[i][j].setTexture("img/red_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            case GREEN_BLOCK:
                block_field[i][j].setTexture("img/green_block.jpg");
                block_field[i][j].setType(type_field[i][j]);
                break;
            default:
                break;
            }
        }
    }
}

Field::~Field() {
    for (int i = 0; i < field_size; i++)
    {
        delete[] type_field[i];
        delete[] block_field[i];
    }
    delete[] type_field;
    delete[] block_field;
}
