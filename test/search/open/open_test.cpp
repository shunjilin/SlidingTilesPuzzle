#include "open.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct DummyNode {
    int heuristic_value = 0;
    int cost = 0;

    DummyNode(int heuristic_value, int cost) :
        heuristic_value(heuristic_value),
        cost(cost) {}
    
    int getHeuristicValue() const {
        return heuristic_value;
    }

    int getCost() const {
        return cost;
    }

    bool operator==(DummyNode const & rhs) const {
        return heuristic_value == rhs.heuristic_value &&
            cost == rhs.cost;
    }
};

class OpenInitialize : public testing::Test {
public:
    DummyNode node1 = DummyNode{0, 0};
    DummyNode node2 = DummyNode{1, 1};
    DummyNode node3 = DummyNode{1, 2};

    Open<DummyNode> open;

    virtual void SetUp() {
        open.push(node3);
        open.push(node1);
        open.push(node2);
    }
};

TEST_F(OpenInitialize, PopLowestFValNode) {
    ASSERT_TRUE(open.pop() == DummyNode(0, 0));
}

TEST_F(OpenInitialize, EmptyOpenAfterPops) {
    for (int i = 0; i < 3; ++i) {
        open.pop();
    }
    ASSERT_TRUE(open.empty());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
