#include <gtest/gtest.h>
#include "minesweeper.hpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TileTest, Construct) {
    Minesweeper::Tile tile;
}

using Tilestate = Minesweeper::Tile::State;
TEST(TileTest, BombStates) {
    //walkthrough tile states
    Minesweeper::Tile tile;
    EXPECT_EQ(Tilestate::NONE, tile.m_state);
    tile.setActive();
    EXPECT_EQ(Tilestate::ACTIVE, tile.m_state);

    Minesweeper::Tile tile2;
    EXPECT_EQ(Tilestate::NONE, tile2.m_state);
    tile2.uncover();
    EXPECT_EQ(Tilestate::DISCOVERED, tile2.m_state);
}

TEST(MinesweepTest, Construct) {
    uint32_t size = 10;
    uint32_t num_mines = 15;
    Minesweeper board(size, num_mines);

    board.show();
    EXPECT_EQ((size * size - num_mines), board.spacesLeft());
}

TEST(MinesweepTest, UncoverTile) {

    Minesweeper safe_board(1, 0);
    Minesweeper unsafe_board(1, 1);

    EXPECT_EQ(1, safe_board.spacesLeft());
    EXPECT_FALSE(safe_board.uncoverTile(0, 0));
    EXPECT_EQ(0, safe_board.spacesLeft());

    EXPECT_EQ(0, unsafe_board.spacesLeft());
    EXPECT_TRUE(unsafe_board.uncoverTile(0, 0));
}
