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
    int list_size=40;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    struct avl_node *min_node;


    avl_create(list,list_size,&root);



    status = avl_min_get(root->rc_node, &min_node);
    printf("MIN: %f \n", min_node->value);
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

    avl_create(list,list_size,&root);

    status = avl_min_get(root, &min_node);
    printf("MIN: %f \n", min_node->value);
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

    avl_create(list,list_size,&root);

    status = avl_max_get(root, &max_node);
    printf("MIN: %f \n", max_node->value);
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

    avl_create(list,list_size,&root);

    status = avl_max_get(root, &max_node);
    printf("MIN: %f \n", max_node->value);
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
