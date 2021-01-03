#include <iostream>
#include <functional>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

int str_to_int(string str)
{
	int result;

	istringstream{str} >> result;

	return result;
}

template <typename T>
	T sum(const vector<T> &values)
	{
		return reduce(plus<T>(), T(), values);
	}

template <typename T>
	T multiply(const vector<T> &values)
	{
		return reduce(std::multiplies<T>(), T() + 1, values);
	}

int main()
{
	const string input = "1,2,3,4,5,1,2,3";
	const auto parts = split(',', false, input);
	const auto parts_as_int = fplus::transform(str_to_int, parts);

	//const auto sum = fplus::reduce(plus<int>(), 0, parts_as_int);
	//
	auto result = sum(parts_as_int);
	//cout << show(parts_as_int) << endl;
	cout << result << endl;

	result = multiply(parts_as_int);
	//cout << show(parts_as_int) << endl;
	cout << result << endl;

	return 0;
}
