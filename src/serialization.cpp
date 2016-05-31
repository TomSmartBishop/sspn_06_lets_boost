#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>
// needed if you want to serialize the date object
// (and there is a known boost bug that this header
// needs to be included AFTER gregorian.hpp)
#include <boost/date_time/gregorian/greg_serialize.hpp>

#include <boost/serialization/vector.hpp>

using std::cout;
using std::uint16_t;

class sspn_member {
 private:
  friend class boost::serialization::access;

  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar& full_name;
    ar& birthday;
    ar& first_timer;
    ar& num_attended_meetups;
  }

 public:
  std::string full_name;
  boost::gregorian::date birthday;  // I first tried to use std::chrono, but it
                                    // was quite disappointing
  bool first_timer;
  uint16_t num_attended_meetups;

  friend std::ostream& operator<<(std::ostream& stream, const sspn_member& m) {
    stream << m.full_name << ", born on " << m.birthday;

    if (m.first_timer)
      stream << ", never visited our meetup.";
    else
      stream << ", well known member, visited " << m.num_attended_meetups
             << " meetups.";

    return stream;
  }
};

auto serialization_sample1() -> void {
  cout << "<Serialization Sample1>\n";

  // save data to archive
  {
    // let's create a dummy member
    sspn_member member{"Hong Kildong", boost::gregorian::date(1643, 8, 23),
                       false, 3};

    std::ofstream ofs("member.x");
    boost::archive::text_oarchive oarc(ofs);
    oarc << member;
  }

  // read data from archive
  {
    sspn_member another_member;

    std::ifstream ifs("member.x");
    boost::archive::text_iarchive iarc(ifs);
    iarc >> another_member;
    // let's check the result;

    cout << "De-serialized data:\n" << another_member << "\n\n";
  }
}

class sspn {
 public:
  std::string official_name;
  boost::gregorian::date founded;
  std::vector<sspn_member> members;

  friend std::ostream& operator<<(std::ostream& stream, const sspn& s) {
    stream << s.official_name << ", founded " << s.founded << ", "
           << s.members.size() << " members:\n";

    for (const auto& m : s.members)
      stream << m << "\n";

    return stream;
  }
};

// there is also a non-intrusive way for serialization:
namespace boost {
namespace serialization {

template <class Archive>
void serialize(Archive& ar, sspn& s, const unsigned int version) {
  ar& s.official_name;
  ar& s.founded;
  ar& s.members;
}

}  // namespace serialization
}  // namespace boost

auto serialization_sample2() -> void {
  cout << "<Serialization Sample2>\n";

  // also arrays can be saved...
  {
    sspn instance{"Seoul System Programmers Network",
                  boost::gregorian::date(2016, 4, 6)};

    // the boost calender is a "proleptic Gregorian calendar", so it correctly
    // calculate dates before the gregorian calender was introduced in 1582
    instance.members.push_back(sspn_member{
        "Yi Sunshin", boost::gregorian::date(1545, 4, 28), false, 5});
    instance.members.push_back(sspn_member{
        "Hong Kildong", boost::gregorian::date(1643, 8, 23), false, 3});

    std::ofstream ofs("sspn.xb");
    boost::archive::binary_oarchive oarc(ofs);
    oarc << instance;
  }

  // read data from archive
  {
    sspn instance;

    std::ifstream ifs("sspn.xb");
    boost::archive::binary_iarchive iarc(ifs);
    iarc >> instance;
    // let's check the result;

    cout << "De-serialized data:\n" << instance << "\n\n";
  }
}

auto serialization_sample() -> void {
  serialization_sample1();
  serialization_sample2();
}
