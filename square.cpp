#include <iostream>
#include <vector>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;


int square (int x)
{
	return x * x;
}
auto sqr_l = [](int x) -> int
{
	return square(x);
};

auto sqr_c = [](auto f)
{
	return [f](vector<int> xs) -> vector<int>
	{
		vector<int> ys;
		ys.reserve(xs.size());
		for(auto x : xs)
			ys.push_back(f(x));
		return ys;
	};
};

int main()
{
	vector<vector<int>> values = 
	{
		{0, 1, 2},
		{3, 4, 5}
	};


	auto result = fplus::transform(sqr_c(sqr_l), values);

	//auto result = transform(fwd::keep_if(valid), values);

	cout << show(result) << endl;

	return 0;
}
