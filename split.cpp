#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

auto str_to_int = [](const string str)
	{
		int result;
		istringstream ss{str} ;
		ss >> result;

		return result;
	};

auto square_int = [](int x)
	{
		return x * x;
	};

int main()
{
	string str = "1,4,5,17,24";

	auto fn = fwd::compose(str_to_int, square_int);

	auto result = fwd::apply(
		fplus::split(',', false, str),
		fwd::transform(fn));

	cout << show(result) << endl;

	return 0;
}
