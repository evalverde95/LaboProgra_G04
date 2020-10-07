#include "AVL_tree.hpp"
#include "gtest/gtest.h"
#include <chrono>
#include <fstream>

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


TEST(Time_complex, Positive){
    int status = 0;
    int min_order = 100;
    int max_order = 100000;
    int test_quantity = 3;

    // Create the test result file
    std::ofstream resultados;
    resultados.open ("time.csv");
    resultados << "These are the time complexity test results\n";
    resultados << "Test N.;Nth add;Time[us]\n";
    resultados.close();

    for (int index = 0; index < test_quantity; index++) {
      // Obtaining the strcture size
      int list_size = rand() / max_order + min_order;

      // Creating the test structure
      float *list=random_list(list_size);
      struct avl_node *root=nullptr;
      status=avl_create(list,list_size,&root);

      // Adding the N-th node and measuring execution time
      float new_node_value =static_cast <float> (rand()%max_order);
      auto start = std::chrono::steady_clock::now();
      avl_node_add(new_node_value, &root);
      auto stop = std::chrono::steady_clock::now();

      // Saving test results (N and time)
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      int Nth = list_size+1;

      std::ofstream results;
      results.open("time.csv", std::ios_base::app);
      results << index << ";" << Nth << ";" << duration.count() << endl;
      std::cout << "Time test: " << Nth << ", " << duration.count() <<  "\t...saved (" << index << " out of " << test_quantity << ")" << '\n';

      //Free memory
      free_tree_mem(root);
      delete list;
    }
    EXPECT_EQ(status, 0);

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

TEST(Node_remove_test, positive){
  int status = 0;
  int list_size=10;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  status = avl_node_remove(list[0], &root);

  EXPECT_EQ(status, 0);
  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing for a value grater than any in the tree
TEST(Node_remove_test_grater, negative){
  int status = 0;
  int list_size=10;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  float inexistent_num = -1;
  for (int index = 0; index < list_size; index++) {
    float value = list[index];
    inexistent_num = ( inexistent_num > value ) ? inexistent_num : value;
  }
  inexistent_num += 1;

  status = avl_node_remove(inexistent_num, &root);

  EXPECT_EQ(status, -2);
  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing for a value lesser than any in the tree
TEST(Node_remove_test_lesser, negative){
  int status = 0;
  int list_size=10;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  float inexistent_num = -1;

  status = avl_node_remove(inexistent_num, &root);

  EXPECT_EQ(status, -2);
  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing a invalid tree
TEST(Node_remove_test_invalid, negative){
  int status = 0;
  struct avl_node *root=nullptr;
  float inexistent_num = -1;

  status = avl_node_remove(inexistent_num, &root);

  EXPECT_EQ(status, -4);
  //Free memory
  free_tree_mem(root);
}

// Testing search funtion
TEST(Node_search, Positive){
  int status = 0;

  int list_size=5;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  struct avl_node *found_node = nullptr;
  float number_to_search = list[list_size-1];
  status = avl_search(number_to_search, &root, &found_node);

  EXPECT_EQ(status, AVL_SUCCESS);
  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing searching a inexisten greater number
TEST(Node_search_grater, Negative){
  int status = 0;

  int list_size=5;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  float inexistent_num = -1;
  for (int index = 0; index < list_size; index++) {
    float value = list[index];
    inexistent_num = ( inexistent_num > value ) ? inexistent_num : value;
  }
  inexistent_num += 1;

  struct avl_node *found_node = nullptr;
  status = avl_search(inexistent_num, &root, &found_node);

  EXPECT_EQ(status, AVL_OUT_OF_RANGE);
  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing searching a inexisten lesser number
TEST(Node_search_lesser, Negative){
  int status = 0;

  int list_size=5;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  float inexistent_num = -1;
  struct avl_node *found_node = nullptr;
  status = avl_search(inexistent_num, &root, &found_node);

  EXPECT_EQ(status, AVL_OUT_OF_RANGE);
  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing searching an invalid tree
TEST(Node_search_invalid, Negative){
  int status = 0;

  struct avl_node *root=nullptr;

  float number_to_search = 0;
  struct avl_node *found_node = nullptr;
  status = avl_search(number_to_search, &root, &found_node);

  EXPECT_EQ(status, AVL_NOT_FOUND);
  //Free memory
  free_tree_mem(root);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
