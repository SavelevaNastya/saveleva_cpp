#include <iostream>
#include "csv_parser.h"

int main()
{
	try
	{
		
		std::ifstream file("test.txt");
		csv_settings settings;
		settings.set_delimiter(', ');
		settings.set_escaping_symbol('"');
		csv_parser<int, std::string, double> parser(file, 0, settings);
		for (std::tuple<int, std::string, double> rs : parser)
		{
			std::cout << rs << std::endl;
		}
	}
	catch (std::runtime_error const& e)
	{
		std::cout << e.what();
	}
	catch (...)
	{
		std::cout << "Undefin error";
	}

	return 0;
}
