#include "minesweeper.hpp"

Minesweeper::Minesweeper(uint32_t size, uint32_t mines) :
  m_tiles(size, std::vector<Tile>(size, Tile())),
  m_state(State::IN_PROGRESS)
{
    if(mines > size * size) {
        throw std::runtime_error("too many mines for board size");
    }

    if(size == 0) {
        throw std::runtime_error("board size must not be 0");
    }

    init_tiles(mines);    
}

Minesweeper::~Minesweeper() {}

void Minesweeper::show(bool show_active) {

    //print rows one at a time
    std::string col_label = "  ";
    for(uint32_t i = 0; i < m_tiles[0].size(); i++) {
        col_label += std::to_string(i);
    }
    std::cout << col_label << std::endl << std::endl;;

    uint32_t i = 0;
    for(auto row : m_tiles) {

        //row to print
        std::string row_str = std::to_string(i) + " ";
        for(auto tile : row) {
            switch(tile.m_state) {
                case Tile::State::NONE:
                    row_str += "X";
                    break;
                case Tile::State::ACTIVE:
                    if(show_active) {
                        row_str += "*";
                    }
                    else {
                        row_str += "X";
                    }
                    break;
                case Tile::State::DISCOVERED:
                    row_str += std::to_string(tile.m_count);
                    break;
            }
        }
        std::cout << row_str << std::endl;
        i++;

    }
}

uint32_t Minesweeper::spacesLeft() {
    uint32_t spaces = 0;
    for(auto row : m_tiles) {
        for(auto tile : row) {
            if(Tile::State::NONE == tile.m_state) {
                spaces++;
            }
        }
    }
    return spaces;
}

void Minesweeper::init_tiles(uint32_t mines) {

    //randomize tiles
    for(uint32_t i = 0; i < mines; i++) {

        uint32_t row = 0;
        uint32_t column = 0;
        do {
            row = rand() % m_tiles.size();
            column = rand() % m_tiles[0].size();
        }while(m_tiles[row][column].m_state != Tile::State::NONE);

        m_tiles[row][column].m_state = Tile::State::ACTIVE;
    }

    //fill counts
    for(uint32_t row = 0; row < m_tiles.size(); row++) {
        for(uint32_t column = 0; column < m_tiles[0].size(); column++) {

            m_tiles[row][column].m_count = getAdjacentActive(row, column);
        }
    }
}

uint32_t Minesweeper::getAdjacentActive(uint32_t row, uint32_t column) {

    uint32_t count = 0;
    uint32_t rows = m_tiles.size();
    uint32_t columns = m_tiles[0].size();

    //check em all :(
    if(row > 0 && Tile::State::ACTIVE == m_tiles[row - 1][column].m_state) {
        count++;
    }
    if(column > 0 && Tile::State::ACTIVE == m_tiles[row][column - 1].m_state) {
        count++;
    }
    if(row < (rows - 1) && Tile::State::ACTIVE == m_tiles[row + 1][column].m_state) {
        count++;
    }
    if(row < (columns - 1) && Tile::State::ACTIVE == m_tiles[row][column + 1].m_state) {
        count++;
    }
    if(column > 0 && row > 0 && Tile::State::ACTIVE == m_tiles[row - 1][column - 1].m_state) {
        count++;
    }
    if(column < (columns - 1) && row < (rows - 1) && Tile::State::ACTIVE == m_tiles[row + 1][column + 1].m_state) {
        count++;
    }
    if(column > 0 && row < (rows - 1) && Tile::State::ACTIVE == m_tiles[row + 1][column - 1].m_state) {
        count++;
    }
    if(column < (columns - 1) && row > 0 && Tile::State::ACTIVE == m_tiles[row - 1][column + 1].m_state) {
        count++;
    }

    return count;
}

bool Minesweeper::uncoverTile(uint32_t row, uint32_t column) {

    uint32_t rows = m_tiles.size();
    uint32_t columns = m_tiles[0].size();

    if(Tile::State::NONE == m_tiles[row][column].m_state) {
        m_tiles[row][column].m_state = Tile::State::DISCOVERED;

        //uncover adjacent tiles if none are mines
        if(0 == m_tiles[row][column].m_count) {
            if(0 < row) {
                uncoverTile(row - 1, column);
            }
            if(0 < column) {
                uncoverTile(row, column - 1);
            }
            if(row < (rows - 1)) {
                uncoverTile(row + 1, column);
            }
            if(column < (columns - 1)) {
                uncoverTile(row, column + 1);
            }
            if(0 < row && 0 < column) {
                uncoverTile(row - 1, column - 1);
            }
            if(0 < row && column < (columns - 1)) {
                uncoverTile(row - 1, column + 1);
            }
            if(row < (rows - 1) && 0 < column) {
                uncoverTile(row + 1, column - 1);
            }
            if(row < (rows - 1) && column < (columns - 1)) {
                uncoverTile(row + 1, column + 1);
            }
        }
        return false;
    }
    else if(Tile::State::ACTIVE == m_tiles[row][column].m_state) {
        return true;
    }

    //do nothing if uncovering a discovered tile
    return false;
}

Minesweeper::State Minesweeper::state() {
    switch(m_state) {
        case State::IN_PROGRESS:
            if(0 == spacesLeft()) {
                m_state = State::WON;
            }
            return m_state;
          
        default:
            return m_state;
    }
}

void Minesweeper::turn() {
    //get a coordinate, then try to uncover it
    uint32_t row = 0;
    uint32_t column = 0;

    std::cout << "discover a tile!" << std::endl;
    std::cout << "row: ";
    std::cin >> row;
    std::cout << "column: ";
    std::cin >> column;

    bool exploded = uncoverTile(row, column);
    if(true == exploded) {
        m_state = State::LOST;
        return;
    }

}
