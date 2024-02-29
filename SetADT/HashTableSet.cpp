#include "Set.h"

/**
 * Implement the HashTableSet methods correctly
 */
unsigned int HashTableSet::size() {
    return ht.size();
}

void HashTableSet::insert(string s) {
    if(!find(s)){
        ht.insert(s);
    }
}

void HashTableSet::remove(const string & s) {
    if(find(s)){
        ht.erase(s);
    }
   
}

bool HashTableSet::find(const string & s) {
    unordered_set<string>::iterator it = ht.find(s);
    if (it == ht.end()){
        return false;
    }else{
        return true;
    }
}
