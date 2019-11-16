# Linked List

For this assignment I implemented the following functions for a linked list data
structure (in linked_list.cpp):

* **init_node** - creates a new node and returns a pointer to it.
* **report** - returns a string representation of the list.
* **append** and **append_data** - adds to the end of the list.
* **insert** and **insert_data** - inserts into any spot in the list.
* **size** - returns the current size of the list.
* **contains** - returns true if the list contains a given value.

To run the tests:

Run `make`, then one of the following:

* `python grade.py linked_list_test` - this runs the python grading
  script, using `points.json` and produces a tab separated report on the number of points 
  earned for each function based on the number of tests passed (ie, 5/5)
* `./linked_list_test` - this runs all the unit tests in a row.
* `./linked_list_test "[sometest]"` - runs a particular unit
  test:

    1. `init`
    2. `report`
    3. `append data`
    4. `append node`
    5. `insert data`
    6. `insert node`
    7. `remove`
    8. `size`
    9. `contains`