#ifndef __FLOAT32_H_
#define __FLOAT32_H_

namespace fp 
{
	//unfortunately there is no std::float32 or similar in the C++ standard yet...
	static_assert(std::numeric_limits<float>::is_iec559, "The float of this platform does not conform with the IEC559 standard");
	static_assert(std::numeric_limits<float>::digits == 24, "We expect 32 bit floats, therefore 24 digits");

	//at this point we know our float type a bit better and we can define it a bit better:
	using float32_t = float;
	//since C++11 we can use alias names instead of creating new types with typedef,
	//which provides easier syntax and can be used with templates
							 
	//some (micro controller) platforms already define a float32_t so 
	//always keep you things in namespaces

};

#endif //__FLOAT32_H_
