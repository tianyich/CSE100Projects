#include "Set.h"

/**
 * Implement the MultiwayTrieSet constructor
 */
MultiwayTrieSet::MultiwayTrieSet() {
    numElements = 0;
    root = new Node();
}

/**
* Helper function for destructor
*/
void recursionDelete(MultiwayTrieSet::Node* root){
    if (root->children.size()==0){
        return;
    }
    for(auto child : root->children){
         recursionDelete(child.second);
         delete child.second;
    }
}
/**
 * Implement the MultiwayTrieSet destructor
 */
MultiwayTrieSet::~MultiwayTrieSet() {
    recursionDelete(root);
    delete root;
    root = nullptr;
    numElements = 0;
}

/**
 * Implement the MultiwayTrieSet methods correctly
 */
unsigned int MultiwayTrieSet::size() {
   return numElements;
}

void MultiwayTrieSet::insert(string s) {
    Node* curr = root;
    for(char c: s){
        if(curr->children.find(c)==curr->children.end()){
            curr->children[c] = new Node();
        }
        curr = curr->children[c];
    }
    if (!curr->isWord){
        curr->isWord = true;
        numElements += 1;
    }
}

void MultiwayTrieSet::remove(const string & s) {
    Node* curr = root;
    
    for(char c: s){
        if(curr->children.find(c)==curr->children.end()){
            return;
        }
        curr = curr->children[c];
        
    }
    if (curr->isWord){
        curr->isWord = false;
        numElements -= 1;
    }
}

bool MultiwayTrieSet::find(const string & s) {
    Node* curr = root;
    for(char c: s){
        if(curr->children.find(c)==curr->children.end()){
            return false;
        }
        curr = curr->children[c];
    }
    if (curr->isWord){
        return true;
    }else{
        return false;
    }

}
