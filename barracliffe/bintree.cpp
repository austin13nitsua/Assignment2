//----------------------------------------------------------------------------
// BINTREE.CPP
// Member function definitions for class BinaryTree
// Coded by: Austin Barracliffe
//----------------------------------------------------------------------------
// Binary Tree: stores NodeData objects (with Strings for this implementation)
// and allows other features:
//      --allows the retrieval of sibling nodes
//      --allows the retrieval of parent nodes
//      --allows the outputting of a Binary Tree to an Array
//      --allows the building of a Binary Tree from a sorted Array
//
// Assumptions:
//      --user will pass pointers to NodeData objects to add nodes to the tree
//      --array passed to arrayToBSTree() is already sorted beforehand
//      --for <<, tree outputs data in each node followed by a space
//----------------------------------------------------------------------------

#include "bintree.h"

//----------------------------------------------------------------------------
// operator<<
// Preconditions: None 
// Postconditions: Nothing outputted if tree is empty, otherwise each NodeData
//                 object from each node of the tree is put into the ostream
//                 in an in-order manner
ostream& operator<<(ostream& os, const BinTree& binTree) {
    // Call helper function on root to iterate through the tree inorder
    binTree.inorderHelper(binTree.root, os);
    os << endl;
    return os;
}

void BinTree::inorderHelper(Node* curPtr, ostream& os) const {
    // Base case, node doesn't exist
    if(curPtr == nullptr) {
        return;
    }
    // Recursive call on left subtree
    inorderHelper(curPtr->left, os);
    // Process root
    os << *curPtr->data << " ";
    // Recursive call on right subtree
    inorderHelper(curPtr->right, os);
}

//----------------------------------------------------------------------------
// Default constructor
// Preconditions: None
// Postconditions: The tree's root pointer is set to null
BinTree::BinTree() {
    // Make an empty tree
    root = nullptr;
}

//----------------------------------------------------------------------------
// Copy constructor
// Preconditions: Tree passed as argument exists and can be empty or hold values
// Postconditions: New tree created that is a deep copy of the argument tree
BinTree::BinTree(const BinTree & otherTree) {
    // Call helper function passing the roots of both trees
    copyHelper(this->root, otherTree.root);
}

void BinTree::copyHelper(Node*& newTreeNode, const Node* oldTreeNode) {
    // Base case, node doesn't exist so terminate
    if(oldTreeNode == nullptr) {
        newTreeNode = nullptr;
        return;
    }
    // Node exists so make a deep copy
    newTreeNode = new Node;
    newTreeNode->data = new NodeData(*(oldTreeNode->data));
    // Recursive call on left subtree
    copyHelper(newTreeNode->left, oldTreeNode->left);
    // Recursive call on right subtree
    copyHelper(newTreeNode->right, oldTreeNode->right);
}

//----------------------------------------------------------------------------
// Destructor
// Preconditions: None
// Postconditions: Nodes in the tree are deleted recursively by makeEmpty()
//                 along with their data pointers which are set to null
BinTree::~BinTree() {
    // Calls make empty to delete all the nodes in the tree
    makeEmpty();
}

// isEmpty
// Preconditions: None
// Postconditions: Returns true f the tree is empty, otherwise false
bool BinTree::isEmpty() const {
    // Return whether root node exists
    return root == nullptr;
}

//----------------------------------------------------------------------------
// makeEmpty
// Preconditions: Tree has nodes
// Postconditions: All nodes in the tree are deleted and pointers are set to
//                 null, root is now null and thus returns true on isEmpty
void BinTree::makeEmpty() {
    // Call helper function on root
    makeEmptyHelper(root);
} 

void BinTree::makeEmptyHelper(Node*& treeNode) {
    // Base case, node doesn't exist so terminate
    if(treeNode == nullptr) {
        return;
    }
    // Recursive call on left subtree
    makeEmptyHelper(treeNode->left);
    // Recursive call on right subtree
    makeEmptyHelper(treeNode->right);
    // Subtrees have been cleared so delete the data of current node
    delete treeNode->data;
    treeNode->data = nullptr;
    // Finally delete current node
    delete treeNode;
    treeNode = nullptr;
}

//----------------------------------------------------------------------------
// operator=
// Preconditions: None
// Postconditions: A deep copy of the argument tree is made and assigned to this
//                 tree, except in the case of self-assignment where nothing is
//                 changed and the same tree is returned
BinTree& BinTree::operator=(const BinTree& otherTree) {
    // If self-assignment is called then do nothing and return this
    if(&otherTree == this) {
        return *this;
    }
     // Crucial to prevent memory leaks!
    makeEmpty();
    // Call helper function on the roots
    copyHelper(this->root, otherTree.root); 
    return *this;
}

//----------------------------------------------------------------------------
// operator==
// Preconditions: User must want to check if 2 trees have the same structure and
//                data in the nodes of the trees
// Postconditions: Returns true if trees have the same structure/data, also if
//                 both trees are empty, otherwise returns false
bool BinTree::operator==(const BinTree & otherTree) const {
    // Return result of helper function call
    return(equalityHelper(this->root, otherTree.root));
}

bool BinTree::equalityHelper(const Node* treeNode, const Node* otherTreeNode)
const {
    // Base case 1: current node pointers are both null
    if(treeNode == nullptr && otherTreeNode == nullptr) {
        return true;
    }
    // Base case 2: one node is null but other isn't
    if((treeNode == nullptr && otherTreeNode != nullptr) ||
    (treeNode != nullptr && otherTreeNode == nullptr)) {
        return false;
    }
    // Base case 3: nodes' data aren't equal
    if(treeNode->data->operator!=(*(otherTreeNode->data))) {
        return false;
    }
    // Recursive call on left subtrees
    if(!equalityHelper(treeNode->left, otherTreeNode->left)) {
        return false;
    }
    // Recursive call on right subtrees
    if(!equalityHelper(treeNode->right, otherTreeNode->right)) {
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------
// operator!=
// Preconditions: User must want to check if 2 trees do not have the same
//                structure and data in the nodes of the trees
// Postconditions: Returns true if trees have diferent structure/data, also if
//                 only one tree is empty, otherwise returns false
    bool BinTree::operator!=(const BinTree & otherTree) const {
        // Return inverse result of helper function call
        return(!equalityHelper(this->root, otherTree.root));
    }

//----------------------------------------------------------------------------
// insert
// Preconditions: NodeData to add is not a duplicate entry and is of same type
//                and comparable to those in the tree
// Postconditions: Node is created and added to the tree with NodeData equal to
//                 the argument, true is returned unless argument is duplicate
//                 which isn't added and false is returned
bool BinTree::insert(NodeData* dataptr) {
    Node* ptr = new Node;     // exception is thrown if memory is not allocated
    ptr->data = dataptr;
    dataptr = nullptr;
    ptr->left = ptr->right = nullptr;
    if (isEmpty()) {
        root = ptr;
    }
    else {
        Node* current = root;
        bool inserted = false;

        // if item is less than current item, insert in left subtree,
        // if item is greater than current item, insert in right subtree
        // if item is equal to current item, do not insert
        while (!inserted) {
            if (*ptr->data < *current->data) {
                if (current->left == nullptr) {         // at leaf, insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                    current = current->left;             // one step left
            }
            else if(*ptr->data > *current->data) {
                if (current->right == nullptr) {        // at leaf, insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                    current = current->right;            // one step right
            }
            else if(*ptr->data == *current->data) {
                delete ptr;
                ptr = nullptr;
                return false;
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------------
// retrieve
// Preconditions: second NodeData argument is unallocated and is expected to be
//                used to store the retrieved NodeData
// Postconditions: returns true if 1st argument is found in the tree and 2nd
//                 argument is set to point to this NodeData object, otherwise
//                 returns false and nothing is done with 2nd argument so it
//                 still points to garbage
bool BinTree::retrieve(const NodeData& toFind, NodeData*& toReturn) const {
    // Tree is empty, nothing to retrieve here
    if(isEmpty()) {
        return false;
    }
    // Tree has nodes, iteratively search tree for node
    Node* ptr = root;
    bool found = false;
    while(!found) {
        // Base case 1: current node is null
        if(ptr == nullptr) {
            break;
        }
        // Base case 2: correct node is found
        else if(*ptr->data == toFind) {
            found = true;
            toReturn = ptr->data;
        }
        // Search left subtree
        else if(*ptr->data > toFind) {
            ptr = ptr->left;
            continue;
        }
        // Search right subtree
        else {
            ptr = ptr->right;
        }
    }
    return found;
}

//----------------------------------------------------------------------------
// getSibling
// Preconditions: first NodeData argument exists in the tree and has a sibling
//                node in the tree
// Postconditions: true returned if the first NodeData argument exists in the
//                 tree AND the node has a valid sibling node, otherwise
//                 false is returned (if tree is empty or has only 1 node, node
//                 is an only child)
bool BinTree::getSibling(const NodeData & toFind, NodeData& toReturn) const {
    // Tree is empty so no sibling
    if(isEmpty()) {
        return false;
    }
    // Node is root of tree so no sibling
    if(*root->data == toFind) {
        return false;
    }
    // Begin recursive search using helper function
    return getSiblingHelper(root, toFind, toReturn);
}

bool BinTree::getSiblingHelper(Node* curPtr, const NodeData& toFind,
NodeData& toReturn) const {
    // Both children are null
    if(curPtr->left == nullptr && curPtr->right == nullptr) {
        return false;
    }
    // Left is null, right isn't
    if(curPtr->left == nullptr) {
        // If right matches search data, sibling isn't valid so return false
        if(*curPtr->right->data == toFind) {
            return false;
        }
        // Recursive search right subtree
        return getSiblingHelper(curPtr->right, toFind, toReturn);
    }
    // Right is null, left isn't
    if(curPtr->right == nullptr) {
        // If left matches search data, sibling isn't valid so return false
        if(*curPtr->left->data == toFind) {
            return false;
        }
        // Recursive search left subtree
        return getSiblingHelper(curPtr->left, toFind, toReturn);
    }
    // If left matches search data, return true
    if(*curPtr->left->data == toFind) {
        toReturn = *curPtr->right->data;
        return true;
    }
    // If right matches search data, return true
    if(*curPtr->right->data == toFind) {
        toReturn = *curPtr->left->data;
        return true;
    }
    // Recursive search of left subtree
    if(getSiblingHelper(curPtr->left, toFind, toReturn)) {
        return true;
    }
    // Recursive search of right subtree, last thing to check so return result
    return getSiblingHelper(curPtr->right, toFind, toReturn);
}

//----------------------------------------------------------------------------
// getParent
// Preconditions: first NodeData argument exists in the tree and has a parent
//                node in the tree
// Postconditions: true returned if the first NodeData argument exists in the
//                 tree AND the node has a parent node, otherwise false is
//                 returned (tree is empty, tree has only 1 node)
bool BinTree::getParent(const NodeData& toFind, NodeData& toReturn) const {
    // Tree is empty so there is no parent
    if(isEmpty()) {
        return false;
    }
    // Root is search node so there is no parent
    if(*root->data == toFind) {
        return false;
    }
    // Begin recursive search
    return getParentHelper(root, toFind, toReturn);
}

bool BinTree::getParentHelper(Node* curPtr, const NodeData& toFind,
NodeData& toReturn)const {
    // Both children are null
    if(curPtr->left == nullptr && curPtr->right == nullptr) {
        return false;
    }
    // Left pointer isn't null and matches search object
    if(curPtr->left != nullptr && *curPtr->left->data == toFind) {
        toReturn = *curPtr->data;
        return true;
    }
    // Right pointer isn't null and matches search object
    if(curPtr->right != nullptr && *curPtr->right->data == toFind) {
        toReturn = *curPtr->data;
        return true;
    }
    // Recursive search left subtree
    if(curPtr->left != nullptr) {
        if(getParentHelper(curPtr->left, toFind, toReturn)) {
            return true;
        }
    }
    // Recursive search right subtree
    if(curPtr->right != nullptr) {
        if(getParentHelper(curPtr->right, toFind, toReturn)) {
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------------------
// displaySideways
// Preconditions: None
// Postconditions: Displays a binary tree as though you are viewing it from the
//                 side, outputs nothing if tree is empty
void BinTree::displaySideways() const {
   sidewaysHelper(root, 0);
}

void BinTree::sidewaysHelper(Node* current, int level) const {
   if (current != nullptr) {
      level++;
      sidewaysHelper(current->right, level);

      // indent for readability, same number of spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "      ";
      }

      cout << *current->data << endl;        // display information of object
      sidewaysHelper(current->left, level);
   }
}

//----------------------------------------------------------------------------
// bstreeToArray
// Preconditions: Array passed as argument is a statically allocated array of
//                100 nullptr elements
// Postconditions: Nodes from the tree are placed into the array sequentially
//                 and tree is then emptied.
void BinTree::bstreeToArray(NodeData* dataPtrs[]) {
    // Initialize an int to use in recursive helper function call
    int index = 0;
    bstreeToArrayHelper(root, dataPtrs, index);
    // Second pass through tree to empty it
    makeEmpty();
    return;
}

void BinTree::bstreeToArrayHelper(Node* curPtr, NodeData* dataPtrs[],
int& index) const {
    // Base case 1: current node is null
    if(curPtr == nullptr) {
        return;
    }
    // Base case 2: index exceeds assumed array size
    if(index == 100) {
        return;
    }
    // Recursive call on left subtree
    bstreeToArrayHelper(curPtr->left, dataPtrs, index);
    // Set pointer in array to current node's NodeData and unassign
    // current pointer's data pointer
    dataPtrs[index] = curPtr->data;
    curPtr->data = nullptr;
    index++;
    // Recursive call on right subtree
    bstreeToArrayHelper(curPtr->right, dataPtrs, index);
    return;
}

//----------------------------------------------------------------------------
// arrayToBSTree
// Preconditions: Array passed as argument is already sorted beforehand, and is
//                a statically allocated array of 100 elements originally
//                initalized to nullptr and then filled from index 0 
// Postconditions: A balanced tree is built from the array and every index of
//                 the array is set to nullptr
void BinTree::arrayToBSTree(NodeData* dataPtrs[]) {
    // Clear the tree for insertion
    makeEmpty();
    // Find out how much of the array is used (how many nodes to add)
    int low = 0;
    int high = 0;
    for(int i = 0; i < 100; i++) {
        if(dataPtrs[i] == nullptr) {
            break;
        }
        high++;
    }
    // Array has only 1 node so just add it to tree
    if(high == 1) {
        insert(dataPtrs[0]);
        dataPtrs[0] = nullptr;
        return;
    }
    // Call helper function
    arrayToBSTreeHelper(low, high-1, dataPtrs);
    return;
}

void BinTree::arrayToBSTreeHelper(int low, int high, NodeData* dataPtrs[]) {
    // Boundary exception check
    if(low < 0 || high < 0) {
        return;
    }
    // Base case: sub array size is 1, add the NodeData object from this index
    if(low == high) {
        insert(dataPtrs[low]);     
        dataPtrs[low] = nullptr;    
        return;
    }
    // Divide the array in two
    int mid = (low + high) / 2;
    // Add middle node to the tree
    insert(dataPtrs[mid]);
    dataPtrs[mid] = nullptr;
    // Recursive call on left sub-array
    arrayToBSTreeHelper(low, mid-1, dataPtrs);
    // Recursive call on right sub-array
    arrayToBSTreeHelper(mid+1, high, dataPtrs);
}