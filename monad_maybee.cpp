#include <iostream>
#include <fstream>
#include <vector>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

typedef vector<string> Strings;
typedef vector<int> Ints;

maybe<string> get_path(Strings arguments)
{
	if(arguments.size() < 2)
		return nothing<string>();
	else
		return just(arguments[1]);
}

maybe<string> get_content(string fpath)
{
	char *res;
	ifstream in {fpath};
	if(!in.good())
		return nothing<string>();

	return just(trim_whitespace( std::string(
		istreambuf_iterator<string::value_type>(in),
		istreambuf_iterator<string::value_type> ())));
}

maybe<Strings> split_content (string str)
{
	auto result = fplus::split(',', false, str);
	if(result.size() == 0)
		return nothing<Strings>();
	return just(result);

}

maybe<int> calc_median(Ints xs)
{
	if(xs.size() > 0)
		return just(fplus::median(xs));
	else
		return nothing<int>();
}

/*maybe<int> str_to_int(string str)
{
	int result;
	istringstream (str) >> result;

	return result;
}*/


maybe<Ints> strings_to_ints(Strings strs)
{
	//cout << show_cont(strs) << endl;	
	auto maybe_values = fplus::transform(fplus::read_value<int>, strs);
//	cout << fplus::show_cont(maybe_values) << endl;
	//for(auto x : maybe_values)
	//	cout << x.is_nothing() << " " << endl;
	//cout << all_by(is_just<int>, maybe_values) << endl;
	if(all_by(is_just<int>, maybe_values))
		return just<Ints>(justs(maybe_values));
	else
		return nothing<Ints>();

}

template<typename InT, typename OutT, typename F>
	auto and_then(F f)
	{
		return [f](maybe<InT> in)
			{
				if(in.is_nothing())
					return nothing<OutT>();
				else
					return f(in.unsafe_get_just());
			};
	};

int main(int argc, char *argv[])
{
	// Pipeline (apply)
	const Strings arguments (argv, argv+argc);
	auto apply_res = fwd::apply(
		arguments,
		get_path,
		and_then<string, string>(get_content),
		and_then<string, Strings>(split_content),
		and_then<Strings, Ints>(strings_to_ints),
		and_then<Ints, int>(calc_median)
		);

	if(!apply_res.is_nothing())
		cout << show(apply_res.unsafe_get_just()) << endl;
	else
		cout << "nothing" << endl;

	// Superposition (compose)
	auto comp = compose_maybe(
			get_path, 
			get_content,
			split_content,
			strings_to_ints,
			calc_median);
	auto comp_res = comp(arguments);
	if(!comp_res.is_nothing())
		cout << show(comp_res.unsafe_get_just()) << endl;
	else
		cout << "nothing" << endl;
		

	


	

	return 0;
}
