#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

//using str_fn = std::function<string(string)>;


template<typename F>
	void cmd(F f)
	{
		cout << f(string (istreambuf_iterator<char>(cin.rdbuf()),
				istreambuf_iterator<char>())) << endl;
	}

//void cmd = []()

int main()
{
	cmd(fwd::compose(
		fwd::to_upper_case(), 
		fwd::split_lines(false), 
		fwd::sort(), 
		fwd::join(string{"\n"})));

	return 0;
}
