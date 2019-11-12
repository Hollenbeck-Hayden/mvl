#pragma once

#include <string>
#include <functional>
#include <vector>
#include <cstddef>
#include <iostream>
#include <sstream>

namespace testing
{
	using test_func = std::function<void(void)>;

	class TestError
	{
	public:
		TestError(const std::string& msg)
		{
			message = msg;
		}

		template<typename T>
		TestError(const T& actual, const T& expected)
		{
			std::stringstream ss;
			ss << "Expected: " << expected << ", Actual: " << actual;
			message = ss.str();
		}

		const std::string& getMessage()
		{
			return message;
		}
	
	private:
		std::string message;
	};


	class Tester
	{
	public:
		void addTest(const std::string& name, test_func f)
		{
			test_names.push_back(name);
			test_functions.push_back(f);
		}

		void test()
		{
			size_t failures = 0;
			std::cout << "Beginning testing..." << std::endl << std::endl;

			for (size_t i = 0; i < test_names.size(); i++)
			{
				std::cout << "Testing " << test_names[i] << std::endl;
				try
				{
					(test_functions[i])();
				}
				catch(TestError e)
				{
					failures++;
					std::cout << "Failure" << std::endl;
					std::cout << e.getMessage() << std::endl;
				}

				std::cout << std::endl;
			}

			std::cout << std::endl;
			std::cout << "Testing completed!" << std::endl;
			std::cout << "Total failures: " << failures << std::endl;
		}

	private:
		std::vector<std::string> test_names;
		std::vector<test_func> test_functions;
	};

	template<typename T>
	void checkEquals(const T& a, const T& b)
	{
		if (a != b)
			throw TestError(a, b);
	}
};
