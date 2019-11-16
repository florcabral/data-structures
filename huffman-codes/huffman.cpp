// huffman.cpp
//

#include "huffman.h"
#include <sstream>
#include <iostream>

using namespace std;


freq_info* create_leaf(char symbol, int count) {
    
    //leaf is initialized with the given symbol and count, and should have NULL children
    freq_info* node = new freq_info();
    node->symbol = symbol;
    node->count = count;
    node->left = NULL;
    node->right = NULL;
    node->is_leaf = true;
    
  return node;
}


freq_info* combine_nodes(freq_info* left, freq_info* right) {
    
    //internal node is initialized with the given left and right children, count is their combined counts, and symbol is undefined
    freq_info* node = new freq_info();
    node->count = left->count + right->count;
    node->left = left;
    node->right = right;
    node->is_leaf = false;
    
  return node;

}


void increment_lookup(map<char, int>& lookup, char symbol) {
    
    // find out if the symbol is already in the map
  bool present = lookup.find(symbol) != lookup.end();
  
    // if it is, increment the count by 1
    if (present == true) {
        lookup[symbol] = lookup[symbol] + 1;
    }   
    
    // if it isn't, assign a count of 1 to that symbol
    else {
      lookup[symbol] = 1;
    }
    
}

void load_queue(const map<char, int>& lookup, tree_queue& q) {

    //turns each key/value pair in the lookup table into a freq_info pointer, by creating leaves and adding them to the queue
    for (auto it = lookup.cbegin(); it != lookup.cend(); ++it) {
        char k = (*it).first;
        int v =  (*it).second;
        freq_info* node = create_leaf(k, v);
        q.push(node);
    }
}


freq_info* build_tree(tree_queue& q) {
    
    //get and store the first and second items in the q
    //pop the first, you get the second at the top, pop it too
    for (int i=q.size(); i > 1; i--) {
        freq_info* left = q.top();     
        q.pop();
        freq_info* right = q.top();
        q.pop();
        freq_info* internal = combine_nodes(left, right);     //create internal node with the first on the left and second on the right
        q.push(internal);     //need to add the internal node back into the queue
    }
    
  return q.top();
}

void encoding_table_helper(freq_info* node, map<char, string>& huffmap, string huffstring) {
    
    //base case, reached the symbol
    if (node->is_leaf) {
        huffmap[node->symbol] = huffstring;
        return;
    }

    //build the string mappings as you move down the tree, adding the appropriate char
    string left_huffstring = huffstring + LEFT_CHAR;
    string right_huffstring = huffstring + RIGHT_CHAR;

    encoding_table_helper(node->left, huffmap, left_huffstring);
    encoding_table_helper(node->right, huffmap, right_huffstring);
}


map<char, string> build_encoding_table(freq_info* root) {

    //create a new map and call helper function to fill it with each character's sequence
    map<char, string> huffmap;
    encoding_table_helper(root, huffmap, huffmap[root->symbol]);
    
  return huffmap;
}

string encode(map<char, string> enc_table, string input) {
    
    //traverse string, encode the characters according to the encoding table
    string huffstring;
    
    for (int i = 0; i < input.size(); i++) {
        huffstring = huffstring + enc_table[input[i]];
    }
    
  return huffstring;
}

string decode(freq_info* root, string input) {
  
    string decoded;
    freq_info* cursor = root;
    
    // traverse string and check characters, move left or right depending on what you encounter
    for (int i=0;i < input.size(); i++) { 
          
        if (input[i] == LEFT_CHAR[0]) {
           cursor = cursor->left; 
        }
        else {
           cursor = cursor->right; 
        }
  
        // reached leaf node, retrieve the character stored there, add it to the decoded string
        if (cursor->is_leaf == true) 
        { 
            decoded += cursor->symbol; 
            cursor = root; 
        } 
      }

  return decoded;
}
