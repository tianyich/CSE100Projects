#include "BST.h"
#include <vector>

BST::BST() { 
    root = nullptr;
    numElements = 0;
}

BST::~BST() {
    BST::clear();
}

unsigned int BST::size() const {
    /* YOUR CODE HERE */
    return numElements;
}

void helper(BST::Node* node){
    if(node == nullptr){
        return;
    }
    helper(node->leftChild);
    helper(node->rightChild);
    delete node;
    node = nullptr;
}

void BST::clear() {
    helper(root);
    numElements = 0;
    root = nullptr;
}

bool BST::insert(int element) {
    /* YOUR CODE HERE */
    if(BST::find(element)){
        return false;
    }
    if(root == nullptr){
        root = new Node(element);
        numElements += 1;
        return true;
    }
    
    BST::Node* currNode = root;
    while(true){
        if(currNode->data > element ){
            if(currNode->leftChild == nullptr){
                currNode->leftChild = new Node(element);
                currNode->leftChild -> parent = currNode;
                BST::numElements += 1;
                return true;
            }
            else{
                currNode = currNode ->leftChild;
            }
        }
        else {
            if(currNode->rightChild == nullptr){
                currNode->rightChild = new Node(element);
                currNode->rightChild->parent = currNode;
                BST::numElements += 1;
                return true; 
            }
            else{
                currNode = currNode ->rightChild;
            }
                
        }
    }
}

bool BST::find(const int & query) const {
    BST::Node* currNode = root;
    while(currNode != nullptr){
        if(currNode->data > query){
            currNode = currNode->leftChild;
        }else if(currNode->data < query){
            currNode = currNode ->rightChild;
        }else{
            return true;
        }
    }
    return false;
}

BST::Node* BST::getLeftMostNode() {
    if(root == nullptr){
        return nullptr;
    }
    BST::Node* currNode = BST::root;
    while(currNode->leftChild != nullptr){
        currNode = currNode->leftChild;
    } 
    return currNode;
}

BST::Node* BST::Node::successor() {
    /* YOUR CODE HERE */
    BST::Node* currNode = this;
    if(this->rightChild != nullptr){
        currNode = currNode->rightChild;
        while(currNode->leftChild != nullptr){
            currNode = currNode->leftChild;
        }
        return currNode;
    }
    else{ 
        BST::Node* currParent = currNode->parent;
        while(true){
            if(currParent == nullptr){
                return nullptr;
            }
            if(currParent->leftChild == currNode){
                return currParent;
            }
            currNode = currNode-> parent;
            currParent = currParent->parent;
        }   
    }
    return nullptr;
}

