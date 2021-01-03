#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

typedef vector<int> Ints;

struct Even
{
	int operator()(const int x) const noexcept
	{
		return x % 2 == 0;
	}
};

int square(int x)
{
	return x * x;
}

template<typename F, typename T>
	vector<T> keep_if(F f, const vector<T> &xs)
	{
		vector<T> ys;
		//ys.reserve(xs.size());
		//transform(begin(xs), end(xs), back_inserter(ys), f);

		auto itr_found = std::find_if(begin(xs), end(xs), f);
		while(itr_found != end(xs))
		{
			ys.pushback(*itr_found);
			++itr_found;
		}

		return ys;
	}

template<typename T>
	void show(const vector<T> &items)
	{
		for(auto item : items)
			cout << item << " ";
		cout << endl;
	}

const int REPEAT_COUNT = 10000;
int main()
{
	Even even;
	Ints in(16384);//{1, 2, 3, 4, 5, 6, 7};

	for(int i = 0; i < REPEAT_COUNT; ++i)
		auto res = keep_if(even, in);

	//show(res);
	
	

	return 0;
}
