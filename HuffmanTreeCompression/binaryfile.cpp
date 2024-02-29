#include "Helper.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    FancyOutputStream o("binarytest");
    srand (time(NULL));
    for(int i = 0; i< 1000; i++){
        int bit = rand()%2;
        o.write_bit(bit);
    }
}
