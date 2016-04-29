#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "stack/Stack.hpp"

// RPN Stack caclulator

int calculate(const std::string& input, int startVal = 0)
{
	if (input.empty()) return 0;

	MyStack::Stack<int> values{};

	values.push(startVal);

	bool prevWasNum = false;
	for (unsigned char i : input)
	{
		if ('0' <= i && i <= '9')
		{
			if (prevWasNum && values.head())
			{
				throw std::invalid_argument("Numbers cant start with 0");
			}

			if (prevWasNum && !values.empty())
			{
				values.setHead(values.head() * 10 + (i - '0'));
			}	
			else
			{
				values.push(i - '0');
			}
			
			prevWasNum = true;

			continue;
		}

		prevWasNum = false;

		if (i == '+' || i == '-' || i == '*' || i == '/' || i == '%')
		{
			if (values.empty()) throw std::invalid_argument("Parse error"); 

			int second = values.pop();

			if (values.empty()) throw std::invalid_argument("Parse error"); 

			int first = values.pop();

			switch (i)
			{
				case '+':
				{
					values.push(first + second);

					break;
				}
				case '-':
				{
					values.push(first - second);

					break;
				}
				case '*':
				{
					values.push(first * second);

					break;
				}
				case '/':
				{
					if (second == 0) throw std::invalid_argument("Divide by zero"); 

					values.push(first / second);

					break;
				}
				case '%':
				{
					values.push(first % second);

					break;
				}
				default: break;
			}
		}
	}

	if (values.empty()) throw std::invalid_argument("Parse error"); 

	return values.pop();
}

int main() 
{
	try
	{
		/*
		std::string input;

		int startVal = 0;
		while (input != std::string("exit"))
		{
			startVal = calculate(input, startVal);

			std::cout << startVal << std::endl;

			getline(std::cin, input, '\n');
		}
		*/

		MyStack::Stack<int> initListStack = {1, 2, 3, 4, 5};

		std::cout << initListStack.pop() << " " << initListStack.head() << std::endl;

		std::cout << initListStack.pop() << std::endl;
		
		std::cout << initListStack.head() << std::endl;	
	}
	catch (std::invalid_argument ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (std::out_of_range ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unexpected exception" << std::endl;
	}

	std::cin.ignore();

	return EXIT_SUCCESS;
}
