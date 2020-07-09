#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

enum class Color {
	red,
	blue,
	green,
};

Color color_from_string(const std::string & value) {
	if (value == "red") return Color::red;
	if (value == "blue") return Color::blue;
	
	return Color::green;
}

std::string color_to_string(Color color) {
	switch (color) {
	case Color::red: return "red";
	case Color::green: return "green";
	default: return "blue";
	}
}

struct Palette {
	Color main_color;
	Color background_color;
	std::list<Color> special_colors;
	std::map<std::string, Color> colors;

	friend std::ostream & operator<<(std::ostream & os, const Palette & o) {
		os << "main_color       : " << color_to_string(o.main_color) << std::endl;
		os << "background_color : " << color_to_string(o.background_color) << std::endl;
		os << "special_colors   : ";
		for (auto color : o.special_colors) os << color_to_string(color) << ", ";
		os << std::endl << "colors           : ";
		for (auto [name, color] : o.colors) os << "[" << name << ", " << color_to_string(color) << "], ";
		os << std::endl;

		return os;
	}
};

int main() {
	sm::MemberString<Color>::set(color_from_string, color_to_string);

	sm::reg(&Palette::main_color, "main_color", sm::Required{});
	sm::reg(&Palette::background_color, "background_color", sm::Default{Color::blue});
	sm::reg(&Palette::special_colors, "special_colors");
	sm::reg(&Palette::colors, "colors");

	Palette palette;

	std::istringstream json_data(R"json(
	{
		"main_color": "green",
		"special_colors": ["green", "green", "red"],
		"colors": {
			"dark": "green",
			"light": "red",
			"neutral": "blue"
		}
	}
	)json");

	sm::map_json_to_struct(palette, json_data);

	std::cout << palette << std::endl;
}
