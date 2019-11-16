//                  _   _             
//                 | | (_)            
//   ___  ___  _ __| |_ _ _ __   __ _ 
//  / __|/ _ \| '__| __| | '_ \ / _` |
//  \__ \ (_) | |  | |_| | | | | (_| |
//  |___/\___/|_|   \__|_|_| |_|\__, |
//                               __/ |
//                              |___/
//
//  This defines the names of various sorting functions and related
//  helper functions. You are required to implement all of these.
//
//  When the user calls the sorting functions, it is expected that the
//  output data is sorted in _nondecreasing_ order.  E.g.
//
//  input:  9, 5, 4, 1, 10, 5
//  output: 1, 4, 5, 5, 9, 10 
//

#include <vector>

using namespace std;

// quicksort is the entry point for the quicksort routine. It should
// use the quicksort_partition function. It is also recursive, so you
// will call quicksort from inside the quicksort function.
// 
// data: The input is a vector of integers. You can use this in a very
// similar manner to arrays, but without a lot of the pointer
// brain-damage. Note that the ampersand in front of the parameter
// name indicates this is passed by _reference_, which means whatever
// you do to this vector inside the quicksort function will be visible
// outside as well.
//
// low_idx and high_idx: these are the current indices for the
// quicksort algorithm, and are normal pass-by-value parameters. Both
// of these indices are inclusive: they refer to an addressable
// element of the data vector.
void quicksort(vector<int> &data, int low_idx, int high_idx);


// quicksort_partition is the helper function for quicksort. Input
// parameters have same semantics as for quicksort.
//
// The pivot index is returned.
int quicksort_partition(vector<int> &data, int low_idx, int high_idx);


// bubblesort is probably the easiest sorting algorithm to conceive
// of. It is unfortunately not all that fast. Here's your chance to
// write really inefficient code! There are no related helper
// functions. 
void bubblesort(vector<int> &data);


// mergesort is another classic O(n log n) sorting algorithm. This
// uses the helper function 'merge'.
void mergesort(vector<int> &data);


// merge is the helper function for mergesort. It returns a vector
// containing the merged contents of the two input vectors.
vector<int> merge(vector<int> &data, vector<int> &left, vector<int> &right);

 // split is another helper function for mergesort!   
vector<int> split(vector<int> &data);

// mystery_sort is any other sorting function that you choose to
// implement. You may write any additional sorting function you wish,
// and call it 'mystery_sort'.
// 
// See http://en.wikipedia.org/wiki/Sorting_algorithm for a list.
//
// Only rules are: (1) it has to have the following signature, and the
// calling code will expect 'data' to be in non-decreasing order when
// it returns, and (2) you have to write something new---no relying on
// the other functions you've implemented.
//
// Also, write a comment somewhere near the top that explains which
// sorting algorithm you're implementing.
void mystery_sort(vector<int> &data);

