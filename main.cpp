#include <iostream>
#include <fstream>
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
    unsigned char mem[len]; // changed arr to mem
    f1.seekg(0,ios::beg);
    f1.read((char*)mem,len);
    f1.close();

    int sp = 0;         //stackpointer
    int pc = 0;        // program counter
    int fpsp = 0;
    vector<Bytecode> rstack;        //runtime stack
    vector<Bytecode> fstack;         // frame stack
     

    int i = 0;
    for(int i = 0; i < len; ++i)
    {
        cout<< +mem[i] << endl;
    } 
	
	// adding data structures below
	// unsure if they should actually be in main or not...

    return EXIT_SUCCESS;
}
