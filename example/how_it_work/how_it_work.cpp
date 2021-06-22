#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

struct Student
{
	std::string name;
	int age;
};

struct Library
{
	int book_count;
};

struct School
{
	bool college;
	Library library;
	std::list<Student> students;
};

struct City
{
	std::string name;
	std::map<std::string, School> schools;
};

int main()
{
	struct_mapping::reg(&Student::name, "name");
	struct_mapping::reg(&Student::age, "age");

	struct_mapping::reg(&Library::book_count, "book_count");

	struct_mapping::reg(&School::college, "college");
	struct_mapping::reg(&School::library, "library");
	struct_mapping::reg(&School::students, "students");

	struct_mapping::reg(&City::name, "name");
	struct_mapping::reg(&City::schools, "schools");


	std::istringstream json_data(R"json(
	{
		"name": "Saratov",
		"schools": {
			"15": {
				"college": false,
				"library": {
					"book_count": 1562
				},
				"students": [
					{
						"name": "Griffin",
						"age": 42
					},
					{
						"name": "Agent K",
						"age": 29
					}
				]
			},
			"42": {
				"college": true,
				"library": {
					"book_count": 27305
				},
				"students": [
					{
						"name": "Agent O",
						"age": 78
					},
					{
						"name": "Boris",
						"age": 256
					}
				]
			}
		}
	}
	)json");

	City city;

	struct_mapping::map_json_to_struct(city, json_data);

	std::cout << "name :" << city.name << std::endl;

	std::cout << "schools :" << std::endl;

	for (const auto& [ name, school ] : city.schools)
	{
		std::cout << std::endl
			<< " name    : " << name << std::endl
			<< " college : " << std::boolalpha << school.college << std::endl
			<< " library : " << std::endl
			<< "  book_count : " << school.library.book_count << std::endl
			<< " students : " << std::endl;

		for (const auto& student : school.students)
		{
			std::cout << "  [ " << student.name << ", " << student.age << " ]" << std::endl;
		}
	}

	std::cout << std::endl;
}
