#include <iostream>
#include <fstream>
#include "Bytecode.h"
#include "Datatype.h"
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	ifstream file("interpreter_input.smp", ios::binary);
	//ifstream file(argv[1], ios::binary);

	file.unsetf(ios::skipws);
	streampos fileSize;
	file.seekg(0, ios::end);
	fileSize = file.tellg();
	file.seekg(0, ios::beg);

	cout << "size:" << fileSize << endl;

	vector<unsigned char> mem;
	
	mem.reserve(fileSize);

	mem.insert(mem.begin(), istreambuf_iterator<char>(file), istreambuf_iterator<char>());

	file.close();

	 //mem.reserve(11);
	 //mem.push_back((unsigned char) 70);
	 //mem.push_back((unsigned char) 16);
	 //mem.push_back((unsigned char) 0);
	 //mem.push_back((unsigned char) 0);
	 //mem.push_back((unsigned char) 0);
	 //mem.push_back((unsigned char) 70);
	 //mem.push_back((unsigned char) 17);
	 //mem.push_back((unsigned char) 0);
	 //mem.push_back((unsigned char) 0);
	 //mem.push_back((unsigned char) 0);
	 //mem.push_back((unsigned char) 132);

	for (int i = 0; i < fileSize; ++i)
	{
		cout << +mem[i] << endl;
	}

	// Separate code for testing for add functionality

	Bytecode * bytecode = new Bytecode(mem,fileSize);

	//return EXIT_SUCCESS;
	return 0;
}
