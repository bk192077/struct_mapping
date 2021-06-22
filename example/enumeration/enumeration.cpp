#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

enum class Color
{
	red,
	blue,
	green,
};

Color ColorFromString(const std::string& value)
{
	if (value == "red")
	{
		return Color::red;
	}
	else if (value == "blue")
	{
		return Color::blue;
	}
	
	return Color::green;
}

std::string ColorToString(Color color)
{
	switch (color)
	{
	case Color::red: return "red";
	case Color::green: return "green";
	default: return "blue";
	}
}

struct Palette
{
	Color main_color;
	Color background_color;
	std::list<Color> special_colors;
	std::map<std::string, Color> colors;

	friend std::ostream& operator<<(std::ostream& os, const Palette& o)
	{
		os
			<< "main_color       : " << ColorToString(o.main_color) << std::endl
			<< "background_color : " << ColorToString(o.background_color) << std::endl
			<< "special_colors   : ";

		for (const auto& color : o.special_colors)
		{
			os << ColorToString(color) << ", ";
		}

		os << std::endl << "colors           : ";

		for (const auto& [name, color] : o.colors)
		{
			os << "[" << name << ", " << ColorToString(color) << "], ";
		}

		os << std::endl;

		return os;
	}
};

int main()
{
	sm::MemberString<Color>::set(ColorFromString, ColorToString);

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
