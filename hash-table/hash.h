/*

 _               _     _        _     _      
| |             | |   | |      | |   | |     
| |__   __ _ ___| |__ | |_ __ _| |__ | | ___ 
| '_ \ / _` / __| '_ \| __/ _` | '_ \| |/ _ \
| | | | (_| \__ \ | | | || (_| | |_) | |  __/
|_| |_|\__,_|___/_| |_|\__\__,_|_.__/|_|\___|
                                             
                                             
 */
#include <string>

// Advice for approaching this assignment:
//
// Many of the unit tests depend on more than one function. For
// example, the [hash func] test requires init_table to work. Because
// of this I recommend you proceed in this order:
//
// 1. init node
// 2. init table
// 3. hash func
// 4. bucket func
// 5. set
//
// Once you're there, you can take on the rest: load, get, contains,
// remove, and (if you're feeling saucy) resize.
//
// resize is extra credit.

// hash_node represents the contents of an individual bucket in your
// hash table.
struct hash_node {
  // deleted indicates if the node was marked as removed from the hash
  // table. it should be initialized to false.
  bool deleted;

  // key is the key the user provides to associate with a value.
  std::string key;

  // hashcode is the hashcode computed by the hash table's hash_func
  // on the key. it is stored to avoid having to re-compute it.
  unsigned int hashcode;

  // value is the user value associated with the key.
  std::string value;
};

// hash_table is the structure that holds your hashed data and
// associated metadata and hash function references.
struct hash_table {
  // capacity current number of addressable buckets in table. kept up-to-date.
  unsigned int capacity;

  // number of actual (not deleted) entries. kept up-to-date.
  unsigned int size;

  // number of non-null buckets. (so all hash_nodes, deleted or
  // otherwise). kept up-to-date.
  unsigned int occupied;

  // table points to dynamic array of hash_node pointers. it should be
  // initialized to a dynamic array of pointers to hash_node
  // structs. those pointers shoudl all initially be NULL.
  hash_node** table;

  // hash_func is the currently in-use hash function. it should be
  // initialized to the djb2 hash function.
  //
  // to assign this, simply do:
  //
  // mytable->hash_func = djb2; // any function with signature like djb2 works.
  //
  // to use this:
  //
  // unsigned int hashcode_of_foo = mytable->hash_func("foo");
  unsigned int (*hash_func)(std::string);

  // bucket_func is the currently in-use bucket indexing function. it
  // should be initialized to the modulo_bucket_func function. assign
  // and use similarly to hash_func.
  unsigned int (*bucket_func)(unsigned int hashcode, unsigned int capacity); 
};

// init_table creates and initializes a hash_table structure and
// returns a pointer to it. see the hash_table documentation for
// details on the fields and their expected default values.
hash_table* init_table(unsigned int cap);

// init_node creates and initializes a hash_node that will occupy a
// hash table bucket. see the hash_node documentation for more info.
hash_node* init_node(std::string key, unsigned int hashcode, std::string val);

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
bool set_kvp(hash_table* tbl, std::string key, std::string value);

// load returns a load factor describing how 'full' the table
// is. because we are using linear probing, which leaves 'deleted'
// hash nodes sitting around, it is reasonable to use occupied divided
// by capacity. you can alternately use size divided by capacity,
// which is a more canonical definition of hashtable load. either will
// work with the unit tests.
float load(hash_table* tbl);

// get_val returns the value associated with the provded key in the
// table, or the empty string "" if no such mapping exists (or if
// there is a mapping but it is deleted).
std::string get_val(hash_table* tbl, std::string key);

// contains returns true if the table has a non-deleted node whose
// hashcode matches the given key's hashcode.
bool contains(hash_table* tbl, std::string key);

// remove marks as 'deleted' any existing non-deleted hash_node with
// the same hashcode as the provided key's hashcode. if it finds such
// a hash node, it decrements the table's size (but not occupancy) and
// returns true. it returns false otherwise.
bool remove(hash_table* tbl, std::string key);

// resize creates a new underlying backing array (tbl->table) with the
// provided new capacity, rehashes the existing backing array into the
// new array. on exit, the hash table's fields and functions
// accurately reflect the hash table's current state.
//
// this is an extra-credit function.
void resize(hash_table* tbl, unsigned int new_capacity);

// print_table is a debugging function. 
void print_table(hash_table* tbl);

// djb2 is a hash function that hashes strings and gives an unsigned
// integer hash code that could take on any value in the 32-bit
// unsigned integer range.
unsigned int djb2(std::string key);

// modulo_bucket_func simply returns hashcode % cap. It is provided
// here as a separate function because you *could* write your own hash
// function for putting keys into buckets. It is implemented for you.
unsigned int modulo_bucket_func(unsigned int hashcode, unsigned int cap);
