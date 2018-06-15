#include "tiles.hpp"
#include <string>
#include <sstream>
#include <gtest/gtest.h>

TEST(Tiles, InitializeTilesCorrect) {
    auto node = Tiles::Node({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 ,14, 15,
                16, 17, 18, 19, 20, 21, 22, 23, 24, 0});
    std::ostringstream oss;
    oss << node;
    ASSERT_EQ(oss.str(), "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 0 \n");
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
