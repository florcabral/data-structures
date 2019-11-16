//
// binary_search_tree.cpp
//
// Please refer to binary_search_tree.h for documentation.
//

#include "binary_search_tree.h"

// init_node initializes a new bt_node from the heap using the given
// data, and two NULL children, and returns a pointer to it.
bt_node* init_node(int data) {
    bt_node* my_node = new bt_node;       // creates new node
    my_node->data = data;                 // assign data to new node
    my_node->left = NULL;
    my_node->right = NULL;                // node is the only element in the list, has left and right null children
    return my_node;
}

void insert(bt_node** top, bt_node* new_node) {
    
    // if inserting at the root of the tree
      if (*top == NULL) {      
          *top = new_node;
          new_node->left = NULL;
          new_node->right = NULL;
      }
    
      // otherwise, check left if data < cursor, right if data > cursor
      else {
          bt_node* cursor = *top;
          while (cursor != NULL) {
              if (new_node->data < cursor->data) {
                  if (cursor->left == NULL) {
                      cursor->left = new_node;
                      cursor = NULL;
                  }
                  else { 
                      cursor = cursor->left;
                      }
              }
              else {
                  if (cursor->right == NULL) {
                      cursor->right = new_node;
                      cursor = NULL;
                      }
                  else {
                      cursor = cursor->right;
                      new_node->left = NULL;
                      new_node->right = NULL;
                      }
                  }
              }
          }
      }
      

void insert_data(bt_node** top, int data) {
  
      bt_node* my_node = init_node(data);
    
    // if inserting at the root of the tree
      if (*top == NULL) {      
          *top = my_node;
          my_node->left = NULL;
          my_node->right = NULL;
      }
      
    // otherwise, check left if data < cursor, right if data > cursor
      else {
          bt_node* cursor = *top;
          while (cursor != NULL) {
              if (my_node->data < cursor->data) {
                  if (cursor->left == NULL) {
                      cursor->left = my_node;
                      cursor = NULL;
                  }
                  else { 
                      cursor = cursor->left;
                      }
              }
              else {
                  if (cursor->right == NULL) {
                      cursor->right = my_node;
                      cursor = NULL;
                      }
                  else {
                      cursor = cursor->right;
                      my_node->left = NULL;
                      my_node->right = NULL;
                      }
                  }
              }
          }
      }
    
// helper function to find the successor for removing node w/2 children
bt_node* findsuccessor(bt_node* cursor) {

if (cursor->left == NULL) {
    return cursor;
}
else {
    // call recursively, moving left until reaching leftmost node
    return findsuccessor(cursor->left);
}
}

void remove(bt_node** top, int data) {

  bt_node* cursor = *top;
  bt_node* parent;
    
 if (cursor == NULL) {
     return;
  }
    
    while (cursor != NULL) {
        if (data == cursor->data) {

     // case 1: leaf (no children)
     if (cursor->left == NULL && cursor->right == NULL) {
        if (parent->left == cursor) {
            parent->left = NULL;
            delete cursor;
            return;
        }
        else {
            parent->right = NULL;
            delete cursor;
            return;
        }
     }
      
     // case 2: one child
                      
         if (parent->right == cursor) {
                         
             if (cursor->left == NULL && cursor->right != NULL) {
                 // if cursor is parent's right child
                 if (parent->right == cursor) {
                 
                     // assign the parent's right child to cursor's single child (right)
                     bt_node* temp = cursor; 
                     parent->right = cursor->right;
                     delete temp;
                     }
                 
                 if (parent->left == cursor) {
                 
                     // assign the parent's left child to cursor's single child (right)
                     bt_node* temp = cursor; 
                     parent->left = cursor->right;
                     delete temp;
                     }
             }
         }
          if (parent->left == cursor) {
             
             if (cursor->left != NULL && cursor->right == NULL) {
                 
                 if (parent->right == cursor) {
                     
                 // assign the parent's right child to cursor's single child (left)
                 bt_node* temp = cursor; 
                 parent->right = cursor->left;
                 delete temp;
             }
                 if (parent->left == cursor) {
         
                 // assign the parent's left child to cursor's single child (left)
                 bt_node* temp = cursor; 
                 parent->left = cursor->left;
                 delete temp;
             }
           }
         }
       
        
          // case 3: 2 children  
        
        if (cursor->left != NULL && cursor->right != NULL) {           
            bt_node* suc = findsuccessor(cursor->right);
            cursor->data = suc->data;
            remove(&cursor->right,suc->data);
            
        }
        }
        
          // if the data isn't matching node data, move left if data < cursor, right if data > cursor
         else {
            parent = cursor;
            if (data >= cursor->data){
                parent = cursor;
                cursor = cursor->right;
            }
            else {
                parent = cursor;
                cursor = cursor->left;
            }
        }    
    }
}


bool contains(bt_node* t, int data) {  
    
    if (t == NULL) {
        return NULL;
    }
    // returns true if the node w/matching data was found
    if (t->data == data) {
        return true;
    }
    // if search data is smaller than current data, go left
    if (data < t->data) {
        return get_node(t->left, data);
    }
    // if search data is larger than current data, go right
    else {
        return get_node(t->right, data);
    }
}

bt_node* get_node(bt_node* t, int data) {
  
    if (t == NULL) {
        return NULL;
    }
    // returns the node if it has macthing data
    if (t->data == data) {
        return t;
    }
    // if search data is smaller than current data, go left
    if (data < t->data) {
        return get_node(t->left, data);
    }
    // if search data is larger than current data, go right
    else {
        return get_node(t->right, data);
    }

}

int size(bt_node* t) {
    
    int sizecount = 1; 
    
    // first move left and add to sizecount for each node
    if (t->left != NULL) {
       sizecount += size(t->left);
    }
    // then move right and do the same
    if (t->right != NULL) {
        sizecount += size(t->right);
    }
    return sizecount;
}
 

int index = 0;

void to_array(bt_node* t, int arr[]) 
{

  if (t != NULL) {

      // recursively call function moving left
      to_array(t->left, arr);
      
      // add the current node to array, increase the index by 1
      arr[index] = t->data;
      index++;

      // recursively call function moving right
      to_array(t->right, arr);
  }
}



    
    

        
