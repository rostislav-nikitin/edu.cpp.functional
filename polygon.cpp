#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;

typedef pair<float, float> point;

float point_distance(const point &p1, const point &p2)
{
	const float dx = p2.first - p1.first;
	const float dy = p1.first - p1.first;

	const float result = sqrt(dx * dx + dy * dy);

	return result;
}

int main()
{
	vector<point> polygon =
		{{1, 2}, {7, 3}, {6, 5}, {4, 4}, {2, 9}};

	const auto edges = fplus::overlapping_pairs_cyclic(polygon);
	const auto result = fplus::maximum_on([](auto pt)
			{
				return point_distance(pt.first, pt.second);
			}
			, edges);

	cout << fplus::show(result) << endl;


	return 0;
}
