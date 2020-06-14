#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(Author)

MANAGED_FIELD(std::string, name)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(Book)

MANAGED_FIELD(int, price)
MANAGED_FIELD_STRUCT(Author, author)
MANAGED_FIELD_ARRAY(std::string, chapters)

END_MANAGED_STRUCT

int main() {
	Book white_space;

	std::istringstream json_data(R"json(
	{
		"price": 273,
		"author": {
			"name": "bk192077"
		},
		"chapters": [
			"launch",
			"new horizons"
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(white_space, json_data);

	std::cout << "Book:" << std::endl;
	std::cout << " price : " << white_space.price << std::endl;
	std::cout << " author :" << std::endl;
	std::cout << "  name : " << white_space.author.name << std::endl;
	std::cout << " chapters :" << std::endl;
	for (auto& c : white_space.chapters.get_data()) {
		std::cout << "  " << c << std::endl;
	}
	std::cout << std::endl;
}
