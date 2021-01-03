#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

typedef pair<float, float> point;

//auto edge_length_c = []()
//{
auto edge_length = [](auto points)
{
	auto p1 = points.first;
	auto p2 = points.second;
	auto dx = p2.first - p1.first;
	auto dy = p2.second - p1.second;

	return sqrt(dx * dx + dy * dy);
};

auto get_edges_c = []()
{
	return  [](auto polygon)
	{
		return fplus::overlapping_pairs_cyclic(polygon);
	};
};

int main()
{
	vector<point> polygon = 
		{
			{1, 2}, {7, 3}, {6, 5}, {4, 4}, {2, 9}
		};
	auto result = fwd::apply(
			polygon,
			get_edges_c(),
			fwd::maximum_on(edge_length));
		/*fplus::maximum_on(
			edge_length, 
			get_edges(polygon)); */
		

	cout << show(result) << endl;
	return 0;
}
