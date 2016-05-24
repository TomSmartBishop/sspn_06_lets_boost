#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include <boost/signals2.hpp>

#include "float32.h"

using std::cout;
using std::vector;
using std::int32_t;
using fp::float32_t;

using boost::signals2::signal;

struct hello {
  auto operator()() -> void const { cout << "Hello "; }
};

struct world {
  auto operator()() -> void const { cout << "World!"; }
};

auto signals2_sample1() -> void {
  cout << "<Signals2 Sample1>\n";

  // simplest version

  signal<void()> sig;

  // add slots (boost terminology)
  sig.connect(hello());
  auto con =
      sig.connect(world()); // there is an optional return value (connection)

  sig();

  // we can temporarily block slots (via the connection)
  {
    boost::signals2::shared_connection_block block(con); // block the slot
    sig();
  }

  sig(); // so here it is working again as before

  // or disconnect all slots (or a specific slot)...
  sig.disconnect_all_slots();
  sig();
}

struct sspn {
  auto operator()() -> void const { cout << "...and hello SSPN!"; }
};

auto signals2_sample2() -> void {
  // the interface can also handle groups which can be seen like priorities

  cout << "\n\n<Signals2 Sample2 with groups>\n";

  signal<void()> sig;

  sig.connect(1, hello());
  sig.connect(0, world());

  sig();

  // but what happens when we mix these two things?

  cout << "\n\n<Signals2 Sample2 with and without groups>\n";

  sig.connect(sspn());
  sig();

  // better control it to be sure when mixing these concepts

  cout << "\n\n<Signals2 Sample2 with and without groups second approach>\n";

  sig.connect(sspn(), boost::signals2::at_front); // or at_back

  sig();
}

auto report_position(float32_t x, float32_t y) -> void {
  cout << "\n@position x: " << x << " y: " << y;
}

auto report_length(float32_t x, float32_t y) -> void {
  cout << "\ndistance from origin: " << std::sqrt(x * x + y * y);
}

auto signals2_sample3() -> void {
  // now let's try it with some parameters:
  cout << "\n\n<Signals2 Sample3 with parameters>";

  signal<void(float32_t, float32_t)> sig;

  sig.connect(&report_position);
  sig.connect(&report_length);

  sig(3.14f, 42.f);
}

auto calc_square_length(float32_t x, float32_t y) -> float32_t {
  cout << "\ncalc_square_length";
  return x * x + y * y;
}

auto calc_length(float32_t x, float32_t y) -> float32_t {
  cout << "\ncalc_length";
  return std::sqrt(calc_square_length(x, y));
}

template <typename ty> struct maximum {
  using result_type = ty; // this is needed by boost, name must be 'result_type'

  template <typename iter> auto operator()(iter first, iter last) -> ty const {
    // in case there there is noting (no slot) connected to the signal
    if (first == last)
      return ty();

    return *std::max_element(first, last);
  }
};

auto signals2_sample4() -> void {
  // if there is a return parameter we need a combiner, the default
  // combiner returns simply the vale of the last function
  cout << "\n\n<Signals2 Sample4 with parameters and return value>";

  signal<float32_t(float32_t, float32_t)> sig;
  signal<float32_t(float32_t, float32_t), maximum<float32_t>> sig2;

  sig.connect(&calc_square_length);
  sig.connect(&calc_length);

  cout << "\nThe return value of sig is: " << *sig(1.f, -1.f) << "\n";

  sig2.connect(&calc_square_length);
  sig2.connect(&calc_length);

  // notice the difference in the return value!
  cout << "\nThe return value of sig2 is: " << sig2(1.f, -1.f) << "\n";

  // so you can also create a combiner with a vector return value collecting all
  // outputs
}

auto signals2_sample5() -> void {
  // we can also disconnect slots
  cout << "\n\n<Signals2 Sample5 disconnect slots>";

  signal<float32_t(float32_t, float32_t)> sig;

  sig.connect(&calc_square_length);
  sig.connect(&calc_length);
}

// just run all samples
auto signals2_sample() -> void {
  signals2_sample1();
  signals2_sample2();
  signals2_sample3();
  signals2_sample4();
  signals2_sample5();
}