#include "bintree.h"

//----------------------------------------------------------------------------
// Constructors and Destructor

// Default constructor
BinTree::BinTree() {
    root = nullptr;
}

// Copy constructor
BinTree::BinTree(const BinTree & otherTree) {
    copyHelper(this->root, otherTree.root);
}

void BinTree::copyHelper(Node*& newTreeNode, const Node* oldTreeNode) {
    if(oldTreeNode == nullptr) {
        newTreeNode = nullptr;
        return;
    }
    newTreeNode = new Node;
    newTreeNode->data = new NodeData(*(oldTreeNode->data));
    copyHelper(newTreeNode->left, oldTreeNode->left);
    copyHelper(newTreeNode->right, oldTreeNode->right);
}

// Destructor
BinTree::~BinTree() {
    makeEmpty();
}

//----------------------------------------------------------------------------
// isEmpty
// true if tree is empty, otherwise false
bool BinTree::isEmpty() const {
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
    makeEmptyHelper(root);
} 

void BinTree::makeEmptyHelper(Node*& treeNode) {
    if(treeNode == nullptr) {
        return;
    }
    makeEmptyHelper(treeNode->left);
    makeEmptyHelper(treeNode->right);
    delete treeNode->data;
    treeNode->data = nullptr;
    delete treeNode;
    treeNode = nullptr;
}

//----------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree& otherTree) {
    copyHelper(this->root, otherTree.root);
    return *this;
}

//----------------------------------------------------------------------------
bool BinTree::operator==(const BinTree & otherTree) const {
    return(equalityHelper(this->root, otherTree.root));
}

bool BinTree::equalityHelper(const Node* treeNode, const Node* otherTreeNode)
const {
    if(treeNode == nullptr && otherTreeNode == nullptr) {
        return true;
    }
    if(treeNode == nullptr && otherTreeNode != nullptr) {
        return false;
    }
    if(treeNode != nullptr && otherTreeNode == nullptr) {
        return false;
    }
    if(treeNode->data->operator!=(*(otherTreeNode->data))) {
        return false;
    }
    if(!equalityHelper(treeNode->left, otherTreeNode->left)) {
        return false;
    }
    if(!equalityHelper(treeNode->right, otherTreeNode->right)) {
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------
    bool BinTree::operator!=(const BinTree & otherTree) const {
        return(!equalityHelper(this->root, otherTree.root));
    }

//----------------------------------------------------------------------------
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
                if (current->left == nullptr) {           // at leaf, insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                    current = current->left;               // one step left
            }
            else if(*ptr->data > *current->data) {
                if (current->right == nullptr) {          // at leaf, insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                    current = current->right;              // one step right
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
bool BinTree::retrieve(const NodeData& toFind, NodeData*& toReturn) const {
    // Tree is empty, nothing to retrieve here
    if(isEmpty()) {
        return false;
    }
    // Tree has nodes
    Node* ptr = root;
    bool found = false;
    while(!found) {
        if(ptr == nullptr) {
            break;
        }
        else if(*ptr->data == toFind) {
            found = true;
            toReturn = ptr->data;

        }
        else if(*ptr->data > toFind) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }
    return found;
}

//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side.
// Turn head 90 degrees counterclockwise (to the left) to see tree structure.
// Hard coded displaying to standard output.

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
bool BinTree::getSibling(const NodeData & toFind, NodeData& toReturn) const {
    // Tree is empty so no sibling
    if(isEmpty()) {
        return false;
    }
    // Node is root of tree so no sibling
    if(*root->data == toFind) {
        return false;
    }
    // Begin recursive search
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
        if(*curPtr->right->data == toFind) {
            return false;
        }
        return getSiblingHelper(curPtr->right, toFind, toReturn);
    }
    // Right is null, left isn't
    if(curPtr->right == nullptr) {
        if(*curPtr->left->data == toFind) {
            return false;
        }
        return getSiblingHelper(curPtr->right, toFind, toReturn);
    }
    // Check left's data
    if(*curPtr->left->data == toFind) {
        toReturn = *curPtr->right->data;
        return true;
    }
    // Check right's data
    if(*curPtr->right->data == toFind) {
        toReturn = *curPtr->left->data;
        return true;
    }
    // Recursive search left subtree
    if(getSiblingHelper(curPtr->left, toFind, toReturn)) {
        return true;
    }
    // Return results of recursive search of right subtree
    return getSiblingHelper(curPtr->right, toFind, toReturn);
}

//----------------------------------------------------------------------------
bool BinTree::getParent(const NodeData &, NodeData&) const {
    return false;
}

//----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* []) {
    return;
}

//----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* []) {
    return;
}

ostream& operator<<(ostream& os, const BinTree& binTree) {
    return os;
}