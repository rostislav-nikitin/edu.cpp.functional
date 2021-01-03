#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

int main()
{
	const string in (
		istreambuf_iterator<char>(cin.rdbuf()),
		istreambuf_iterator<char>());

	string result = fwd::apply(
		in,
		fwd::split_lines(false),
		fwd::sort(),
		fwd::join(string{"\n"})
	);

	cout << result << endl;
	return 0;
}
