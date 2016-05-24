#include <cstdint>
#include <iostream>
#include <vector>

#include <boost/variant.hpp>

using std::cout;
using std::vector;
using std::int32_t;

auto variant_sample() -> void {
  cout << "<Variant Sample>\n";

  vector<boost::variant<std::string, int32_t>> variant_vec;
  variant_vec.reserve(6);

  variant_vec.push_back(42);
  variant_vec.push_back("Hello");
  variant_vec.push_back("World");
  variant_vec.push_back(std::string("A std::string"));
  variant_vec.push_back(3.14f); // it does not prevent implicit conversion
  variant_vec.push_back('c');   // T.T

  for (const auto &val : variant_vec) {
    cout << val << "\n";
  }

  for (const auto &val : variant_vec) {
    if (const int *pi = boost::get<int>(&val))
      cout << "std::int32_t " << *pi << "\n";
    else if (const std::string *pstr = boost::get<std::string>(&val))
      cout << "std::string " << *pstr << "\n";
  }
}
