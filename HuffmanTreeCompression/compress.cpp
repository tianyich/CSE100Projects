#include "Helper.hpp"
#include "HCTree.hpp"
#include <stdlib.h>


int main(int argc, char* argv[]){
    if (argc != 3){
        cerr << "ERROR: Incorrect parameters" << endl;
        cerr << "USAGE: ./compress <original_file> <compressed_file>" <<endl;
        return 1;
    }
    FancyInputStream i(argv[1]);
    FancyOutputStream o(argv[2]);
    if(i.filesize() == 0){
        return 0;
    }
    vector<int> freqs(256,0); 
    int read;
    int charCount = 0;
    int distinctChar = 0;
    while((read = i.read_byte()) != -1){
        if(freqs[read] == 0){
            distinctChar += 1;
        }
        freqs[read] += 1;
        charCount += 1;
    }
    o.write_int(charCount);
    o.write_byte(distinctChar);
    for(int j=0; j<256;j++){
        if(freqs[j] != 0){
            o.write_byte(j);
            o.write_int(freqs[j]);
        }
    }
        
    HCTree tree;
    tree.build(freqs); 
    i.reset();
    while((read = i.read_byte()) != -1){
        tree.encode(read,o);
    }
    
}
