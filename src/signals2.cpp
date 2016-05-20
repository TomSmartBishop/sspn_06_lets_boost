#include <iostream>
#include <vector>
#include <cstdint>

#include <boost/signals2.hpp>

#include "float32.h"

using std::cout;
using std::vector;
using std::int32_t;
using fp::float32_t;

using boost::signals2::signal;

struct hello
{
	void operator()() const
	{
		cout << "Hello ";
	}
};

struct world
{
	void operator()() const
	{
		cout << "World!";
	}
};

struct sspn
{
	void operator()() const
	{
		cout << "...and hello SSPN!";
	}
};

void report_position(float32_t x, float32_t y)
{
	cout << "\n@position x: " << x << " y: " << y ;
}

void report_length(float32_t x, float32_t y)
{
	cout <<  "\ndistance from origin: " << std::sqrt(x*x + y*y);
}

float32_t calc_square_length(float32_t x, float32_t y)
{
	cout << "\ncalc_square_length";
	return x*x + y*y;
}

float32_t calc_length(float32_t x, float32_t y)
{
	cout << "\ncalc_length";
	return std::sqrt( calc_square_length(x,y) );
}

auto signals2_sample() -> void
{
	cout << "<Signals2 Sample>\n";

	//simplest version
	{
		cout << "\nSignals2 demo:\n";

		signal<void()> sig;

		sig.connect(hello());
		sig.connect(world());

		sig();
	}

	//the interface can also handle groups which can be seen like priorities
	{
		cout << "\n\nSignals2 demo with groups:\n";

		signal<void()> sig;

		sig.connect(1, hello());
		sig.connect(0, world());

		sig();

		//but what happens when we mix these two things?

		cout << "\n\nSignals2 demo with and without groups:\n";

		sig.connect(sspn());
		sig();

		//better control it to be sure when mixing these concepts

		cout << "\n\nSignals2 demo with and without groups second approach:\n";

		sig.connect(sspn(), boost::signals2::at_front); //or at_back

		sig();

	}

	//now let's try it with some parameters:
	{
		cout << "\n\nSignals2 demo with parameters:";

		signal<void(float32_t, float32_t)> sig;

		sig.connect(&report_position);
		sig.connect(&report_length);

		sig(3.14f, 42.f);
	}

	//if there is a return parameter we need a combiner, the default
	//combiner returns simply the vale of the last function
	{
		cout << "\n\nSignals2 demo with parameters and return value:";

		signal<float32_t(float32_t, float32_t)> sig;

		sig.connect(&calc_square_length);
		sig.connect(&calc_length);

		cout << "\nThe return value is: " << *sig(1.f, -1.f) << "\n";
	}
}
