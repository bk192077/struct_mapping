#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

#include "struct_mapping/struct_mapping.h"

struct Library
{
	std::unordered_map<
		std::string,
		std::multimap<std::string, int>> counters;

	std::multimap<
		std::string,
		std::unordered_multimap<std::string, std::string>> books;
};

int main()
{
	struct_mapping::reg(&Library::counters, "counters");
	struct_mapping::reg(&Library::books, "books");

	Library library;

	std::istringstream json_data(R"json(
	{
		"counters": {
			"first": {
				"112": 13,
				"142": 560,
				"112": 0
			},
			"second": {
				"2": 28,
				"20": 411
			},
			"third": {
			}
		},
		"books": {
			"asd": {
				"Leo": "aaa",
				"Leo": "bbb",
				"Mark": "ccc"
			},
			"wwert": {
				"Gogol": "ddd",
				"Tom": "eee"
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(library, json_data);

	std::cout << "library:" << std::endl;

	std::cout << " counters :" << std::endl;

	for (const auto& [n1, v] : library.counters)
	{
		std::cout << "  " << n1 << " : ";
		for (const auto& [n2, c] : v)
		{
			std::cout << "[" << n2 << ", " << c << "], ";
		}
		std::cout << std::endl;
	}

	std::cout << " books :" << std::endl;
	for (const auto& [n1, v] : library.books)
	{
		std::cout << "  " << n1 << " : ";
		for (const auto& [n2, b] : v)
		{
			std::cout << "[" << n2 << ", " << b << "], ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}
