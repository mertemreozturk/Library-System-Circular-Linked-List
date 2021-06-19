#include <iostream>
#include <string>
#include "LibrarySystem.cpp"
using namespace std;

int main(int argc,char* argv[]){
    
    LibrarySystem lb;
    lb.control(argv[1],argv[2]);   // start read from command.txt and write results to output file

    return 0;
}
