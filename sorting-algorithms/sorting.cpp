/*
  sorting.cpp

  Please refer to sorting.h for documentation on each function.
 */

#include "sorting.h"
#include <iostream>
#include <algorithm> 

using namespace std;


// helper function for quicksort
int quicksort_partition(vector<int> &data, int low_idx, int high_idx) {
    
  int pivot = data[low_idx];
  int left = low_idx+1;
  int right = high_idx;
  int temp;
  
    // move through list and "split" using pivot as reference
  while (left != right) {
    if (data[left]  <= pivot) {
        left++;
    }
      
      // if value on right is lower than pivot, put it on left side
    else {
      while (( left != right)  && (pivot < data[right])) {
          right--;
      }
        
      temp =  data[right];
      data[right] = data[left];
      data[left] = temp;
    }
  }
    
  // if value on left is higher than pivot, put it on right side
  if (data[left] > pivot) {
      left--;
  }
  data[low_idx] = data[left];
  data[left] = pivot;

  return (left);
}

void quicksort(vector<int> &data, int low_idx, int high_idx) {
  
    // call partition function, use index of middle to call recursively and keep splitting
    if (low_idx < high_idx) {
        int q = quicksort_partition(data, low_idx, high_idx);
        quicksort(data, low_idx, q - 1);
        quicksort(data, q + 1, high_idx);
  }
}

void bubblesort(vector<int> &data) {

    // initialize iterators, vector size and completion check
   int n = data.size();
   int i, j; 
   bool swapped; 
        
    // run through list, compare every element to the next, swap them if previous > next
   for (i = 0; i < n-1; i++) 
   { 
     swapped = false; 
     for (j = 0; j < n-i-1; j++) 
     { 
        if (data[j] > data[j+1]) 
        { 
           int temp;
            temp = data[j];
            data[j] = data[j+1]; 
            data[j+1] = temp;
           swapped = true; 
        } 
     } 

     if (swapped == false) 
        break; 
}
}

// merge helper function for mergesort
vector<int> merge(vector<int> &data, vector<int> &left, vector<int> &right){
  
  vector<int> temp;

  int l = 0;
  int r = 0;

    // compare left and right values, add them in order
  while (l < left.size() && r < right.size()) {
      
    if (left[l] < right[r]){
      temp.push_back(left[l]);
      l++;
        
    } else {
      temp.push_back(right[r]);
      r++;
    }
  } 

  while (l < left.size()) {
    // add remaining sorted left values
    temp.push_back(left[l]);
    l++;
  }

  while (r < right.size()) {
    // do the same for the right
    temp.push_back(right[r]);
    r++;
  }

  data = temp;
  return data;
}
    
// split helper function for mergesort
vector<int> split(vector<int> &data) {
    
  // base case reached, return
  if(data.size() == 1)
    return data;

  // find middle point and halve vector
  vector<int>::iterator mid = data.begin() + (data.size() / 2);
  vector<int> left(data.begin(), mid);
  vector<int> right(mid, data.end());
  
  // keep at it
  left = split(left);
  right = split(right);
  
  // now merge
  return merge(data, left, right);
}


void mergesort(vector<int> &data) {
    
    // call the data split to start the sorting game
    split(data);
}

        
// Algorithm implemented: Insertion Sort!
void mystery_sort(vector<int> &data) {

    for(int i = 1; i < data.size(); i++) {
        int check = data[i];
        int j = i-1;
 
    while(j >= 0 && data[j] > check)
      {
        data[j+1] = data[j];
        j--;
      }
        
    data[j+1] = check;
     }
}
    

  

