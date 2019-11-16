//
// binary_search_tree_test.cpp
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "binary_search_tree.h"
#include <string>

using namespace std;

bt_node* HandBuildNode ( int data );
bt_node* HandBuildTree ( );
void inOrderWalk( bt_node* top, int arr[]);
int treeSize (bt_node* top);
bool ArrayContains ( int arr[], int size, int value );

TEST_CASE("BST: initialization", "[init]") {
  bt_node* four = init_node(4);
  
  REQUIRE(four != NULL);
  REQUIRE(four->data == 4);
  REQUIRE(four->left == NULL);
  REQUIRE(four->right == NULL);
}

TEST_CASE("BST: insert", "[insert]") {
  bt_node* top = HandBuildNode(2);
  bt_node* one = HandBuildNode(1);
  bt_node* three = HandBuildNode(3);
  bt_node* four = HandBuildNode(4);
  
  insert(&top, one);
  insert(&top, three);
  insert(&top, four);

  REQUIRE(top->left == one);
  REQUIRE(top->right == three);
  REQUIRE(top->right->right == four);
}

TEST_CASE("BST: insert data", "[insert data]") {
  bt_node* top = HandBuildNode(2);
  
  insert_data(&top, 1);
  insert_data(&top, 3);
  insert_data(&top, 4);

  REQUIRE(top != NULL);
  REQUIRE(top->left != NULL);
  REQUIRE(top->right != NULL);
  REQUIRE(top->data == 2);
  REQUIRE(top->right->right != NULL);
  REQUIRE(top->left->data == 1);
  REQUIRE(top->right->data == 3);
  REQUIRE(top->right->right->data == 4);
}

TEST_CASE("bst: size", "[size]") {
  bt_node* top = HandBuildTree(); // Hand build a tree of size 6
  REQUIRE(size(top) == 6);
}

TEST_CASE("bst: contains", "[contains]") {
  bt_node* top = HandBuildTree( ); // Hand build a node with 0, 1, 2, 3, 4, 5 in it.
  
  bool containsReal = contains(top, 0) &&
    contains(top, 1) &&
    contains(top, 2) && 
    contains(top, 3) && 
    contains(top, 4) &&
    contains(top, 5);
  
  bool containsFake = !contains(top, -2) &&
    !contains(top, -1) && 
    !contains(top, 99) && 
    !contains(top, 42); 
  
  REQUIRE(contains(top, 0));
  REQUIRE(contains(top, 1));
  REQUIRE(contains(top, 2));
  REQUIRE(contains(top, 3));
  REQUIRE(contains(top, 4));
  REQUIRE(contains(top, 5));

  REQUIRE_FALSE(contains(top, -2));
  REQUIRE_FALSE(contains(top, -1));
  REQUIRE_FALSE(contains(top, -99));
  REQUIRE_FALSE(contains(top, 42));
}

TEST_CASE("bst: get node", "[get node]") {
  {
    // tests getting a node from an empty tree.
    bt_node* empty = NULL;
    bt_node* n = get_node(empty, 50);
    REQUIRE(n == NULL);
  }

  {
    // tests getting nodes that we know are NOT there.
    bt_node* top = HandBuildTree();
    REQUIRE(NULL == get_node(top, 42));
    REQUIRE(NULL == get_node(top, -1));
  }
  
  {
    // tests getting nodes that we know are there.
    bt_node* top = HandBuildTree();
    REQUIRE(get_node(top, 0) == top->left);
    REQUIRE(get_node(top, 1) == top);
    REQUIRE(get_node(top, 2) == top->right->left->left);
    REQUIRE(get_node(top, 3) == top->right->left);
    REQUIRE(get_node(top, 4) == top->right);
    REQUIRE(get_node(top, 5) == top->right->right);
  }
}

TEST_CASE("bst: remove", "[remove]") {
  // Create separate scopes for this test.
  {
    // Hand build a node with 0, 1, 2, 3, 4, 5 in it.
    bt_node* top = HandBuildTree();
    
    // remove the leaf node 5
    remove( &top, 5 );

    int size = treeSize(top);
    int contents[size];
    int expected[5] = {0, 1, 2, 3, 4};

    inOrderWalk(top, contents);
   
    bool result = true;

    for (int i = 0; i < 5; i++) {
      if (contents[i] != expected[i]) {
        result = false;
        break;
      }
    }
    result = result && size == 5;
    
    REQUIRE(result); // tests removing a leaf
  }
  {
    // Hand build a node with 0, 1, 2, 3, 4, 5 in it.
    bt_node* top = HandBuildTree();
    
    // remove the branch node 3
    remove( &top, 3 );

    int size = treeSize(top);
    int contents[size];
    int expected[5] = {0, 1, 2, 4, 5};

    inOrderWalk(top, contents);
   
    bool result = true;

    for (int i = 0; i < 5; i++) {
      if (contents[i] != expected[i]) {
        result = false;
        break;
      }
    }
    result = result && size == 5;
    
    REQUIRE(result); // Tests removing a branch with one child.
  }
}

TEST_CASE("bst: remove with 2 children", "[remove fork]") {
  // Hand build a node with 0, 1, 2, 3, 4 in it.
  bt_node* top = HandBuildTree();
  
  // remove the trunk node 1
  // Note that there are two possible results for this depending on
  // what bias the tree is.
  remove( &top, 1 );
  
  int size = treeSize(top);
  REQUIRE(size == 5);
  int contents[size];
  int expected[5] = {0, 2, 3, 4, 5};
  
  inOrderWalk(top, contents);
  
  bool result = true;
  
  for (int i = 0; i < 5; i++) {
    cout << "expecting " << expected[i] << ", actual " << contents[i] << endl;
    REQUIRE(contents[i] == expected[i]);
  }
}

TEST_CASE("bst: to array", "[to array]") {
  bt_node* top = HandBuildTree();
  
  int results[6] = {-1, -1, -1, -1, -1, -1};
  to_array(top, results);
  
  REQUIRE(results[0] != -1);
  REQUIRE(results[1] != -1);
  REQUIRE(results[2] != -1);
  REQUIRE(results[3] != -1);
  REQUIRE(results[4] != -1);
  REQUIRE(results[5] != -1);
  
  REQUIRE(ArrayContains(results, 6, 0));
  REQUIRE(ArrayContains(results, 6, 1));
  REQUIRE(ArrayContains(results, 6, 2));
  REQUIRE(ArrayContains(results, 6, 3));
  REQUIRE(ArrayContains(results, 6, 4));
  REQUIRE(ArrayContains(results, 6, 5));
  
  REQUIRE(results[0] == 0);
  REQUIRE(results[1] == 1);
  REQUIRE(results[2] == 2);
  REQUIRE(results[3] == 3);
  REQUIRE(results[4] == 4);
  REQUIRE(results[5] == 5); 
}

bt_node* HandBuildNode ( int data )
{
  bt_node* top = new bt_node();
  top->data = data;
  top->left = NULL;
  top->right = NULL;
  
  return top;
}

bt_node* HandBuildTree ( )
{
  // Hand build an unbalanced tree with 0, 1, 2, 3, 4, 5 in it. Looks
  // like this:
  //
  //    1
  //   / \
  //  0   4
  //     /  \
  //    3    5
  //   /
  //  2
  //
  bt_node* top = HandBuildNode(1);
  top->left = HandBuildNode(0);
  top->right = HandBuildNode(4);
  top->right->left = HandBuildNode(3);
  top->right->left->left = HandBuildNode(2);
  top->right->right = HandBuildNode(5);
  
  return top;
}

static void _inOrderWalk( bt_node* top, int arr[], int * index ) {
  if (!top) return;
  // first make an array out of the left side
  if (top->left) _inOrderWalk(top->left, arr, index);

  // add our current node
  arr[*index] = top->data;
  (*index)++;

  // and make one from the right
  if (top->right) _inOrderWalk(top->right, arr, index);
}

void inOrderWalk( bt_node* top, int arr[]) {
  // check for empty tree
  if (!top) return;

  int index = 0;

  // call our helper, with the added index field
  // to keep track of our position in the array
  _inOrderWalk(top, arr, &index);
}

int treeSize( bt_node* top) {
  if (!top) return 0; 

  int left = 0; 
  int right = 0; 

  if (top->left)  left =  treeSize(top->left); 
  if (top->right) right = treeSize(top->right); 

  return left + right + 1; 
}

bool ArrayContains ( int arr[], int size, int value )
{
  for ( int i = 0; i < size; i++ )
    {
      if ( arr[i] == value )
	return true;
    }
  
  return false;
}
