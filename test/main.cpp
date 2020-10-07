#include "AVL_tree.hpp"
#include "gtest/gtest.h"

using namespace std;

// Positive testing for creation with valid arguments, status should return AVL_SUCCESS.
TEST(Create_test, positive) {
    // Initialize status to success.
    int status = AVL_SUCCESS;
    // Define list size.
    int list_size=10;

    // Create list and initialize root to null.
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    
    // Call creation with valid list size.
    status=avl_create(list,list_size,&root);
    
    // Check status against success.
    EXPECT_EQ(status,AVL_SUCCESS);

    //Free memory
    free_tree_mem(root);
    delete list;
}

// Negative testing for creation with valid arguments, status should return AVL_INVALID_PARAM.
TEST(Create_test, negative) {
    // Initialize status to success.
    int status = AVL_SUCCESS;
    // Define list size.
    int list_size=10;

    // Create list and initialize root to null.
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    
    // Call creation with invalid list size.
    status=avl_create(list,0,&root);
    
    // Check status against invalid param.
    EXPECT_EQ(status,AVL_INVALID_PARAM);

    //Free memory
    free_tree_mem(root);
    delete list;
}

// Insert positive testing. Nodes should be added and tree balanced every time.
TEST(Insert, positive) {
    int status = AVL_SUCCESS;

    //Create empty root node
    struct avl_node *root=nullptr; 
    float val = 0;

    //Insert 10 random numbers to AVL tree
    for(int i = 0; i <= 10; i++){
      val = float(rand()%50);
      status = avl_node_add(val, &root);

      //Compare each insert status
      EXPECT_EQ(status, AVL_SUCCESS);
    }

    // Print AVL tree values
    printf("AVL tree values: \n");
    avl_print(root);
    
    //Free memory
    free_tree_mem(root);
}

// Right rotation negative testing.Can only rotate right if left children exist
TEST(Insert, rr_negative) {
    int status = AVL_SUCCESS;
    struct avl_node *root=nullptr;

    // Insert two values for only root and right children.
    avl_node_add(10, &root);
    avl_node_add(20, &root);

    // Try right rotation, should be invalid
    status = right_rotation(&root);
    EXPECT_EQ(status, AVL_INVALID_ROT);

    // Print AVL tree
    printf("AVL tree values: \n");
    avl_print(root);
    
    //Free memory
    free_tree_mem(root);
}

// Left rotation negative testing.Can only rotate left if right children exist
TEST(Insert, lr_negative) {
    int status = AVL_SUCCESS;
    struct avl_node *root=nullptr;

    // Insert two values for only root and left children.
    avl_node_add(20, &root);
    avl_node_add(10, &root);

    // Try left rotation, should be invalid
    status = left_rotation(&root);
    EXPECT_EQ(status, AVL_INVALID_ROT);

    // Print AVL tree
    printf("AVL tree values: \n");
    avl_print(root);
    
    //Free memory
    free_tree_mem(root);
}



// Positive test for getting min value of element, status should be AVL_SUCCESS
TEST(Min_test, positive) {
    int status = AVL_SUCCESS;
    int list_size=20;

    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    struct avl_node *min_node;
    
    // Create AVL tree with 20 random numbers
    avl_create(list,list_size,&root);


    // Get minimum node
    status = avl_min_get(root, &min_node);

    // Print values and min value
    printf("AVL tree values: \n");
    avl_print(root);
    printf("MIN: %f \n", min_node->value);

    // Check correct test, should be succesful
    EXPECT_EQ(status, AVL_SUCCESS);

    //Free memory
    free_tree_mem(root);
    delete list;
}

// Negative test for getting min value of element, status should be AVL_OUT_OF_RANGE
TEST(Min_test, negative) {
    int status = AVL_SUCCESS;
    int list_size=0;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    struct avl_node *min_node;

    // Create AVL tree with 0 random numbers, it's empty
    avl_create(list,list_size,&root);

    // Get minimum node
    status = avl_min_get(root, &min_node);

    // Print values and min value
    printf("AVL tree values: \n");
    avl_print(root);
    printf("MIN: %f \n", min_node->value);

    // Check correct test, should be negative testing
    EXPECT_EQ(status, AVL_OUT_OF_RANGE);

    //Free memory
    free_tree_mem(root);
    delete list;
}

// Positive test for getting max value of element, status should be AVL_SUCCESS
TEST(Max_test, positive) {
    int status = AVL_SUCCESS;
    int list_size=15;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    struct avl_node *max_node;

    // Create AVL tree with 15 random numbers
    avl_create(list,list_size,&root);

    // Get max element of tree
    status = avl_max_get(root, &max_node);

    // Print AVL tree and min value
    printf("AVL tree values: \n");
    avl_print(root);
    printf("Max: %f \n", max_node->value);

    // Status should be succesful
    EXPECT_EQ(status, AVL_SUCCESS);

    //Free memory
    free_tree_mem(root);
    delete list;
}

// Negative test for getting max value of empty tree, status should be AVL_OUT_OF_RANGE
TEST(Max_test, negative) {
    int status = AVL_SUCCESS;
    int list_size=0;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    struct avl_node *max_node;

    // Create empty node
    avl_create(list,list_size,&root);

    // Get max element of empty node
    status = avl_max_get(root, &max_node);

    // Print tree and max element
    printf("AVL tree values: \n");
    avl_print(root);
    printf("Max: %f \n", max_node->value);

    // Status should be out of range
    EXPECT_EQ(status, AVL_OUT_OF_RANGE);

    //Free memory
    free_tree_mem(root);
    delete list;
}


TEST(Print,positive) {

    // Initialize status to success.
    int status=AVL_SUCCESS;

    // Create a 10-element.
    int list_size=10;
    float *list=new float[list_size];
    int counter=0;
    // Assign the elements from 10 to a 100 in increments of 10 to the list.
    for (float index = 10; index <= 10*list_size; index+=10){
        list[counter]=index;
        counter++;
    }
    
    // Assign the well known correct output to a string.
    string correct_output="Pre-order traversal: 40 20 10 30 80 60 50 70 90 100 \n";

    // Initialize root and creat AVL tree.
    struct avl_node *root=nullptr;
    status=avl_create(list,list_size,&root);
    
    // Redirect stdout to a buffer before calling avl_print
    // to capture the printed output.
    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    
    // Call avl_print to capture the printing in the buffer.
    avl_print(root);

    // Convert the stringstream buffer to string.
    string buffer2=buffer.str();

    // Compare printed elements with the correct output and success status.
    EXPECT_EQ(status,AVL_SUCCESS);
    EXPECT_EQ(buffer2,correct_output);
    
    // Reset the stdout to console.
    std::cout.rdbuf( old );

    // Free memory.
    free_tree_mem(root);
    delete list;

}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}
