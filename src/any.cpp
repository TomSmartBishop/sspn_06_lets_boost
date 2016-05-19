#include <iostream>
#include <vector>
#include <cstdint>

#include <boost/any.hpp>

using std::cout;
using std::vector;
using std::int32_t;

auto any_sample() -> void
{
	cout << "<Any Sample>\n";

	vector<boost::any> many;
	many.reserve(6);

	many.push_back(42);
	many.push_back("Hello");
	many.push_back("World");
	many.push_back(std::string("A std::string"));
	many.push_back(3.14f);
	many.push_back('c');


	for (const auto& val : many)
	{
		if (val.type() == typeid(int32_t))
		{
			cout << "std::int32_t: " << boost::any_cast<int32_t>(val) << "\n";
		}
		else if (val.type() == typeid(const char *))
		{
			cout << "const char *: " << boost::any_cast<const char *>(val) << "\n";
		}
		else if (val.type() == typeid(std::string))
		{
			cout << "std::string: " << boost::any_cast<std::string>(val) << "\n";
		}
		else if (val.type() == typeid(char))
		{
			cout << "char: " << boost::any_cast<char>(val) << "\n";
		}
		else
		{
			cout << "oh.. something that we do not handle" << "\n";
		}
	}
}
