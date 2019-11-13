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
		TestError(const std::string& msg);

		template<typename T>
		TestError(const T& actual, const T& expected)
		{
			std::stringstream ss;
			ss << "Expected: " << expected << ", Actual: " << actual;
			message = ss.str();
		}

		const std::string& getMessage() const;
	
	private:
		std::string message;
	};


	class Tester
	{
	public:
		void addTest(const std::string& name, test_func f);
		void test();

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

	void failUnimplemented();
	void checkTrue(bool t);
	void checkFalse(bool t);
};
