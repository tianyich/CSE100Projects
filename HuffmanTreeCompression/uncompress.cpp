#include "Helper.hpp"
#include "HCTree.hpp"
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 3){
        cerr << "ERROR: Incorrect parameters" << endl;
        cerr << "USAGE: ./uncompress <compressed_file> <uncompressed_file>" <<endl;
        return 1;
    }
    FancyInputStream i(argv[1]);
    FancyOutputStream o(argv[2]);
    vector<int> freqs(256,0);
    if(i.filesize() == 0){
        return 0;
    }
    int charCount = i.read_int();
    int distinctChar = i.read_byte();
    for(int j = 0; j< distinctChar; j++){
        int index = i.read_byte();
        int frequency = i.read_int();
        freqs[index] = frequency;
    }
    HCTree tree;
    tree.build(freqs);
    int decodeCount = 0;
    while(i.good()&&decodeCount<charCount){
        o.write_byte(tree.decode(i));
        decodeCount += 1;
    }
    return 0;
}
