// hash.cpp

#include "hash.h"
#include <iostream>

using namespace std;

// init_table creates and initializes a hash_table structure and
// returns a pointer to it. see the hash_table documentation for
// details on the fields and their expected default values.
hash_table* init_table(unsigned int cap) {
    
    // allocate memory for new hashtable, initialize its attributes
    hash_table* tbl = new hash_table();
    tbl->capacity = cap;
    tbl->size = 0;
    tbl->occupied = 0;

    // run through array of hash node pointers, initialize them all to NULL
    hash_node** newtable = new hash_node*[cap];
    for (int i = 0; i < cap; i++) {
        newtable[i] = NULL;
    }

    tbl->table = newtable;

    // table will use hash and bucket functions to store keys
    tbl->hash_func = djb2;
    tbl->bucket_func = modulo_bucket_func;
    return tbl;
}

// init_node creates and initializes a hash_node that will occupy a
// hash table bucket. see the hash_node documentation for more info.
hash_node* init_node(std::string key, unsigned int hashcode, std::string val) {
    
    // initialize new hash node and its attributes
    hash_node* new_node = new hash_node();
    new_node->deleted = false;
    new_node->key = key;
    new_node->hashcode = hashcode;
    new_node->value = val;
    return new_node;
}

// set_kvp establishes a mapping between the given key and value pair
// in the provided hash table. if the key (as identified by its hash
// code) is already in the hash table, its value is potentially
// updated. otherwise a new key/value pair is added to the hash table.
//
// on exit, the size and occupancy of the hash table is increased if a
// new key/value pair was added.
//
// if there is no room in the hash table, return false. do not resize
// the table.
//
// the return value should be true unless there was no room in the
// hash table.
bool set_kvp(hash_table* tbl, string key, string value) {
    
    // if there's no room, just return false
    if (tbl->occupied == tbl->capacity) {
        return false;
    }

    // find the hashcode and bucket for the given key
    unsigned int hashcode = djb2(key);
    unsigned int bucket = modulo_bucket_func(hashcode, tbl->capacity);

    // run through hashtable, find the location to insert key
    // cover case where bucket is full, apply linear probing
    while (tbl->table[bucket] != nullptr) {
        if (tbl->table[bucket]->hashcode == hashcode) {
            tbl->table[bucket]->value = value;
            return true;
        }
        if (bucket == tbl->capacity) {
            bucket = 0;
        } else {
            bucket++;
        }
    }
    
    tbl->table[bucket] = init_node(key, hashcode, value);
    
    // size and occupancy of the hash table is increased if a new key/value pair was added
    tbl->occupied++;
    tbl->size++;
    return true;
}

// load returns a load factor describing how 'full' the table
// is. because we are using linear probing, which leaves 'deleted'
// hash nodes sitting around, it is reasonable to use occupied divided
// by capacity. you can alternately use size divided by capacity,
// which is a more canonical definition of hashtable load. either will
// work with the unit tests.
float load(hash_table* tbl) {
    
    // compute the occupancy/capacity value
    float loadfactor = (float)tbl->occupied / (float)tbl->capacity;

    return loadfactor;
}

// from key, get value
// basically you're consulting the hash table
string get_val(hash_table* tbl, std::string key) {

    // find the hashcode and bucket for the given key
    unsigned int hashcode = djb2(key);
    unsigned int bucket = modulo_bucket_func(hashcode, tbl->capacity);

    // if the keys match, return the key's value
    while (tbl->table[bucket] != nullptr) {
        if (tbl->table[bucket]->hashcode == hashcode && tbl->table[bucket]->deleted == false) {
            return tbl->table[bucket]->value;
        }
        bucket++;
    }
    // if not found, return empty string
    return "";
}

// contains returns true if the table has a non-deleted node whose
// hashcode matches the given key's hashcode.
bool contains(hash_table* tbl, std::string key) {

    // find the hashcode and bucket for the given key
    unsigned int hashcode = djb2(key);
    unsigned int bucket = modulo_bucket_func(hashcode, tbl->capacity);

    // if the keys match, return the key's value
    while (tbl->table[bucket] != nullptr) {
        if (tbl->table[bucket]->hashcode == hashcode && tbl->table[bucket]->deleted == false) {
            return true;
        }
        bucket++;
    }
    return false;
}

// remove marks as 'deleted' any existing non-deleted hash_node with
// the same hashcode as the provided key's hashcode. if it finds such
// a hash node, it decrements the table's size (but not occupancy) and
// returns true. it returns false otherwise.
bool remove(hash_table* tbl, std::string key) {
    
    // find the hashcode and bucket for the given key
    unsigned int hashcode = djb2(key);
    unsigned int bucket = modulo_bucket_func(hashcode, tbl->capacity);

    // if the keys match, marck the node as deleted, decrement the table's size, and return true
    while (tbl->table[bucket] != nullptr) {
        if (tbl->table[bucket]->hashcode == hashcode && tbl->table[bucket]->deleted == false) {
            tbl->table[bucket]->deleted = true;
            tbl->size--;
            return true;
        }
        bucket++;
    }
    // not found, return false
    return false;
}

// resize creates a new underlying backing array (tbl->table) with the
// provided new capacity, rehashes the existing backing array into the
// new array. on exit, the hash table's fields and functions
// accurately reflect the hash table's current state.
void resize(hash_table* tbl, unsigned int new_capacity) {
    
    // define table with new capacity
    hash_table* newtable = init_table(new_capacity);

    // fill the new table with old table keys
    for (int i = 0; i < tbl->capacity; i++) {
        if (tbl->table[i] != nullptr) {
            set_kvp(newtable, tbl->table[i]->key, tbl->table[i]->value);
        }
    }

    // set the new table's occupied and size to the old table's
    newtable->occupied = tbl->occupied;
    newtable->size = tbl->size;
    *tbl = *newtable;
}

// print_table is a debugging function. 
void print_table(hash_table* tbl) {
    cout << "Hashtable:" << endl;
    cout << "  capacity: " << tbl->capacity << endl;
    cout << "  size:     " << tbl->size << endl;
    cout << "  occupied: " << tbl->occupied << endl;
    cout << "  load:     " << load(tbl) << endl;
    if (tbl->capacity < 130) {
        for (unsigned int i = 0; i < tbl->capacity; i++) {
            cout << "[" << i << "]    ";
            if (tbl->table[i] == NULL) {
                cout << "<empty>" << endl;
            } else if (tbl->table[i]->deleted) {
                cout << "<deleted>" << endl;
            } else {
                cout << "\"" << tbl->table[i]->key << "\" = \"" << tbl->table[i]->value << "\"" << endl;
            }
        }
    } else {
        cout << "    <hashtable too big to print out>" << endl;
    }
}


unsigned int djb2(string key) {
    unsigned int hash = 5381;
    //
    //  cout << "Hashing string \"" << key << "\"" << endl;
    //  cout << bitset<32>(hash) << " " << hash << endl;
    for (size_t i = 0; i < key.length(); i++) {
        char c = key[i];
        hash = ((hash << 5) + hash) + c;
        // cout << bitset<32>(hash) << " " << hash << endl;
    }
    // cout << "Hashed string \"" << key << "\" to " << hash << endl;
    //
    return hash;
}

// implemented for you - don't change this one
unsigned int modulo_bucket_func(unsigned int hashcode, unsigned int cap) {
    unsigned int b = hashcode % cap;
    return b;
}
