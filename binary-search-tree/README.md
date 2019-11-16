# Binary Search Tree

For this assignment I implemented the following functions for a binary search tree data
structure (in binary_search_tree.cpp):

* **init_node** - creates a new bt_node and returns a pointer to it
* **insert** and **insert_data** - insert given data into the correct spot in the tree
* **remove** - removes a node with 0, 1, or 2 nodes from the tree
* **contains** - returns true if the tree contains a given value
* **get_node** - returns pointer to a node that has the given value
* **size** - returns the current number of nodes reachable from the top
* **to_array** - fills an array with the tree's data in sorted order

## To run the tests:

Run `make`, then one of the following:

* `python grade.py binary_search_tree_test` - this runs the python grading
  script, using `points.json` and produces a tab separated report on the number of points 
  earned for each function based on the number of tests passed (ie, 5/5)
* `./binary_search_tree_test` - this runs all the unit tests in a row.
* `./binary_search_tree_test "[sometest]"` - runs a particular unit
  test:

   1. `init`
   2. `insert`
   3. `insert data`
   4. `size`
   5. `contains`
   6. `get node`
   7. `remove`
   8. `remove fork`
   9. `to array`