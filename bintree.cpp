#include "bintree.h"

//----------------------------------------------------------------------------
// Constructors and Destructor

// Default constructor
BinTree::BinTree() {
    root = nullptr;
}

// Copy constructor
BinTree::BinTree(const BinTree & otherTree) {

}

// Destructor
BinTree::~BinTree() {
    makeEmpty();
}

//----------------------------------------------------------------------------
// isEmpty
// true if tree is empty, otherwise false
bool BinTree::isEmpty() {
    // Check if root does not exist, tree is empty if false
    if(root == nullptr) {
        return true;
    }
    // Root exists so tree isn't empty
    return false;
}

//----------------------------------------------------------------------------
// makeEmpty
// make the tree empty so isEmpty returns true
void BinTree::makeEmpty() {
    
} 