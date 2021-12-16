#include "struct_mapping/struct_mapping.h"

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

namespace sm = struct_mapping;

struct Color
{
	int value;

	bool operator<(const Color& o) const
	{
		return value < o.value;
	}
};

static Color color_from_string(const std::string & value)
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

static std::string color_to_string(const Color& color)
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

	std::ostringstream out_json_data;
	struct_mapping::map_struct_to_json(palette, out_json_data, "  ");

	std::cout << out_json_data.str() << std::endl;
}
