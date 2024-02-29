#include <string>
#include <vector>
#include <algorithm> 
#include "SuffixArray.h"
using namespace std;

/**
 * Implement suffix_array() correctly
 */
vector<unsigned int> suffix_array(const string & s) {
    vector<unsigned int> arr;
    for(unsigned int i =0; i<s.size(); i++){
        arr.push_back(i);
    }
    std::sort(arr.begin(),arr.end(),
        [=](unsigned int i, unsigned int j){
            return (s.substr(i).compare(s.substr(j)) < 0);
        }
        );
    return arr;
}
