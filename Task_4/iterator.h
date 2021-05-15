#pragma once
#include <tuple>
#include <fstream>

#include "stringTo.h"

class csv_settings;

template<typename...Args>
class csv_parser_iterator
{
public:
	csv_parser_iterator(std::ifstream& file_obj, csv_settings& settings, bool end = false):
		in(file_obj),
		m_settings(settings)
	{
		if (end)
			current_row = -1;
		else
		{
			current_row = 0;
			buff = row_parse();
		}
	}
	csv_parser_iterator& operator++()
	{
		if (column_count == -1)
			throw std::runtime_error("End iterator not changing");
		buff = row_parse();
		return *this;
	}
	csv_parser_iterator& operator++(int)
	{
		if (column_count == -1)
			throw std::runtime_error("End iterator not changing");
		buff = row_parse();
	}
	std::tuple<Args...>& operator*()
	{
		if (current_row == -1)
			throw std::runtime_error("Operator \"*\" not used for end iterator");
		return buff;
	}
	bool operator!=(csv_parser_iterator const& r)
	{
		if (&in != &(r.in))
			return true;
		return current_row != r.current_row;
	}
	operator std::tuple<Args...>&()
	{
		return buff;
	}

private:
	std::tuple<Args...> row_parse()
	{
		if (in.eof())
		{
			current_row = -1;
			return std::tuple<Args...>();
		}
		
		std::vector<std::string> data;
		std::stringstream ss;
		uint64_t column = 1;
		try
		{
			while (!in.eof())
			{
				char c = in.get();
				if (c == m_settings.delimiter())
				{
					data.push_back(ss.str());
					ss.str("");
					++column;
				}
				else if (c == m_settings.new_line_symbol())
				{
					data.push_back(ss.str());
					++current_row;
					if (data.size() == column_count)
						return make_tuple_(data);
					else
						throw std::runtime_error("Read data count not equal column count");
				}
				else if (c == m_settings.escaping_symbol())
				{
					bool close = false;
					while (!in.eof())
					{
						c = in.get();
						if (c == m_settings.escaping_symbol())
							if (in.peek() != m_settings.escaping_symbol())
							{
								close = true;
								break;
							}
							else
								in.ignore(1);

						ss << c;
					}
					if(close == false)
						throw std::runtime_error("Open symbol '\"' found, but not found closing symbol '\"'");
				}
				else
				{
					ss << c;
				}
			}
			data.push_back(ss.str());
			++current_row;
			if (data.size() == column_count)
				return make_tuple_(data);
			else
				throw std::runtime_error("read data count not equal column count");
		}
		catch (std::runtime_error const& e)
		{
			throw std::runtime_error(std::string(e.what()) + ": row " + std::to_string(current_row) + ", column " + std::to_string(column));
		}
		catch (...)
		{
			throw std::runtime_error("UNdefine error: row " + std::to_string(current_row) + ", column " + std::to_string(column));
		}

		return std::tuple<Args...>();
	}
	auto make_tuple_(std::vector<std::string> const& data)
	{
		return make_tuple_impl(data, std::make_index_sequence<sizeof...(Args)>{});
	}
	template<typename T, std::size_t... I>
	auto make_tuple_impl(T const& data, std::index_sequence<I...>)
	{
		return std::make_tuple((stringTo< Args >(data[I]))...);
	}
	friend std::ostream& operator<<(std::ostream& out, csv_parser_iterator const& data);

private:
	std::ifstream& in;
	uint64_t column_count = sizeof...(Args);
	int64_t current_row;
	csv_settings& m_settings;
	std::tuple<Args...> buff;
};
template<typename...Args>
std::ostream& operator<<(std::ostream& out, csv_parser_iterator<Args...> const& data)
{
	return (out << (static_cast<std::tuple<Args...>>(data)));
}