#include <iostream>
#include <map>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

template<typename ValOut, typename F, typename Key, typename ValIn>
	map<Key, ValOut> lift_dict(F f, map<Key, ValIn> dict)
	{
		map<int, ValOut> result {};

		for(auto p : dict)
			result.insert({p.first, f(p.second)});

		return result;
	};


int main()
{
	map<int, double> dict = 
		{{2, 1.41}, {3, 1.73}, {4, 2.0}};

	auto sqr_dict = lift_dict<double>(square<double>, dict);
	auto show_dict = lift_dict<string>(show<double>, dict);

	cout << show_cont(sqr_dict) << endl;

	return 0;
}
