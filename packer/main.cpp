#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
	std::ofstream output;
 	output.open(argv[1]);
	int i;
	for(i = 2; i < argc; i++)
	{
		std::ifstream t(argv[i]);
		std::stringstream buffer;
		buffer << t.rdbuf();
 		output << buffer.str();
	}
	output.close();
	return 0;
}
