#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

template<typename T>
	T add_four(T x1, T x2, T x3, T x4)
	{
		return x1 + x2 + x3 + x4;
	}

auto add_four_c = [](auto x1)
{
	return [x1](auto x2)
	{
		return [x1, x2](auto x3)
		{
			return [x1, x2, x3] (auto x4)
			{
				return add_four(x1, x2, x3, x4);
			};
		};
	};
};

int main()
{
	cout << add_four(1, 5, 17, 45) << endl;
	cout << add_four_c(1)(5)(17)(45) << endl;
	return 0;
}
