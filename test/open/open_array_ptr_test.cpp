#include "open_array_ptr.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct DummyNode {
    int heuristic_value = 0;
    int cost = 0;

    DummyNode(int heuristic_value, int cost) :
        heuristic_value(heuristic_value),
        cost(cost) {}

    bool operator==(DummyNode const & rhs) const {
        return heuristic_value == rhs.heuristic_value &&
            cost == rhs.cost;
    }
    struct Board {
        std::array<int, 1> tiles;
    } board;
};

int getH(DummyNode const & node) {
    return node.heuristic_value;
}

int getG(DummyNode const & node) {
    return node.cost;
}

int getF(DummyNode const & node) {
    return getG(node) + getH(node);
}

class OpenArrayInitialize : public testing::Test {
public:
    DummyNode node1 = DummyNode{0, 0};
    DummyNode node2 = DummyNode{2, 1};
    DummyNode node3 = DummyNode{1, 2};

    OpenArrayPtr<DummyNode> open;

    virtual void SetUp() {
        open.push(&node3);
        open.push(&node1);
        open.push(&node2);
    }
};

TEST_F(OpenArrayInitialize, PopLowestFValHighestGValNode) {
    EXPECT_TRUE(*open.pop() == DummyNode(0, 0));
    EXPECT_TRUE(*open.pop() == DummyNode(1, 2));
    EXPECT_TRUE(*open.pop() == DummyNode(2, 1));
}

TEST_F(OpenArrayInitialize, EmptyOpenAfterPops) {
    for (int i = 0; i < 3; ++i) {
        open.pop();
    }
    ASSERT_TRUE(open.empty());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
