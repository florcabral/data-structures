# Priority Queue

For this assignment I implemented a priority queue as a double linked list (in pq.cpp), 
including the following functions:

- **init_priority_queue** - initializes a new priority queue
- **insert** - inserts element with a given numeric priority
- **remove** - removes the highest priority element
- **peek** - peeks at the highest priority element

## To run the tests:

Run `make`, then one of the following:

* `python grade.py pq_test` - this runs the python grading
  script, using `points.json` and produces a tab separated report on the number of points earned 
  for each function based on the number of tests passed (ie, 5/5)
* `./pq_test` - this runs all the unit tests in a row.
* `./pq_list_test "[sometest]"` - runs a particular unit
  test:

    1. `init_priority_queue`
    2. `peek`
    3. `insert`
    4. `remove`