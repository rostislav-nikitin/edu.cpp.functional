#include <iostream>
#include <fstream>
#include <vector>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

typedef vector<string> Strings;
typedef vector<int> Ints;

result<string, string> get_path(Strings arguments)
{
	if(arguments.size() < 2)
		return error<string, string>(string{"Invalid arguments: filename not specified."});
	else
		return fplus::ok<string, string>(arguments[1]);
}

result<string, string> get_content(string fpath)
{
	char *res;
	ifstream in {fpath};
	if(!in.good())
		return error<string, string>(string{"Can not read file."});

	return ok<string, string>(trim_whitespace( std::string(
		istreambuf_iterator<string::value_type>(in),
		istreambuf_iterator<string::value_type> ())));
}

result<Strings, string> split_content (string str)
{
	auto result = fplus::split(',', false, str);
	if(result.size() == 0)
		return error<Strings, string>(string{"The file is empty."});
	return ok<Strings, string>(result);

}

result<int, string> calc_median(Ints xs)
{
	if(xs.size() > 0)
		return ok<int, string>(fplus::median(xs));
	else
		return error<int, string>(string{"The array of ints is empty."});
}

result<Ints, string> strings_to_ints(Strings strs)
{
	auto result_values = fplus::transform(fplus::read_value_result<int>, strs);
	if(all_by(fplus::is_ok<int,string>, result_values))
		return ok<Ints, string>(oks(result_values));
	else
		return error<Ints, string>(string{"Some of string elements can not be converted to the ints."});
}

template<typename InT, typename OutT, typename F>
	auto and_then(F f)
	{
		return [f](result<InT, string> in)
		{
			if(in.is_error())
				return error<OutT, string>(in.unsafe_get_error());
			else
				return f(in.unsafe_get_ok());
		};
	}

int main(int argc, char *argv[])
{
	// Pipeline (apply)
	const Strings arguments(argv, argv+argc);
	auto apply_res = fwd::apply(
			arguments,
			get_path,
			and_then<string, string>(get_content),
			and_then<string, Strings>(split_content),
			and_then<Strings, Ints>(strings_to_ints),
			and_then<Ints, int>(calc_median));

	if(!apply_res.is_error())
		cout << show(apply_res.unsafe_get_ok()) << endl;
	else
		cout << show(apply_res.unsafe_get_error()) << endl;

	// Superposition (compose)
	auto comp = compose_result (
			get_path, 
			get_content,
			split_content,
			strings_to_ints,
			calc_median);
	auto comp_res = comp(arguments);
	if(!comp_res.is_error())
		cout << show(comp_res.unsafe_get_ok()) << endl;
	else
		cout << show(comp_res.unsafe_get_error()) << endl;


	return 0;
}
