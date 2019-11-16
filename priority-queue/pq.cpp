//
// pq.cpp
//
// Implemented a PQ as a double linked list
//


#include <string>
#include "pq.h"
#include "pq_struct.h"

// initializes a new priority queue
pq* init_priority_queue() {
    pq* init_queue = new pq();
    init_queue->data = "";
    init_queue->priority = 0;
    init_queue->prev = NULL;
    init_queue->next = NULL;
    return init_queue;
}

// insert function finds the appropriate insert location for the new element, according to priority value
// it inserts the element before elements with lower priority, and after elements with higher priority
// if another existing element has the same priority, this implementation inserts after it
void insert(pq* &queue, string text, float priority) {
    
    // create the new element to insert, assign it the value and priority
    pq* new_element = init_priority_queue();
    new_element->data = text;
    new_element->priority = priority;
    
    // base case: empty queue, just insert the element, will have the trivially highest priority
    if (queue == NULL) {
        queue = new_element;
    }
    
    else {
    
    // initialize cursor to traverse queue
    pq* cursor = queue;
    
    while (cursor != NULL) {
        
        // first case -> same priority, insert after
        if (cursor->priority == priority) {
            new_element->prev = cursor;
            new_element->next = cursor->next;
            cursor->next = new_element;
            return;
        }
            
        // second case-> higher priority, insert before cursor
        if (cursor->priority < priority) {
            new_element->prev = cursor->prev;
            cursor->prev = new_element;
            new_element->next = cursor;
            
            // subcase: new element might be head of list
            // as long as new element is not the first in queue, update previous->next pointer
            if (new_element->prev != NULL) {
                new_element->prev->next = new_element;
            }
            // if it is the first, update the queue head
            else {
                queue = new_element;
            }
            return;
        }
        
        // else: continue searching
        cursor = cursor->next;        
    }
    
    // reached end of list, no element with lower priority. Insert as last element
    if (cursor == NULL) {
        cursor->prev->next = new_element;
        new_element->next = cursor;
    }
    }
}   


// remove function accesses, deletes and returns the highest priority element in the queue
// if queue is empty, returns an empty string
string remove(pq* &queue) {
    
    // base case: empty queue, just return an empty string
    if (queue == NULL) {
        return "";
    }
    
    // just remove highest priority element
        std::string remove_data = queue->data;
        pq* thisone = queue;
        queue = queue->next;   // update next pointer
        delete thisone;   // don't forget to delete
    
    return remove_data;

}


// peek function accesses and returns the highest priority element in the queue
// if queue is empty, returns NULL
string peek(pq* &queue) {
    if (queue == NULL) {
        return NULL;
    }
    else {
        return queue->data;
    }
}
