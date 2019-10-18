#include <iostream>
#include <fstream>
//#include "Bytecode.h"
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	ifstream file("interpreter_input.smp", ios::binary);
	
	file.unsetf(ios::skipws);
	streampos fileSize;
	file.seekg(0, ios::end);
	fileSize = file.tellg();
	file.seekg(0, ios::beg);

	cout << "size:" << fileSize << endl;

	vector<unsigned char> mem;
	mem.reserve(fileSize);

	mem.insert(mem.begin(), istreambuf_iterator<char>(file), istreambuf_iterator<char>());

	int i = 0;
	for (int i = 0; i < fileSize; ++i)
	{
		cout << +mem[i] << endl;
	}

	return EXIT_SUCCESS;
}
