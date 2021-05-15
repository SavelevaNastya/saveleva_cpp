#pragma once
#include <type_traits>
#include <string>
#include <vector>

template< typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
T stringTo(std::string const& data)
{
	return std::atoll(data.c_str());
}
template< typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
T stringTo(std::string const& data)
{
	return std::atof(data.c_str());
}
template< typename T, typename std::enable_if<std::is_convertible<T, std::string>::value>::type* = nullptr>
T stringTo(std::string const& data)
{
	return std::string(data);
}