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
    unsigned char arr[len];
    f1.seekg(0,ios::beg);
    f1.read((char*)arr,len);
    f1.close();

    int i = 0;
    for(int i = 0; i < len; ++i)
    {
        cout<< +arr[i] << endl;
    } 

    return EXIT_SUCCESS;
}