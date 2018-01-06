#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>

class Minesweeper {

public:

    ///
    /// \brief Enum of game states
    ///

    enum class State {
        IN_PROGRESS = 0,
        WON,
        LOST
    };

    ///
    /// \brief Atmoic unit for the game board
    ///
    struct Tile {
        
        ///
        /// \brief Enum for bomb states of tile
        /// Can either have nothing, discovered, or active bomb 
        ///
        enum class State {
            NONE=0,
            DISCOVERED,
            ACTIVE
        };

        ///
        /// \brief Constructor
        ///

        Tile() {
            m_state = State::NONE;
            m_count = 0;
        }

        ///
        /// \brief Destructor
        ///

        ~Tile() {}

        ///
        /// \brief Set state to active
        ///
  
        void setActive() {
            m_state = State::ACTIVE;
        }

        ///
        /// \brief Set state to discovered
        ///

        void uncover() {
            m_state = State::DISCOVERED;
        }

        ///
        /// \brief Current state of the tile
        ///
      
        State m_state;

        ///
        /// \brief Record of number of adjacent bombs
        /// Avoids having to keep recalculating the same number
        ///

        uint32_t m_count;
    };

    ///
    /// \brief Constructor for game
    ///
    /// \param[in] size Length and width for board
    /// \param[in] mines Number of mines for board
    ///
    Minesweeper(uint32_t size, uint32_t mines);

    ///
    /// \brief Destructor for game
    ///
    ~Minesweeper();

    ///
    /// \brief Print the board to the screen
    ///
    /// \param[in] show Distinguish mines from undicovered tiles
    ///

    void show(bool show=false);

    ///
    /// \brief Get the number of remaining safe spaces
    ///
    /// \return Number of undiscovered safe spaces
    ///

    uint32_t spacesLeft();

    ///
    /// \brief Uncover a tile specified by provided coordinates
    ///
    /// \param[row] row of tile to uncover
    /// \param[column] column of tile to uncover
    ///
    /// \return True if it was a mine, otherwise false
    ///

    bool uncoverTile(uint32_t row, uint32_t column);

    ///
    /// \brief Get the current state of the game
    /// Also checks for win condition if state is in_progress
    ///
    /// \return State of game
    ///

    State state(); 

    ///
    /// \brief Take a turn of the game
    ///

    void turn();

protected:

    ///
    /// \brief Initialize tiles by placing active mines
    ///
    /// \param[in] mines Number of mines to place
    ///

    void init_tiles(uint32_t mines);        

    ///
    /// \brief Get the number of active tiles next to the specified tile
    ///
    /// \param[in] row Row of tile
    /// \param[in] column Column of tile
    ///

    uint32_t getAdjacentActive(uint32_t row, uint32_t column);

    ///
    /// \brief Board tiles for the game instance
    /// Vector of board rows 
    /// e.g. m_tiles[1][3] is row 1 column 3
    ///

    std::vector<std::vector<Tile>> m_tiles;

    ///
    /// \brief State of game
    ///

    State m_state;

};
