#include "Set.h"

/**
 * Implement the LinkedListSet methods correctly
 */
unsigned int LinkedListSet::size() {
    return linked.size();
}

void LinkedListSet::insert(string s) {
    if(!find(s)){
        linked.push_back(s);
    }
    
}

void LinkedListSet::remove(const string & s) {
    linked.remove(s);
}

bool LinkedListSet::find(const string & s) {
    std::list<string>::iterator it = linked.begin();
    while(it != linked.end()){
        if (*it == s){
            return true;
        }
        ++it;
    }
    return false;
}
