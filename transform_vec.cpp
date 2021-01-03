#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

typedef vector<int> Ints;

struct Square
{
	int operator()(const int x) const noexcept
	{
		return x * x;
	}
};

int square(int x)
{
	return x * x;
}

template<typename F, typename T, int size>
	void transform_vec(F f, const T (&xs)[size])
	{
		T ys[size];
		//ys.reserve(xs.size());
		//transform(begin(xs), end(xs), back_inserter(ys), f);
		for(int i = 0; i < size; ++i)
		{
			ys[i] = f(xs[i]);
		}

		//return ys;
	}

int main()
{
	Square s;
	//const Ints source(65535); //{0, 1, 2, 3, 4};
	int source[65535];
	for(int iter = 0; iter < 10000; ++iter)
	{
//		for(int i = 0; i < sizeof(source) / sizeof(int); ++i)
//		{
			transform_vec(s, source);
//		}
	}

	return 0;
}
