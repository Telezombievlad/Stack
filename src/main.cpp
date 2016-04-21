#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "stack/Stack.hpp"

int main() 
{
	try
	{
		Stack::Stack<int> test{};

		test.push(666);
		test.push(228);
		std::cout << test.head() << std::endl;

		test.setHead(420);
		std::cout << test.head() << std::endl; 

		std::cout << test.pop() << std::endl;

		std::cout << test.empty() << std::endl;

		std::cin.ignore();

		test.pop();
		std::cout << test.empty() << std::endl;
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cin.ignore();

	return EXIT_SUCCESS;
}
