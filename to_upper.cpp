#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

int main()
{
	const string in (
		istreambuf_iterator<char>(cin.rdbuf()),
		istreambuf_iterator<char>());

	cout << fplus::to_upper_case(in) << endl;

	return 0;
}
