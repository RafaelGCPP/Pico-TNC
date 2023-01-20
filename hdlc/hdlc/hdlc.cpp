// hdlc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>

int main()
{

	size_t nbytes = 54;
	char inputdata[54] = "~PU1OWL??/{Rafael Gustavo da Cunha Pereira Pinto\xe0}~_Z";

	size_t max_output_bytes = ((nbytes * 48) / 40)+1;
	size_t max_words = max_output_bytes/4;

	
	for (uint32_t *i = (uint32_t*) inputdata; *i ; i++)
		std::cout << std::bitset<32>(*i) << " - " << *i << std::endl;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
