#include "minesweeper.hpp"

int main(int argv, char** argc) {
    //disregard args
    (void)argv;
    (void)argc;

    uint32_t size = 0;
    uint32_t mines = 0;
    std::cout << "enter board size: ";
    std::cin >> size;
    std::cout << "enter number of mines: ";
    std::cin >> mines;

    Minesweeper game(size, mines);
    game.show();


    uint32_t turn_number = 0;
    while(1) {
        switch(game.state()) {
            case Minesweeper::State::IN_PROGRESS:
                std::cout << "turn: " << turn_number << std::endl;
                game.turn();
                game.show();
                turn_number++;
                break;
            case Minesweeper::State::WON:
                std::cout << "congrats!" << std::endl;
                return 0;
            case Minesweeper::State::LOST:
                std::cout << "better luck next time!" << std::endl;
                game.show(true);
                return 0;
        }
    }

    return 1;
}
