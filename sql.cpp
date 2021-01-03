#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

struct user
{
	string name;
	string country;
	int visits;
};

string get_country(const user &u)
{
	return u.country;
}

int get_visits(const user &u)
{
	return u.visits;
}

ostream & operator << (ostream &out, const user &u)
{
	out << get_visits(u) << " ";

	return out;
}

int main()
{
	const vector<user> users = 
	{
		{"Nicole", "GER", 2},
		{"Justin", "USA", 1},
		{"Rachel", "USA", 5},
		{"Robert", "USA", 6},
		{"Stefan", "GER", 4}
	};

	//const user u1 = users.at(0);
	//cout << get_country(u1) << endl;
	

	

	auto result = fwd::apply(
		users,
		fwd::group_globally_on_labeled(
			[](const user &u)
			{
				return get_country(u); 
			}),
		fwd::transform(fwd::transform_snd(
				[](auto vu)
				{
					return fwd::apply(
						vu,
						fwd::transform(
							[](const user &u) -> int 
								{ return get_visits(u); }),
						fwd::sum()
						);
				}))
					

				
				
			/*[](auto p)
			{
				return fwd::apply(
					p,
					fwd::transform([](const user &u) { return get_visits(u);  }),
					fwd::sum()
				);
			}))*/

		);/*,
		fwd::transform_snd(fwd::mean()));*/

	cout << show(result) << endl;


	auto result2 = fwd::apply(
		users,
		fwd::sort_on(get_country),
		fwd::group_on_labeled(get_country),
		fwd::transform(fwd::transform_snd(
			[](auto sub_users)
			{
				return fwd::apply(
					sub_users,
					fwd::transform([](auto user) { return get_visits(user); }),
					fwd::sum()
				);
			}))
	);

	cout << show(result2) << endl;

	// SELECT country, SUM(visits)
	// 	FROM users
	// 	GROUP BY country;
	


	return 0;
}
