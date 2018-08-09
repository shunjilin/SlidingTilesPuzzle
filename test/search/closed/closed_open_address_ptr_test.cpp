#include "closed_open_address_ptr.hpp"
#include <memory>
#include <optional>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct DummyNode {
    int id;
    int f_value = 0;
    std::shared_ptr<DummyNode> parent_node = nullptr;

    DummyNode() : id(-1), f_value(-1) {}

    DummyNode(int id, int f_value) :
        id(id),
        f_value(f_value) {}

    bool operator==(DummyNode const & rhs) const {
        return id == rhs.id;
    }
    bool operator !=(DummyNode const & rhs) const {
        return id != rhs.id;
    }
};

int getF(DummyNode const & node) {
    return node.f_value;
}

std::optional<DummyNode> getParent(DummyNode const & node) {
    if (node.parent_node) {
        return *node.parent_node;
    }
    return {};
}

// overload default hash
namespace std
{
    template<>
    struct hash<DummyNode>
    {
        size_t
        operator()(const DummyNode& node) const
        {
            return 0; // force collision
        }
    };
}

class ClosedInitialize : public testing::Test {
public:
    DummyNode node0 = DummyNode{0, 3}; // f-value 3
    DummyNode node1 = DummyNode{1, 3}; // f-value 3
    DummyNode node2 = DummyNode{2, 3}; // f-value 3
    ClosedOpenAddressPtr<DummyNode, std::hash<DummyNode>, 100> closed;

    virtual void SetUp() {
        closed.insert(&node2);
        closed.insert(&node0);
        closed.insert(&node1);
    }
};

TEST_F(ClosedInitialize, correctSizeOnInserts) {
    ASSERT_EQ(closed.size, 3);
}

TEST_F(ClosedInitialize, insertUniqueNode) {
    auto node = DummyNode{3, 3};
    // insert return true when node needs to be expanded
    ASSERT_TRUE(closed.insert(&node));
}

TEST_F(ClosedInitialize, insertNonUniqueNode) {
    auto node = DummyNode{0, 3};
    ASSERT_FALSE(closed.insert(&node));
}

// inserting non unique node with lower f-value triggers reopening
TEST_F(ClosedInitialize, Reopening) {
    auto node = DummyNode{0, 2};
    ASSERT_TRUE(closed.insert(&node));
}

TEST_F(ClosedInitialize, RebuildPath) {
    DummyNode node3 = DummyNode{3, 0};
    DummyNode node4 = DummyNode{4, 0};
    node4.parent_node = std::make_shared<DummyNode>(node3);
    DummyNode node5 = DummyNode{5, 0};
    node5.parent_node = std::make_shared<DummyNode>(node4);
    EXPECT_TRUE(closed.insert(&node3));
    EXPECT_TRUE(closed.insert(&node4));
    EXPECT_TRUE(closed.insert(&node5));
    ASSERT_THAT(closed.getPath(&node5),
                testing::ElementsAre(node3, node4, node5));
}


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

