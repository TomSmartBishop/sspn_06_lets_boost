#include <iostream>
#include <vector>
#include <cstdint>

#include <boost/lexical_cast.hpp>
#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>

using std::cout;
using std::int32_t;
using boost::lexical_cast;
using boost::bad_lexical_cast;

auto lexical_cast_sample() -> void
{
	try
	{
		int32_t i = lexical_cast<int32_t>("3");
		cout << "Converted to int32_t: " << i << "\n";

		int32_t j = lexical_cast<int32_t>("3.14");
		cout << "Converted to int32_t: " << j << "\n";
	}
	catch (const bad_lexical_cast & blc)
	{
		//not good
		cout << "lexical_cast failed (from " << blc.source_type().name() << " to " << blc.target_type().name() << ")\n";
	}

	//if you don't like exceptions...
	int32_t x;
	if (boost::conversion::try_lexical_convert("42", x))
	{
		cout << "Converted to int32_t: " << x << "\n";
	}
	else
	{
		cout << "Failed to convert \"42\"" << "\n";
	}

}
