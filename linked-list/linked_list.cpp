/*

  linked_list.cpp

 */

#include "linked_list.h"

using namespace std;

// create a new node structure that points to NULL and holds the
// provided integer. return a pointer to that new node.
node* init_node(int data) {
    node* my_node = new node;       // creates new node
    my_node->data = data;           // assign data to new node
    my_node->next = NULL;           // node is the only element in the list, points to null
  return my_node;
}

// create a space-separated string representing the contents of the
// list, in the same order they are found beginning from the head of
// the list. return that string object.  For example, this might
// return "" (the empty string) if the list is empty, or it might
// return "1 7 3" or "1 7 3 " (note the space at the end, you can have
// that there and it is OK).
string report(node* head) {
    string node_report;          // creates a string variable to store the report
    node* cursor = head;         // create pointer to head of list
    if (cursor == NULL) {        // if list empty, return empty string
        return "";
    }
    else {                // move through list, retrieve nodes' data values, transform them to strings and append to report
        while (cursor != NULL) {
            node_report = node_report+(to_string(cursor->data)+" ");
            cursor = cursor->next;
        }
        return node_report;
    }
}
        
// insert an integer into the list pointed to by top. the resulting
// list is one element longer, and the newly appended node has the
// given data value. consider using the 'append' function to help.
void append_data(node** top, int data) {
    node* my_node = init_node(data);           // calls the init_node function to create a node, passes the data into it
    append(top, my_node);                      // calls the append function to add the new node to list
}

// this is the same as append_data, except we're adding a node, rather
// than a value. 
void append(node** top, node* new_node) {
  if (*top == NULL) {                          // if list is empty, append new_node to the head of the list
      *top = new_node;
  } else {                                     // if list is not empty, move through the list to reach the end
      node* cursor = *top;
      while (cursor->next != NULL) {
          cursor = cursor->next;
      }
      cursor->next = new_node;                 // once found end of list, point the last node's pointer to new_node
      cursor = new_node;
    }
}

// similar to append_data. insert a new node that contains the given
// data value, such that the new node occupies the offset
// indicated. Any nodes that were already in the list at that offset
// and beyond are shifted down by one. For example if the list
// contains 23, 74, 93, and we insert 42 at index 1, the resulting
// list should be 23, 42, 74, 93.
void insert_data(node** top, int offset, int data) {
    node* my_node = init_node(data);           // call init_node to create new node and pass data to it
    node* cursor = *top;
    int count = 0;                             // initialize counter to loop through list
    if (offset == 0) {       // if inserting at head of list, add node to top pointer, and point new node to the now second node
      *top = my_node;
      my_node->next = cursor;
    }
    if (cursor == NULL) {         // if list is empty, insert at head
      *top = my_node;
     }
    while (cursor->next != NULL) {        // loop through non-empty list
        if (count == offset-1) {          // when found the offset, point previous node's pointer to new node
            node* temp = cursor->next;    // store next node as temp
            cursor->next = my_node;       // add pointer to new node, and point it to temp
            my_node->next = temp;
            break;
        }         
        else {                            // keep looping and counting
            cursor = cursor->next;
            count++;
        }
    }
    if (cursor->next == NULL && count == offset-1) {     // if offset is the end of list, insert at the end
        cursor->next = my_node;
    }
}
  

// this is the same as insert_data, except we're inserting a node,
// rather than a value.
void insert(node** top, int offset, node* new_node) {
    node* cursor = *top;
    int count = 0;                             // initialize counter
    if (offset == 0) {                         // if inserting at head of list, point new node to the now second node
        *top = new_node;     
        new_node->next = cursor;
    }
    if (cursor == NULL) {                      // if list is empty, insert at head
      *top = new_node;
     }
    while (cursor->next != NULL) {             // move through non-empty list,
        if (count == offset-1) {               // when found the offset, point previous node's pointer to new node
            node* temp = cursor->next;         // store next node as temp
            cursor->next = new_node;           // add pointer to new node, and point it to temp
            new_node->next = temp;
            break;
        }         
        else {                                 // keep moving forward and counting
            cursor = cursor->next;
            count++;
        }
    }
    if (cursor->next == NULL && count == offset-1) {     // if offset is the end of list, point last node's pointer to new node
        cursor->next = new_node;
    }
}

// remove the node indicated by the given offset. For example if our
// list contains 23, 74, 93, and we remove offset 1, the resulting
// list should then contain 23, 93.
void remove(node** top, int offset) {
    node* cursor = *top;
    int count = 0;                         // initialize counter
    if (offset == 0) {                     // if removing head of list,
        *top = cursor->next;               // point top to second node
        delete cursor;                     // delete first node, freeing its memory
    }
    while (cursor != NULL) {               // move through non-empty list
        if (count == offset-1) {           
            node* temp = cursor->next;     // when found the offset, point previous node's pointer to temp node
            cursor->next = cursor->next->next;    // point cursor to 2 nodes ahead 
            delete temp;                   // delete temp node, freeing its memory
            break;
        }
    else if (cursor->next == NULL && count == offset-1) {       // if deleting from the end of list, and found offset
        delete cursor;                                          // delete current node
        break;
    }
    else {
        cursor = cursor->next;                                  // keep moving forward and counting
        count++;
        }
    }
}
    
// report the number of nodes in the linked list pointed to by head.
int size(node* head) {
    int node_size = 0;                               // initialize int variable to store list size
    node* cursor = head;                             
    if (cursor == NULL) {                            // if list is empty, return size 0
        return 0;
    }
    else {
        while (cursor != NULL) {                     // move through non-empty list
            node_size++;                             // add 1 to node size for every node
            cursor = cursor->next;
        }
        return node_size;
    }
}    

// return true if the linked list pointed to by head contains a node
// with the specified value.
bool contains(node* head, int data) {
    node* cursor = head;                            
    if (cursor == NULL) {                            // if list is empty return false, node won't be there
        return false;
    }
    while (cursor != NULL) {                         // move through non-empty list
        if (cursor->data == data) {                  // if node's data matches data of interest, return true
            return true;
        }
        else {                                       // keep moving forward
            cursor = cursor->next;            
        }
    }
    return false;                                   // if didn't find it, return false
}

