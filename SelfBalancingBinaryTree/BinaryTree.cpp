#include "BinaryTree.h"

//Get height of a specific node;
int getHeight(BinaryTree::Node* node){
    if (node == nullptr){
        return 0;
    }
    if (node->leftChild == nullptr && node -> rightChild == nullptr){
        return 1;
    }
    int leftHeight, rightHeight;
    if (node->leftChild == nullptr){
        leftHeight = 0;
    }
    else{
        leftHeight = getHeight(node->leftChild);
    }
    if (node->rightChild == nullptr){
        rightHeight = 0;
    }
    else{
        rightHeight = getHeight(node->rightChild);
    }
    if (rightHeight > leftHeight){
        return rightHeight + 1;
    }
    else{
        return leftHeight + 1;
    }
}

//Traversal the tree by post-order, update map accordingly.
void post_order(BinaryTree::Node* root, unordered_map<int,int>* map){
    if(root == nullptr){
        return;
    }
    
    post_order(root->leftChild, map);
    post_order(root->rightChild, map);
    (*map)[root->label] = getHeight(root->rightChild)-getHeight(root->leftChild);
}
/**
 * Implement balanceFactors() correctly
 */
unordered_map<int,int> BinaryTree::balanceFactors() {
    unordered_map<int,int> map;
    post_order(root, &map);
    return map;
    
}
