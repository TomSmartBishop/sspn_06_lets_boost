#include <cstdint>
#include <iostream>
#include <vector>

#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/system.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include "float32.h"

using std::cout;
using std::uint32_t;
using std::int32_t;
using fp::float32_t;

//helper to print vectors via streams, thanks to
//http://stackoverflow.com/questions/10750057/how-to-print-out-the-contents-of-a-vector
template <typename T>
std::ostream& operator<< (std::ostream& o, const std::vector<T>& v) {
	if (!v.empty())
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(o, " "));
	return o;
}

namespace bc = boost::compute;

auto compute_sample1() -> void {
  cout << "<Compute Sample1>\n";

  // access the compute hardware
  auto device = bc::system::default_device();

  // print the device's name
  cout << "Found " << device.name()
       << " as default device\n\nLet's see what else we got...\n";

  for (auto dev : bc::system::devices()) {
    cout << dev.name() << ":\n\t\t" << dev.clock_frequency() / 1000.0f << " GHz, "
         << dev.compute_units() << " units, driver: " << dev.driver_version() << "\n";
    if (dev.name().find("GeForce") != std::string::npos) {
      device = dev;
    }
  }

  cout << "\nLet's use " << device.name()
       << "\n"; // of course this could just output the same again

  bc::context context(device);
  bc::command_queue queue(context, device);
}



// this example demonstrates how to sort a vector of ints on the GPU
auto compute_sample2() -> void {

	cout << "<Compute Sample2>\n";

	boost::random::mt19937 gen;
	boost::random::uniform_int_distribution<> dist(-99, 99);

	// create vector of random values on the host
	std::vector<int32_t> host_vec(100);
	std::generate(host_vec.begin(), host_vec.end(), [&dist, &gen] { return dist(gen); });

	// print out input vector
	cout << "input: " << host_vec << "\n";

	// transfer the values to the device (default device, we do not specify anything)
	bc::vector<int32_t> dev_vec = host_vec;

	// sort the values on the device
	bc::sort(dev_vec.begin(), dev_vec.end());

	// transfer the values back to the host
	bc::copy(dev_vec.begin(), dev_vec.end(), host_vec.begin());

	// print out the sorted vector
	cout << "\noutput: " << host_vec << "\n\n";
}

//let calculate the square root
auto compute_sample3() -> void {

  cout << "<Compute Sample3>\n";

  // get default device and setup context
  bc::device device = bc::system::default_device();
  bc::context context(device);
  bc::command_queue queue(context, device);

  boost::random::mt19937 gen;
  boost::random::uniform_real_distribution<> dist(0.0001f, 999.0f);

  // create vector of random values on the host
  std::vector<float32_t> host_vec(100);
  std::generate(host_vec.begin(), host_vec.end(),
                [&dist, &gen] { return dist(gen); });

  // create a vector on the device (we can also specify the context)
  bc::vector<float32_t> dev_vec(host_vec.size(), context);

  // print out input vector
  cout << "input: " << host_vec << "\n";

  // transfer data from the host to the device (here we also specify the queue)
  bc::copy(host_vec.begin(), host_vec.end(), dev_vec.begin(), queue);

  // calculate the square-root of each element in-place
  bc::transform(dev_vec.begin(), dev_vec.end(), dev_vec.begin(),
                bc::sqrt<float>(), queue);

  // copy values back to the host
  bc::copy(dev_vec.begin(), dev_vec.end(), host_vec.begin(), queue);

  // print out output vector
  cout << "\noutput: " << host_vec << "\n";

}

auto compute_sample() -> void {
	compute_sample1();
	compute_sample2();
	compute_sample3();
}
