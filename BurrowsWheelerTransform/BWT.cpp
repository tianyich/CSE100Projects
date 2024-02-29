#include <string>
#include <algorithm> 
#include "BWT.h"
#include <vector>
using namespace std;

/**
 * Implement bwt() correctly
 */
string bwt(const string & s) {
    vector<string> arr;
    string result = "";
    for(unsigned int i=0; i<s.size(); i++){
        arr.push_back(s.substr(i)+s.substr(0,i));
    }
    std::sort(arr.begin(),arr.end(),
        [=](string a, string b){
            return (a.compare(b) < 0);
    });
    for(string t : arr){
        result = result + t[t.size()-1];
    }
    return result;
}
