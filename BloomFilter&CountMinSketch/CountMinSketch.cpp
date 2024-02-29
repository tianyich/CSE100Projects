#include <limits>
#include "CountMinSketch.h"
#include "HashFunctions.h"

/**
 * Implement increment() correctly
 */
void CountMinSketch::increment(const string & s) {
    for(int i=0; i< K; i++){
        count[i][hash_functions[i](s)%M] += 1;
    }
}

/**
 * Implement find() correctly
 */
unsigned int CountMinSketch::find(const string & s) {
    unsigned int max = numeric_limits<unsigned int>::max();
    for(int i=0; i< K; i++){
      unsigned int curr = count[i][hash_functions[i](s)%M];
      if (curr < max) {
        max = curr;
      }
    }
    return max;

}
