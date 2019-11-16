# Hash table

For this assignment I implemented the following functions for a hash table data structure (in hash.cpp):

* **init_table** - creates and initializes a hash_table structure
* **init_node** - creates and initializes a hash_node that will occupy a hash table bucket
* **set_kvp** - establishes a mapping between the given key and value pair in the provided hash table
* **load** - returns a load factor describing how 'full' the table is
* **get_val** - returns value stored given a key
* **contains** - contains returns true if the table has a non-deleted node whose hashcode matches the given key's hashcode
* **remove** - marks as 'deleted' any existing non-deleted hash_node with the same hashcode as the provided key's hashcode
* **resize** - creates a new underlying backing array with the provided new capacity, rehashes the existing backing array into the new array

## To run the tests:

Run `make`, then one of the following:

* `python grade.py hash_test` - this runs the python grading
  script, using `points.json` and produces a tab separated report on the number of points 
  earned for each function based on the number of tests passed (ie, 5/5)
* `./hash_test` - this runs all the unit tests in a row.
* `./hash_test "[sometest]"` - runs a particular unit
  test:

   1. `init node`
   2. `init table`
   3. `hash func`
   4. `bucket func`
   5. `set`
   6. `load`
   7. `get`
   8. `contains`
   9. `remove`
   10. `resize`