#include "AVL_tree.hpp"
#include "gtest/gtest.h"

using namespace std;

// Positive testing: use valid input parameter: status should be 0
TEST(helloworld, positive) {
    int status = 0;
    int list_size=10;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    status=avl_create(list,list_size,root);
    

    EXPECT_EQ(status, 0);

    //Free memory
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
