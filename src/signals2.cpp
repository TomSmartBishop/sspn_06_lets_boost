#include <iostream>
#include <vector>
#include <cstdint>

#include <boost/signals2.hpp>

using std::cout;
using std::vector;
using std::int32_t;

using boost::signals2::signal;

struct Hello
{
	void operator()() const
	{
		cout << "Hello";
	}
};

struct World
{
	void operator()() const
	{
		cout << " World!\n";
	}
};

auto signals2_sample() -> void
{
	cout << "<Signals2 Sample>\n";

	signal<void()> sig;

	sig.connect(Hello());
	sig.connect(World());

	sig();
}
