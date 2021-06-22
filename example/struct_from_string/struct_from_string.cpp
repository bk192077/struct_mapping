#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

struct Color
{
	int value;

	bool operator<(const Color& o) const
	{
		return value < o.value;
	}
};

Color color_from_string(const std::string & value)
{
	if (value == "red")
	{
		return Color{1};
	}
	else if (value == "blue")
	{
		return Color{2};
	}
	
	return Color{0};
}

std::string color_to_string(const Color& color)
{
	switch (color.value)
	{
	case 1: return "red";
	case 2: return "blue";
	default: return "green";
	}
}

struct Background
{
	Color color;
};

struct Palette
{
	Color main_color;
	Background background;
	std::list<Color> special_colors;
	std::set<Color> old_colors;
	std::map<std::string, Color> new_colors;

	friend std::ostream& operator<<(std::ostream& os, const Palette& o)
	{
		os
			<< "main_color         : " << color_to_string(o.main_color) << std::endl
			<< "background.color   : " << color_to_string(o.background.color) << std::endl
			<< "special_colors     : ";

		for (const auto& color : o.special_colors)
		{
			os << color_to_string(color) << ", ";
		}

		os << std::endl << "old_colors         : ";

		for (const auto& color : o.old_colors)
		{
			os << color_to_string(color) << ", ";
		}

		os << std::endl << "new_colors         : ";

		for (const auto& [name, color] : o.new_colors)
		{
			os << "[" << name << ", " << color_to_string(color) << "], ";
		}

		os << std::endl;

		return os;
	}
};

int main()
{
	sm::MemberString<Color>::set(color_from_string, color_to_string);

	sm::reg(&Palette::main_color, "main_color", sm::Default{"red"});
	sm::reg(&Palette::background, "background", sm::Required{});
	sm::reg(&Palette::special_colors, "special_colors");
	sm::reg(&Palette::old_colors, "old_colors");
	sm::reg(&Palette::new_colors, "new_colors");

	sm::reg(&Background::color, "color");

	Palette palette;

	std::istringstream json_data(R"json(
	{
		"background": {
			"color": "blue"
		},
		"special_colors": ["red", "green", "red", "blue"],
		"old_colors": ["red", "green", "blue"],
		"new_colors": {
			"dark": "green",
			"light": "red",
			"neutral": "blue"
		}
	}
	)json");

	sm::map_json_to_struct(palette, json_data);

	std::cout << palette << std::endl;
}
