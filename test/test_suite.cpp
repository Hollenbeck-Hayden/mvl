#include "test_suite.h"
#include <string>
#include <functional>
#include <vector>
#include <cstddef>
#include <iostream>
#include <sstream>


testing::TestError::TestError(const std::string& msg)
{
	message = msg;
}

const std::string& testing::TestError::getMessage() const
{
	return message;
}

void testing::Tester::addTest(const std::string& name, testing::test_func f)
{
	test_names.push_back(name);
	test_functions.push_back(f);
}

void testing::Tester::test()
{
	size_t failures = 0;
	std::cout << "Beginning testing..." << std::endl << std::endl;

	for (size_t i = 0; i < test_names.size(); i++)
	{
		std::cout << "Testing " << test_names[i] << "... ";
		try
		{
			(test_functions[i])();
			std::cout << "Success" << std::endl;
		}
		catch(TestError e)
		{
			failures++;
			std::cout << "Failure: " << e.getMessage() << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "Testing completed!" << std::endl;
	std::cout << "Total failures: " << failures << std::endl;
}

void testing::failUnimplemented()
{
	throw testing::TestError("Unimplemented");
}

void testing::checkFalse(bool t)
{
	if (t) throw testing::TestError("Expected false");
}

void testing::checkTrue(bool t)
{
	if (not t) throw testing::TestError("Expected true");
}
