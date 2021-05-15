#pragma once
#include <iostream>
#include <vector>
#include <sstream>

#include "stringTo.h"
#include "iterator.h"

class csv_settings
{
public:

	csv_settings() :
		m_delimiter(','),
		m_new_line('\n'),
		m_escaping('"')
	{
	}

	bool set_delimiter(char n)
	{
		if (n == m_new_line || n == m_escaping)
			return false;

		m_delimiter = n;
		return true;
	}

	bool set_escaping_symbol(char n)
	{
		if (n == m_delimiter || n == m_new_line)
			return false;

		m_escaping = n;
		return true;
	}
	char const delimiter() const
	{
		return m_delimiter;
	}
	char const escaping_symbol() const
	{
		return m_escaping;
	}
	char const new_line_symbol() const
	{
		return m_new_line;
	}

private:
	char m_delimiter;
	char m_new_line;
	char m_escaping;
};

template<typename... Args>
class csv_parser
{
public:
	using iterator = csv_parser_iterator<Args...>;
public:
	csv_parser(std::ifstream& file_obj, int64_t num_skip_rows, csv_settings settings = csv_settings()) :
		in(file_obj),
		m_settings(settings)
	{
		if (!file_obj)
			throw std::runtime_error("File not open");

		std::string buff;
		for (; num_skip_rows > 0; --num_skip_rows)
		{
			static const int max_line = 65536;
			in.ignore(max_line, settings.new_line_symbol());
		}
	}
	~csv_parser()
	{
		in.close();
	}

	iterator begin()
	{
		in.seekg(in.beg);
		return iterator(in, m_settings);
	}
	iterator end()
	{
		return iterator(in, m_settings, true);
	}
	void reset()
	{
		in.seekg(in.beg);
	}

private:
	std::ifstream& in;
	csv_settings m_settings;
};
template<typename Tuple, size_t... I>
void print_tuple(std::ostream& out, Tuple const& tuple, std::index_sequence<I...>)
{
	((out << (I == 0 ? "":" ") << std::get<I>(tuple)), ...);
}
template<typename...Args>
std::ostream& operator<<(std::ostream& out, std::tuple<Args...> const& tuple)
{
	print_tuple(out, tuple, std::make_index_sequence<sizeof...(Args)>{});
	return out;
}