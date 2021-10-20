//----------------------------------------------------------------------------
// BINTREE.H
// Class for a Binary Tree (holds NodeData objects)
// Coded by: Austin Barracliffe
//----------------------------------------------------------------------------
// Binary Tree: stores NodeData objects (with Strings for this implementation)
// and allows other features:
//      --allows the retrieval of sibling nodes
//      --allows the retrieval of parent nodes
//      --allows the outputting of a Binary Tree to an Array
//      --allows the building of a Binary Tree from a sorted Array
//
// Implementation and assumptions:
//      --user will pass pointers to NodeData objects to add nodes to the tree
//      --array passed to arrayToBSTree() is already sorted beforehand
//      --for <<, tree outputs data in each node followed by a space
//----------------------------------------------------------------------------

#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"
using namespace std;

class BinTree {
//----------------------------------------------------------------------------
// operator<<
// Preconditions: None 
// Postconditions: Nothing outputted if tree is empty, otherwise each NodeData
//                 object from each node of the tree is put into the ostream
//                 in an in-order manner
friend ostream &operator<<(ostream&, const BinTree&);

public:
//----------------------------------------------------------------------------
// Default constructor
// Preconditions: None
// Postconditions: The tree's root pointer is set to null
BinTree(); // constructor

//----------------------------------------------------------------------------
// Copy constructor
// Preconditions: Tree passed as argument exists and can be empty or hold values
// Postconditions: New tree created that is a deep copy of the argument tree
BinTree(const BinTree &); // copy constructor

//----------------------------------------------------------------------------
// Destructor
// Preconditions: None
// Postconditions: Nodes in the tree are deleted recursively by makeEmpty()
//                 along with their data pointers which are set to null
~BinTree(); // destructor, calls makeEmpty()
   
//----------------------------------------------------------------------------
// isEmpty
// Preconditions: None
// Postconditions: Returns true f the tree is empty, otherwise false
bool isEmpty() const;

//----------------------------------------------------------------------------
// makeEmpty
// Preconditions: Tree has nodes
// Postconditions: All nodes in the tree are deleted and pointers are set to
//                 null, root is now null and thus returns true on isEmpty
void makeEmpty(); // make the tree empty so isEmpty returns true

//----------------------------------------------------------------------------
// operator=
// Preconditions: None
// Postconditions: A deep copy of the argument tree is made and assigned to this
//                 tree, except in the case of self-assignment where nothing is
//                 changed and the same tree is returned
BinTree& operator=(const BinTree &);

//----------------------------------------------------------------------------
// operator==
// Preconditions: User must want to check if 2 trees have the same structure and
//                data in the nodes of the trees
// Postconditions: Returns true if trees have the same structure/data, also if
//                 both trees are empty, otherwise returns false
bool operator==(const BinTree &) const;

//----------------------------------------------------------------------------
// operator!=
// Preconditions: User must want to check if 2 trees do not have the same
//                structure and data in the nodes of the trees
// Postconditions: Returns true if trees have diferent structure/data, also if
//                 only one tree is empty, otherwise returns false
bool operator!=(const BinTree &) const;

//----------------------------------------------------------------------------
// insert
// Preconditions: NodeData to add is not a duplicate entry and is of same type
//                and comparable to those in the tree
// Postconditions: Node is created and added to the tree with NodeData equal to
//                 the argument, true is returned unless argument is duplicate
//                 which isn't added and false is returned
bool insert(NodeData*);

//----------------------------------------------------------------------------
// retrieve
// Preconditions: second NodeData argument is unallocated and is expected to be
//                used to store the retrieved NodeData
// Postconditions: returns true if 1st argument is found in the tree and 2nd
//                 argument is set to point to this NodeData object, otherwise
//                 returns false and nothing is done with 2nd argument so it
//                 still points to garbage
bool retrieve(const NodeData&, NodeData*&) const;

//----------------------------------------------------------------------------
// getSibling
// Preconditions: first NodeData argument exists in the tree and has a sibling
//                node in the tree
// Postconditions: true returned if the first NodeData argument exists in the
//                 tree AND the node has a valid sibling node, otherwise
//                 false is returned (if tree is empty or has only 1 node, node
//                 is an only child)
bool getSibling(const NodeData &, NodeData&) const;

//----------------------------------------------------------------------------
// getParent
// Preconditions: first NodeData argument exists in the tree and has a parent
//                node in the tree
// Postconditions: true returned if the first NodeData argument exists in the
//                 tree AND the node has a parent node, otherwise false is
//                 returned (tree is empty, tree has only 1 node)
bool getParent(const NodeData &, NodeData&) const;

//----------------------------------------------------------------------------
// displaySideways
// Preconditions: None
// Postconditions: Displays a binary tree as though you are viewing it from the
//                 side, outputs nothing if tree is empty
void displaySideways() const; // displays the tree sideways

//----------------------------------------------------------------------------
// bstreeToArray
// Preconditions: Array passed as argument is a statically allocated array of
//                100 nullptr elements
// Postconditions: Nodes from the tree are placed into the array sequentially
//                 and tree is then emptied.
void bstreeToArray(NodeData* []);

//----------------------------------------------------------------------------
// arrayToBSTree
// Preconditions: Array passed as argument is already sorted beforehand, and is
//                a statically allocated array of 100 elements originally
//                initalized to nullptr and then filled from index 0 
// Postconditions: A balanced tree is built from the array and every index of
//                 the array is set to nullptr
void arrayToBSTree(NodeData* []);

private:
    struct Node {
        NodeData* data; // pointer to data object
        Node* left; // left subtree pointer
        Node* right; // right subtree pointer
    };
    Node* root; // root of the tree
    // utility functions
    void inorderHelper(Node*, ostream&) const; // recursive helper for 
                                               // operator<<

    void sidewaysHelper(Node*, int) const;     // recursive helper for
                                               // displaySideways

    void copyHelper(Node*&, const Node*);      // recursive helper for
                                               // copy constructor

    void makeEmptyHelper(Node*&);              // recursive helper for makeEmpty

    bool equalityHelper(const Node*,           // recursive helper for
        const Node*) const;                    // operator== and operator!=
                                               

    bool getSiblingHelper(Node*,               // recursive helper for
        const NodeData&, NodeData&) const;     // getSibling

    bool getParentHelper(Node* curPtr,         // recursive helper for
        const NodeData&, NodeData&) const;     // getParent

    void bstreeToArrayHelper(Node*,            // recursive helper for
        NodeData* [], int&) const;             // bstreeToArray

    void arrayToBSTreeHelper(int, int,         // recursive helper for
         NodeData* []);                        // arrayToBSTree
}; 

#endif