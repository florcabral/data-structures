# Huffman Codes

For this assignment I implemented the following functions for a Huffman Codes data
structure (in huffman.cpp):

* **create_leaf** - initializes a leaf node in the Huffman codec tree from heap memory and returns a pointer to it
* **combine_nodes** - initializes an internal node in the Huffman codec tree from heap memory and returns a pointer to it
* **increment_lookup** - adds one to the value associated with the given symbol
* **load_queue** - turns each key/value pair in the lookup table into a node pointer, and pushes it into the provided priority queue
* **build_tree** - creates a Huffman codec tree using the values contained in the provided priority queue
* **build_encoding_table** - creates a lookup table for the encoding process
* **encode** - returns an encoded string using the provided encoding lookup table on the input string
* **decode** - returns a decoded string using the provided Huffman codec tree and input string


## To run the tests:

Run `make`, then one of the following:

* `python grade.py huffman_test` - this runs the python grading
  script, using `points.json` and produces a tab separated report on the number of points 
  earned for each function based on the number of tests passed (ie, 5/5)
* `./huffman_test` - this runs all the unit tests in a row.
* `./huffman_test "[sometest]"` - runs a particular unit
  test:

    1. `create leaf`
    2. `create internal`
    3. `count symbols`
    4. `load queue`
    5. `build tree`
    6. `encode table`
    7. `encode`
    8. `decode`