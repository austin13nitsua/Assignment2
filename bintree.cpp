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

//----------------------------------------------------------------------------
    void BinTree::displaySideways() const {
        // TBC
        return;
    }

//----------------------------------------------------------------------------
bool BinTree::getSibling(const NodeData &, NodeData&) const {
    return false;
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