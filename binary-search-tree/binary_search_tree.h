/*
     _     _                            
    | |   (_)                           
    | |__  _ _ __   __ _ _ __ _   _     
    | '_ \| | '_ \ / _` | '__| | | |    
    | |_) | | | | | (_| | |  | |_| |    
    |_.__/|_|_| |_|\__,_|_|   \__, |    
                               __/ |    
                              |___/     
                                 _      
                                | |     
         ___  ___  __ _ _ __ ___| |__   
        / __|/ _ \/ _` | '__/ __| '_ \  
        \__ \  __/ (_| | | | (__| | | | 
        |___/\___|\__,_|_|  \___|_| |_| 
                                        
                                        
             _                          
            | |                         
            | |_ _ __ ___  ___  ___     
            | __| '__/ _ \/ _ \/ __|    
            | |_| | |  __/  __/\__ \    
             \__|_|  \___|\___||___/    
                                        
*/

#include <iostream>
#include <vector>

// Binary search tree invariant:
//
// From any subtree node t, the left subtree's data values must be
// less than t's data value. The right subtree's data values must be
// greater than or equal to t's data value.

// bt_node is the binary search tree node structure.
struct bt_node {
  int data;
  bt_node* left;
  bt_node* right;
};

// init_node initializes a new bt_node from the heap using the given
// data, and two NULL children, and returns a pointer to it.
bt_node* init_node(int data);

// insert places the new_node in a proper location in the tree
// indicated by top, while obeying the invariant. On return, *top
// points to the root of the tree.
void insert(bt_node** top, bt_node* new_node);

// insert_data creates a new node with the given data value and
// inserts it similarly to insert().
void insert_data(bt_node** top, int data);

// remove removes a node from the tree whose data value matches the
// input. On return, *top points to the root of the tree. If no node
// in the tree contains the given data, this function has no effect.
void remove(bt_node** top, int data);

// contains returns true if any node in the subtree pointed to by t
// contains the given data value, false otherwise.
bool contains(bt_node* t, int data);

// get_node searches through the subtree pointed to by t for a node that
// contains the given data value. If such a node is found, a pointer
// to it is returned. Otherwise this function returns NULL.
bt_node* get_node(bt_node* t, int data);

// size returns the number of nodes in the subtree pointed to by t. If
// the tree is empty (t is NULL), it returns zero.
int size(bt_node* t);

// to_array fills an integer array to reflect the contents of the
// subtree pointed to by t. The filled array will be the same as the
// subtree's size (found with the size() function), and the order of
// the array elements are the same that is found during an inorder
// traversal of the subtree.
//
// Note: the array is created and sized before this function is
// called. You will have at least size(top) elements available, so you
// may safely index [0..size(t)-1].
void to_array(bt_node* t, int arr[]);
