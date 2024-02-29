#include "Set.h"

/**
 * Implement the RedBlackTreeSet methods correctly
 */
unsigned int RedBlackTreeSet::size() {
    return rbt.size();
}

void RedBlackTreeSet::insert(string s) {
    if(!find(s)){
        rbt.insert(s);
    }
}

void RedBlackTreeSet::remove(const string & s) {
    set<string>::iterator it = rbt.find(s);
    if(it != rbt.end()){
        rbt.erase(it);
    }
}

bool RedBlackTreeSet::find(const string & s) {
    set<string>::iterator it = rbt.find(s);
    if(it == rbt.end()){
        return false;
    }else{
        return true;
    }
}
