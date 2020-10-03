#include "AVL_tree.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
 
#define MAX_RAND_VALUE 100
using namespace std;


int max(
  int height_1,
  int height_2){
    return ( height_1 > height_2 ) ? height_1 : height_2;
}

int min(
  int status_1,
  int status_2){

    return (status_1<status_2) ? status_1:status_2;
}


int min3(
  int status_1,
  int status_2,
  int status_3){
    int temp_status = (status_1<status_2) ? status_1:status_2;
    return (status_3<temp_status) ? status_3:temp_status;
}


int get_height(
  struct avl_node *current_node){
      
    // Ending condition, when the node is inexistent.
    if (current_node==nullptr){
        return 0;
    }

    // Get left and right side heights.
    int left_height=get_height(current_node->lc_node);
    int right_height=get_height(current_node->rc_node);
    
    // Return max plus current node.
    return max(left_height,right_height)+1;
}


int get_balance(
  struct avl_node *current_node){

    // Get left and right side heights.
    int left_height = get_height(current_node->lc_node);
    int right_height = get_height(current_node->rc_node);

    // Return height difference.
    return left_height-right_height;

}

int new_node(
  struct avl_node **node_ptr,
  float value){

    // Assign pointing address.
    *node_ptr=new struct avl_node;

    // Initially no children, use value given.
    (*node_ptr)->lc_node=nullptr;
    (*node_ptr)->rc_node=nullptr;
    (*node_ptr)->value=value;

    // Return success state.
    return AVL_SUCCESS;

}

int left_rotation(
  struct avl_node **rot_top_node){
    
    // Left rotations require right children.
    if ((*rot_top_node)->rc_node==nullptr){
      return AVL_INVALID_ROT;
    }

    // Get relevant items pointers.
    struct avl_node *rc=(*rot_top_node)->rc_node;
    struct avl_node *lc_of_rc=rc->lc_node;

    // Guard against nullptr reference.
    if (rc==nullptr){
      lc_of_rc=nullptr;
    }
    else{
      lc_of_rc=rc->lc_node;
    }    

    // Perform rotation.
    rc->lc_node=(*rot_top_node);
    (*rot_top_node)->rc_node=lc_of_rc;

    // Update rot_top_node.
    (*rot_top_node)=rc;

    // Return success.
    return AVL_SUCCESS;

}

int right_rotation(
  struct avl_node **rot_top_node){

    // Right rotations require left children.
    if ((*rot_top_node)->lc_node==nullptr){
      return AVL_INVALID_ROT;
    }

    // Get relevant items pointers.
    struct avl_node *lc=(*rot_top_node)->lc_node;
    struct avl_node *rc_of_lc;

    // Guard against nullptr reference.
    if (lc==nullptr){
      rc_of_lc=nullptr;
    }
    else{
      rc_of_lc=lc->rc_node;
    }
    
    // Perform rotation.
    lc->rc_node=(*rot_top_node);
    (*rot_top_node)->lc_node=rc_of_lc;

    // Update rot_top_node.
    *rot_top_node=lc;

    // Return success.
    return AVL_SUCCESS;

}


int avl_create(
  float           *in_number_list,
  int              list_size,
  struct avl_node **new_root_node){
    
    // Initialize status as success.
    int status=AVL_SUCCESS;

    // Iterate over all the list elements.
    for (int index = 0; index < list_size; index++){

      // Add current list element to tree.
      status=avl_node_add(in_number_list[index],new_root_node);
      
      // If unsuccessful return with the current status.
      if (status!=AVL_SUCCESS){
        return status;
      }      
    }

    // If all elements added with success, return success.
    return AVL_SUCCESS;

}

int avl_node_add(
  float num,
  struct avl_node **new_root){

    int status = AVL_SUCCESS;
    int status_1 = AVL_SUCCESS;
    int status_2 = AVL_SUCCESS;
    
    // If nullptr then create the new node.
    if (*new_root == nullptr){  
        status= new_node(new_root,num); 
        return status;
    } 

    // Num smaller than current node.
    if (num < (*new_root)->value){        
        status=avl_node_add(num,&((*new_root)->lc_node));         
    }

    // Num greater than current node.
    else if (num > (*new_root)->value){        
        status=avl_node_add(num,&((*new_root)->rc_node));      
    }
    else {
        // Ignore repeated element.
        return AVL_SUCCESS; 
    }
    // If invalid state, return immediately (skip balancing).
    if (status!=0){
        return status;
    }
       
    // Get balance factor.
    int balance = get_balance(*new_root); 
      
    // Left Left Case.
    if (balance > 1 && num < (*new_root)->lc_node->value){
        status_1=right_rotation(new_root); 
        return min(status,status_1);        
    } 
  
    // Right Right Case.
    if (balance < -1 && num > (*new_root)->rc_node->value){
        status_1 = left_rotation(new_root); 
        return min(status,status_1);
    }
  
    // Left Right Case.
    if (balance > 1 && num > (*new_root)->lc_node->value){ 
        status_1=left_rotation(&((*new_root)->lc_node)); 
        status_2=right_rotation(new_root); 
        return min3(status,status_1,status_2);
    } 
  
    // Right Left Case.
    if (balance < -1 && num < (*new_root)->rc_node->value){ 
        status_1=right_rotation(&((*new_root)->rc_node)); 
        status_2=left_rotation(new_root); 
        return min3(status,status_1,status_2);
    } 
  
    // Return status.
    return status; 

}


float *random_list(
  int list_size){
  
  // Allocate memory for the list.
  float* list=new float[list_size];

  // Initialize seed for random numbers.
  srand(time(nullptr));

  // Declare random value for generation.
  float random_value;

  // Iterate over the list size.
  for (int index = 0; index < list_size; index++){

    // Generate a random float number.
    random_value=static_cast <float> (rand()%MAX_RAND_VALUE);
    // Add random number to list.
    list[index]=random_value;
  }
  
  // Return list pointer.
  return list;

}

void free_tree_mem(
  struct avl_node *root_node){
    if (root_node!=nullptr){
        free_tree_mem(root_node->lc_node);
        free_tree_mem(root_node->rc_node);        
        delete root_node;
    }

}


int avl_print(
  struct avl_node  *in_root){
    
    //   Pre order traversal.
    if (in_root!=nullptr){
        cout<<in_root->value<<endl;
        avl_print(in_root->lc_node);
        avl_print(in_root->rc_node);        
    }
    
    // Return success.
    return AVL_SUCCESS;

}

