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

float str_to_float(string str)
{
	float result;

	istringstream{str} >> result;

	return result;
}

template <typename T>
	T sum(const vector<T> &values)
	{
		return reduce(plus<T>(), T(), values);
	}

int main()
{
	const string input = "1,2,3,4,5,1,2,3";
	const auto parts = split(',', false, input);
	const auto nums = fplus::transform(str_to_float, parts);

	const auto result = fplus::reduce(std::multiplies<float>(), 1.0f, nums);


	//cout << show(parts_as_int) << endl;
	cout << result << endl;

	return 0;
}
