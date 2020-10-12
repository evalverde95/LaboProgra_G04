#include "AVL_tree.hpp"
#include "gtest/gtest.h"
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Positive testing for creation with valid arguments, status should return AVL_SUCCESS.
TEST(Create_test,positive) {
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
TEST(Create_test,negative) {
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

TEST(Time_complex,positive){
  int status = 0;
  float min_order = 100;
  float max_order = 100000;
  int test_quantity = 100;
  int repetition_quantity = 100;

  srand (static_cast <unsigned> (time(nullptr)));

  // Create the test result file
  ofstream resultados;
  resultados.open ("time.csv");
  resultados << "These are the time complexity test results\n";
  resultados << "Test N.;Nth add;Time[ns]\n";
  resultados.close();

  int Nth = 0;
  int median_time=0;
  float times[100];


  for (int index = 0; index < test_quantity; index++) {
    // Obtaining the strcture size
    int list_size = min_order + (int)(max_order*rand()/(RAND_MAX+min_order));

    median_time=0;
    
    // Creating the test structure
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    status=avl_create(list,list_size,&root);
    
    for (int idx_2 = 0; idx_2 < repetition_quantity; idx_2++){

      // Adding the N-th node and measuring execution time
      float new_node_value =static_cast <float>(rand());
      auto start = chrono::steady_clock::now();
      avl_node_add(new_node_value, &root);
      auto stop = chrono::steady_clock::now();

      // Saving test results (N and time)
      auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
      
      times[idx_2]= static_cast<float>(duration.count());
  
    }
    
    //Free memory
    free_tree_mem(root);
    delete list;
      
    Nth = list_size+1;

    median_time = static_cast<int>(median(times,repetition_quantity));
    ofstream results;
    results.open("time.csv", ios_base::app);
    results << index << ";" << Nth << ";" << median_time << endl;
    cout << "Time test:\t" << Nth <<"\t"<< median_time <<"\t...saved (" << index << " out of " << test_quantity << ")" << '\n';
  

  }


    EXPECT_EQ(status, 0);
  }


// Positive test for getting min value of element, status should be AVL_SUCCESS
TEST(Min_test,positive) {
    int status = AVL_SUCCESS;
    int list_size=40;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    struct avl_node *min_node;

    // Print list of values
    cout<<"List values: ";
    for (int i = 0; i < list_size; i++){
      cout<<list[i]<<" ";
    }
    cout<<endl;

    avl_create(list,list_size,&root);


    status = avl_min_get(root->rc_node, &min_node);
    printf("MIN: %f \n", min_node->value);
    EXPECT_EQ(status, AVL_SUCCESS);

    //Free memory
    free_tree_mem(root);
    delete list;
}

// Negative test for getting min value of element, status should be AVL_OUT_OF_RANGE
TEST(Min_test,negative) {
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
TEST(Max_test,positive) {
    int status = AVL_SUCCESS;
    int list_size=15;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    struct avl_node *max_node;

    // Print list of values
    cout<<"List values: ";
    for (int i = 0; i < list_size; i++){
      cout<<list[i]<<" ";
    }
    cout<<endl;

    avl_create(list,list_size,&root);

    status = avl_max_get(root, &max_node);
    printf("MAX: %f \n", max_node->value);
    EXPECT_EQ(status, AVL_SUCCESS);

    //Free memory
    free_tree_mem(root);
    delete list;
}

// Negative test for getting max value of empty tree, status should be AVL_OUT_OF_RANGE
TEST(Max_test,negative) {
    int status = AVL_SUCCESS;
    int list_size=0;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;
    struct avl_node *max_node;

    avl_create(list,list_size,&root);

    status = avl_max_get(root, &max_node);
    printf("MAX: %f \n", max_node->value);
    EXPECT_EQ(status, AVL_OUT_OF_RANGE);

    //Free memory
    free_tree_mem(root);
    delete list;
}

// Test removing a node from a tree
TEST(Node_remove_test,positive){
  int status = 0;

  // Creating the tree
  int list_size=10;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  // Removing the node that contains the first value of the random list
  status = avl_node_remove(list[0], &root);

  // Status should be AVL_SUCCESS
  EXPECT_EQ(status, AVL_SUCCESS);

  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing for a value greater than any in the tree
TEST(Node_remove_test_greater,negative){
  int status = 0;

  // Creating the tree from a random list
  int list_size=10;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  // Getting the max value and adding 1 to it.
  float inexistent_num = -1;
  for (int index = 0; index < list_size; index++) {
    float value = list[index];
    inexistent_num = ( inexistent_num > value ) ? inexistent_num : value;
  }
  inexistent_num += 1;

  // Try removing the inexistent greater value
  status = avl_node_remove(inexistent_num, &root);

  // Status should be AVL_OUT_OF_RANGE
  EXPECT_EQ(status, AVL_OUT_OF_RANGE);

  //Free memory
  free_tree_mem(root);
  delete list;
}

// Test removing a value lesser than any in the tree
TEST(Node_remove_test_lesser,negative){
  int status = 0;

  // Creating the tree
  int list_size=10;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  // Geting an inexistent smaller number to remove
  float inexistent_num = -1;

  // Test removing an inxistent lesser value
  status = avl_node_remove(inexistent_num, &root);

  // Comparing status, should be AVL_OUT_OF_RANGE
  EXPECT_EQ(status, AVL_OUT_OF_RANGE);

  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing removing a node from a empty tree
TEST(Node_remove_test_invalid,negative){
  int status = 0;

  // Creating an emty tree
  struct avl_node *root=nullptr;

  // Test removing any numbre since the tree is empty
  float inexistent_num = -1;
  status = avl_node_remove(inexistent_num, &root);

  // Status should be AVL_NOT_FOUND
  EXPECT_EQ(status, AVL_NOT_FOUND);

  //Free memory
  free_tree_mem(root);
}

// Testing search funtion
TEST(Node_search,positive){
  int status = 0;

  //Creating the tree
  int list_size=5;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  // Creating a varible to store the found node direction
  struct avl_node *found_node = nullptr;

  // Creating a value to search
  float number_to_search = list[list_size-1];

  // Test searching for the value
  status = avl_search(number_to_search, &root, &found_node);

  // Comparing status, should be AVL_SUCCESS
  EXPECT_EQ(status, AVL_SUCCESS);

  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing searching a inexisten greater number
TEST(Node_search_greater,negative){
  int status = 0;

  // Creating the tree
  int list_size=5;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  // Getting the largest value in the tree and adding 1
  float inexistent_num = -1;
  for (int index = 0; index < list_size; index++) {
    float value = list[index];
    inexistent_num = ( inexistent_num > value ) ? inexistent_num : value;
  }
  inexistent_num += 1;

  // Creating a varible to store the found node direction
  struct avl_node *found_node = nullptr;

  // Test searching for the value
  status = avl_search(inexistent_num, &root, &found_node);

  // Should be AVL_OUT_OF_RANGE
  EXPECT_EQ(status, AVL_OUT_OF_RANGE);

  //Free memory
  free_tree_mem(root);
  delete list;
}

// Test searching for a value lesser than any in the tree
TEST(Node_search_lesser,negative){
  int status = 0;

  // Creating tree
  int list_size=5;
  float *list=random_list(list_size);
  struct avl_node *root=nullptr;
  avl_create(list,list_size,&root);

  // Creating a smaller inexistent number
  float inexistent_num = -1;

  // Creating a varible to store the found node direction
  struct avl_node *found_node = nullptr;

  // Serching the inexisten value in the tree
  status = avl_search(inexistent_num, &root, &found_node);

  // Comparing status, should be AVL_OUT_OF_RANGE
  EXPECT_EQ(status, AVL_OUT_OF_RANGE);

  //Free memory
  free_tree_mem(root);
  delete list;
}

// Testing searching an empty tree
TEST(Node_search_invalid,negative){
  int status = 0;

  // Creating emty tree
  struct avl_node *root=nullptr;

  // Creating any number to search since the tree is emty
  float number_to_search = 0;

  // Creating a varible to store the found node direction
  struct avl_node *found_node = nullptr;

  // Searchin the emty tree
  status = avl_search(number_to_search, &root, &found_node);

  // Comparing status, should be AVL_INVALID_ROT
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
    stringstream buffer;
    streambuf * old = cout.rdbuf(buffer.rdbuf());

    // Call avl_print to capture the printing in the buffer.
    avl_print(root);

    // Convert the stringstream buffer to string.
    string buffer2=buffer.str();

    // Compare printed elements with the correct output and success status.
    EXPECT_EQ(status,AVL_SUCCESS);
    EXPECT_EQ(buffer2,correct_output);

    // Reset the stdout to console.
    cout.rdbuf( old );

    // Free memory.
    free_tree_mem(root);
    delete list;

}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
