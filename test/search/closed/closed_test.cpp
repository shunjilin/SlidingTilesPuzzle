#include "closed.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct DummyNode {
    int id;
    int heuristic_value = 0;
    int cost = 0;

    DummyNode(int id, int heuristic_value, int cost) :
        id(id),
        heuristic_value(heuristic_value),
        cost(cost) {}
    
    int getHeuristicValue() const {
        return heuristic_value;
    }

    int getCost() const {
        return cost;
    }

    bool operator==(DummyNode const & rhs) const {
        return id == rhs.id;
    }    
};

// overload default hash
namespace std
{
    template<>
    struct hash<DummyNode>
    {
        size_t
        operator()(const DummyNode& node) const
        {
            return hash<int>()(node.id);
        }
    };
}

class ClosedInitialize : public testing::Test {
public:
    DummyNode node1 = DummyNode{0, 1, 2}; // f-value 3
    DummyNode node2 = DummyNode{1, 1, 2}; // f-value 3
    DummyNode node3 = DummyNode{2, 1, 2}; // f-value 3
    Closed<DummyNode> closed;

    virtual void SetUp() {
        closed.insert(node3);
        closed.insert(node1);
        closed.insert(node2);
    }
};

TEST_F(ClosedInitialize, insertUniqueNode) {
    auto node = DummyNode{3, 1, 2};
    // insert return true when node needs to be expanded
    ASSERT_TRUE(closed.insert(node));
}

TEST_F(ClosedInitialize, insertNonUniqueNode) {
    auto node = DummyNode{0, 2, 1};
    ASSERT_FALSE(closed.insert(node));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

