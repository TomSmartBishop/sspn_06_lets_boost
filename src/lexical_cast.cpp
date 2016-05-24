#include <cstdint>
#include <iostream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>

using std::cout;
using std::int32_t;
using boost::lexical_cast;
using boost::bad_lexical_cast;

auto lexical_cast_sample() -> void {
  cout << "<Lexical Cast Sample>\n";

  try {
    int32_t i = lexical_cast<int32_t>("3");
    cout << "Converted to std::int32_t: " << i << "\n";

    int32_t j = lexical_cast<int32_t>("3.14");
    cout << "Converted to std::int32_t: " << j << "\n";
  } catch (const bad_lexical_cast &blc) {
    // not good
    cout << "lexical_cast failed (from " << blc.source_type().name() << " to "
         << blc.target_type().name() << ")\n";
  }

  // if you don't like exceptions...
  int32_t x;
  if (boost::conversion::try_lexical_convert("42", x)) {
    cout << "Converted to std::int32_t: " << x << "\n";
  } else {
    cout << "Failed to convert \"42\""
         << "\n";
  }

  // also the other way around is quite convenient:
  std::string str("Num: ");

  // mhhh can it throw an exception in this case..?
  str += lexical_cast<std::string>(42); 
  str += 42;
  cout << "From to std::string: " << str << "\n";
}
