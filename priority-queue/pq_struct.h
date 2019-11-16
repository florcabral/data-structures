// 
// pq_struct.h
// 
// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
//
// You will turn in this file and pq.cpp.
//
// Your Name: Florencia Cabral

#ifndef pq_struct_h
#define pq_struct_h

// define the structure of the pq as a double-linked list
// this way we can access both the previous and next items in the queue
struct pq {
    std::string data;
    int priority;
    pq* prev;
    pq* next;
};

#endif
