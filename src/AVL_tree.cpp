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
      
    if (current_node==nullptr){
        return 0;
    }

    int left_height=get_height(current_node->lc_node);
    int right_height=get_height(current_node->rc_node);
    
    return max(left_height,right_height)+1;
}


int get_balance(
  struct avl_node *current_node){

    int left_height = get_height(current_node->lc_node);
    int right_height = get_height(current_node->rc_node);
    return left_height-right_height;

}

struct avl_node *new_node(
  float value){

    struct avl_node *node_ptr=new avl_node;
    //(struct avl_node*)malloc(sizeof(struct avl_node));
    node_ptr->lc_node=nullptr;
    node_ptr->rc_node=nullptr;
    node_ptr->height=1;
    node_ptr->value=value;

    return node_ptr;

}

int left_rotation(
  struct avl_node *rot_top_node){

    if (rot_top_node->lc_node==nullptr){
        return AVL_INVALID_ROT;
    }
    

    struct avl_node *lc=rot_top_node->lc_node;
    struct avl_node *rc_of_lc=lc->rc_node;

    lc->rc_node=rot_top_node;
    rot_top_node->lc_node=rc_of_lc;

    lc->height=get_height(lc);
    rot_top_node->height=get_height(rot_top_node);

    // Update rot_top_node 
    rot_top_node=lc;

    return AVL_SUCCESS;

}

int right_rotation(
  struct avl_node *rot_top_node){

    if (rot_top_node->rc_node==nullptr){
        return AVL_INVALID_ROT;
    }

    struct avl_node *rc=rot_top_node->rc_node;
    struct avl_node *lc_of_rc=rc->lc_node;

    rc->lc_node=rot_top_node;
    rot_top_node->rc_node=lc_of_rc;

    rc->height=get_height(rc);
    rot_top_node->height=get_height(rot_top_node);

    // Update rot_top_node 
    rot_top_node=rc;

    return AVL_SUCCESS;

}


int avl_create(
  float           *in_number_list,
  int              list_size,
  struct avl_node *new_root_node){

    int status=AVL_SUCCESS;

    for (int index = 0; index < list_size; index++){
      status=avl_node_add(in_number_list[index],new_root_node);
      //cout<<new_root_node->value<<endl;
      
      if (status!=AVL_SUCCESS){
        return status;
      }
      
    }

    
    return AVL_SUCCESS;

}

int avl_node_add(
  float num,
  struct avl_node *new_root){

    int status = AVL_SUCCESS;
    int status_1 = AVL_SUCCESS;
    int status_2 = AVL_SUCCESS;
    //check input type


    if (new_root == nullptr){
        new_root = new_node(num); 
        //cout<<new_root->value<<endl;
        return AVL_SUCCESS;
    } 
  
    if (num < new_root->value){
        //cout<<"Before: "<<new_root->lc_node<<" After: ";
        status=avl_node_add(num,new_root->lc_node); 
        //cout<<new_root->lc_node<<endl;
    }

    else if (num > new_root->value){
        //cout<<"Before: "<<new_root->rc_node<<" After: ";
        status=avl_node_add(num,new_root->rc_node);  
        //cout<<new_root->rc_node<<endl;
    }
    else {
        return AVL_SUCCESS; 
    }
  
    new_root->height=get_height(new_root);
  
    
    int balance = get_balance(new_root); 
  
    
  
    // Left Left Case 
    if (balance > 1 && num < new_root->lc_node->value){
        status_1=right_rotation(new_root); 
        return min(status,status_1);
        
    } 
  
    // Right Right Case 
    if (balance < -1 && num > new_root->rc_node->value){
        status_1 = left_rotation(new_root); 
        return min(status,status_1);
    }
  
    // Left Right Case 
    if (balance > 1 && num > new_root->lc_node->value){ 
        status_1=left_rotation(new_root->lc_node); 
        status_2=right_rotation(new_root); 
        return min3(status,status_1,status_2);
    } 
  
    // Right Left Case 
    if (balance < -1 && num < new_root->rc_node->value){ 
        status_1=right_rotation(new_root->rc_node); 
        status_2=right_rotation(new_root); 
        return min3(status,status_1,status_2);
    } 
  
    // Return previous status
    return status; 

}


float *random_list(
  int list_size
){
  float* list=new float[list_size];

  srand(time(nullptr));
  float random_value;

  for (int index = 0; index < list_size; index++){
    random_value=static_cast <float> (rand()%MAX_RAND_VALUE);
    list[index]=random_value;
  }
  
  return list;

}


int avl_print(
  struct avl_node  *in_root){
    //   Pre order traversal
    if (in_root!=nullptr)
    {
        cout<<in_root->value<<endl;
        avl_print(in_root->lc_node);
        avl_print(in_root->rc_node);        
    }
    
    return AVL_SUCCESS;

}

