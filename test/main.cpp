#include "AVL_tree.hpp"
#include "gtest/gtest.h"
#include <chrono>
#include <fstream>

using namespace std;

// Positive testing: use valid input parameter: status should be 0
TEST(tree_creation, positive) {
    int status = 0;
    int list_size=10;
    float *list=random_list(list_size);
    struct avl_node *root=nullptr;

    status=avl_create(list,list_size,&root);

    EXPECT_EQ(status, 0);

    //Free memory
    free_tree_mem(root);
    delete list;
}

TEST(Time_complex, Positive){
    int status = 0;
    int min_order = 100;
    int max_order = 100000;

    //Se crea el archivo de resultados
    std::ofstream resultados;
    resultados.open ("time.csv");
    resultados << "Esos son los resultados de la prueba de complejidad temporal\n";
    resultados << "Prueba;Nth add;Time[us]\n";
    resultados.close();

    for (size_t index = 0; index < 10; index++) {
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

      std::ofstream outfile;
      outfile.open("time.csv", std::ios_base::app);
      outfile << index << ";" << Nth << ";" << duration.count() << endl;
      std::cout << "Check time.txt for the time complexity results" << '\n';

      //Free memory
      free_tree_mem(root);
      delete list;
    }
    EXPECT_EQ(status, 0);

}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}
