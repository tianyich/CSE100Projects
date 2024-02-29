#include "Helper.h"
using namespace std;

int Helper::find_index(vector<string> v, string s){
        for(int i = 0; i<(int)v.size(); ++i){
            if (s.compare(v[i]) == 0){
                return i;
            }
        }
        return -1;
}
