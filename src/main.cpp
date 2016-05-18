//get generated constans from cmake
#include "generated/config.h"

#include <cstddef> //for std::size_t
#include <cstdint> //for std::int32_t and co
#include <iostream> //for std::cout
#include <string> //for std::string
#include <vector> //for std::vector

#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp> //only needed when doing more customizations

//basic stuff to get started
#include "base.h"
#include "float32.h"


//since C++11 we have better control over integer types..!
using std::size_t;
using std::int32_t;
using fp::float32_t;
using std::cout;
using std::vector;
using std::string;

namespace po = boost::program_options;

//our samples
auto any_sample() -> void;
auto lexical_cast_sample() -> void;

auto main(int argc, char * argv[]) -> int //the C++ standard defines that the return type of main has to be int
{
	//speedup cout
	std::cout.sync_with_stdio(false);
	
	int32_t int_val;
	
	//let's define our options
	po::options_description desc("lets_boost\nusage");
	desc.add_options()
		("help,h",
		 "Display this help message.")

		("display,d",	po::value<int32_t>(&int_val)->value_name("NUMBER")/*->default_value(1)*/,
		 "Display a number.")

		("sample,s",	po::value<vector<string>>()->multitoken()->value_name("SAMPLE"),
		 "Run one or more of the following boost samples:\n"
		 "lexical_cast, signals2, sort, any")
	;

	if (argc == 1)
	{
		cout << "<No options specified>\n" << desc << "\n"; //don't use endl (it's really slow)
		return 0;
	}

	//let boost process the command line arguments
	po::variables_map vm;
	auto optional_style = po::command_line_style::unix_style;
	
	//easy way:
	//po::store(po::parse_command_line(argc, argv, desc, optional_style), vm);
	//more customized:
	po::store(po::command_line_parser(argc, argv).options(desc).style(optional_style).allow_unregistered().run(), vm);
	po::notify(vm);

	//display the composed help message
	if (vm.count("help")) {
		cout << desc << "\n"; 
		return 0;
	}

	if (vm.count("display-int")) {
		cout << "You set the number to "  << int_val << ".\n";
	}

	if(vm.count("sample"))
		for (const auto& sample : vm["sample"].as<vector<string>>())
		{
			if (sample == "any")
				any_sample();
			else if (sample == "lexical_cast")
				lexical_cast_sample();
		}


	return 0;
}