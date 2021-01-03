#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

auto logging(std::function<int(int)> f)
{
	return [f](int x)
	{
		int result = f(x);
		cout << "F(" << x << ")=" << result << endl;
		return result;
	};
}

int sqr(int x)
{
	return x * x;
}

int main()
{
	logging(sqr)(4);
	return 0;
}
