# Sorting

For this assignment I fully implemented the following sorting algorithms (in sorting.cpp):

* **bubble sort** 
* **insertion sort** 
* **quicksort** 
* **mergesort** 

## To run the tests:

Run `make`, then one of the following:

* `python grade.py sorting_test` - this runs the python grading
  script, using `points.json` and produces a tab separated report on the number of points earned for each sorting algorithm based on the number of tests passed (ie, 5/5)
* `./sorting_test` - this runs all the unit tests in a row.
* `./sorting_test "[sometest]"` - runs a particular unit
  test:

    1. `bubble`
    2. `quick`
    3. `merge`
    4. `mystery`