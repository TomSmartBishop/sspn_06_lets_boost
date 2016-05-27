#include <cstdint>
#include <iostream>
#include <vector>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/system.hpp>

using std::cout;
using std::uint32_t;

namespace bc = boost::compute;

auto compute_sample() -> void {
  cout << "<Compute Sample1>\n";

  // access the compute hardware
  auto device = bc::system::default_device();

  // print the device's name
  cout << "Found " << device.name()
       << " as default device\n\nLet's see what else we got...\n";

  uint32_t max_freq = 0;
  for (auto dev : bc::system::devices()) {
    cout << dev.name() << ":\n\t\t" << dev.clock_frequency() / 1000.0f << " GHz, "
         << dev.compute_units() << " units, driver: " << dev.driver_version() << "\n";
    if (dev.name().find("GeForce") != std::string::npos) {
      device = dev;
    }
  }

  cout << "\nLet's better use " << device.name()
       << "\n"; // of course this could just output the same again
}
