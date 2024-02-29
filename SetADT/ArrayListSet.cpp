#include "Set.h"

/**
 * Implement the ArrayListSet methods correctly
 */
unsigned int ArrayListSet::size() {
    return arr.size();
}

void ArrayListSet::insert(string s) {
    if(!find(s)){
        arr.push_back(s);
    }
}

void ArrayListSet::remove(const string & s) {
    vector<string>::iterator it = arr.begin();
    while(it != arr.end()){
        if (*it == s){
            arr.erase(it);
            return;
        }
        ++it;
    }
}

bool ArrayListSet::find(const string & s) {
    vector<string>::iterator it = arr.begin();
    while(it != arr.end()){
        if (*it == s){
            return true;
        }
        ++it;
    }
    return false;
}
