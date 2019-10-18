#include <iostream>
#include <fstream>
#include "Bytecode.h"

using namespace std;

int main(int argc, char ** argv)
{
    ifstream f1("interpreter_input.smp");
    if(f1 == NULL)
    {
        cout<<"ERROR"<<endl;
        return EXIT_FAILURE;
    }
    f1.seekg(0,ios::end);
    size_t len = f1.tellg();
    vector<char> mem; // changed arr to mem
    f1.seekg(0,ios::beg);
    f1.read((char*)mem,len);
    f1.close();

    int i = 0;
    for(int i = 0; i < len; ++i)
    {
        cout<< +mem[i] << endl;
    } 
	
	// adding data structures below
	// unsure if they should actually be in main or not...

    return EXIT_SUCCESS;
}
