#include "HCTree.hpp"
#include "Helper.hpp"
#include <queue>

void HCTree::build(const vector<int>& freqs){
    priority_queue<HCNode*,vector<HCNode*>, HCNodePtrComp> pq;
    for(int i = 0; i < (int)freqs.size(); i++){
        if(freqs[i] != 0){
            HCNode* newNode = new HCNode(freqs[i],(unsigned char)i);
            leaves[i] = newNode;
            pq.push(newNode);
        }
    }
    while(pq.size()>1){
        HCNode* t1 = pq.top();
        pq.pop();
        HCNode* t2 = pq.top();
        pq.pop();
        HCNode* t3 = new HCNode(t1->count+t2->count, 0);
        t3 -> c1 = t1;
        t3 -> c0 = t2;
        t1 -> p = t3;
        t2 -> p = t3;
        pq.push(t3);
    }
    root = pq.top();
    pq.pop();
}
void helper(HCNode* root){
    if(root == nullptr){
        return;
    }
    helper(root->c0);
    helper(root->c1);
    delete root;
    root = nullptr;
}

HCTree::~HCTree(){
    helper(root);
    root = nullptr;
    leaves.clear();
}

void recEncode(HCNode* node, FancyOutputStream & out, HCNode* root){
    HCNode* parent = node->p;
    if (parent!= root){
        recEncode(parent,out,root);
    }
    if (parent->c0 == node){
        out.write_bit(0);
    }else{
        out.write_bit(1);
    }
}   


void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const{
    recEncode(leaves[int(symbol)],out,root);
}



unsigned char HCTree::decode(FancyInputStream & i) const{
    HCNode* current = root;
    while(current->c0!=nullptr && current->c1!=nullptr){
        int read = i.read_bit();
        if(read == 0){
            current = current -> c0;
        }else{
            current = current -> c1;
        }
    }
    return current->symbol;
}


