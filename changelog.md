# Change Log
All notable changes to this project will be documented in this file. This project adheres to [Semantic Versioning](http://semver.org/).

## 0.6.0 - 2021.12.16

### Added
* as types of member-data can be used: std::set, std::unordered_set, std::multiset, std::unordered_multiset
* structures in json can be represented as strings
* options in macro
* optional fields (std::optional)
* Clang support

## 0.5.0 - 2020.07.09

### Added
* use of enumerations as member and as element of container
* option Required

### Changed
* option Default for cpp structures
* option Default for containers
* option Default for enumeration
* option NotEmpty for containers

### Fixed
* if Boundes were set for fields with the same types, then all fields used the same range.

## 0.4.0 - 2020.07.02

### Added
* check type limits on set value
* check type on set value
* option Bounds for integer and floating point
* option Default for bool, integer, floating point and string
* option NotEmpty for string
* Visual C++ 2019 and Microsoft (R) C/C++ Optimizing Compiler Version 19.26.28806 for x64 | Windows 64-bit (except tests)

### Changed
* exception messages
* internal mapping mechanics

### Fixed
* before starting mapping the states of F classes is reset
* std::string is no longer treated as array_like

### Removed
* unsigned long

## 0.3.0 - 2020.06.23

### Added
* mapping of json data to common c++ structure
* reverse mapping of common c++ structure to json data
* as types of member-data can be used:
	- std::list
	- std::vector
	- std::map
	- std::unordered_map
	- std::multimap
	- std::unordered_multimap

### Changed
* registration of data members combined with initialization made optional

## 0.2.1 - 2020.06.16

### Changed
* changes to build examples on Windows
* documentation changed

### Removed
* remove macro MANAGED_STRUCT_NAME

## 0.2.0 - 2020.06.14

### Added
* reverse mapping of c++ structure on json data

## 0.1.0 - 2020.06.10

Initial. Mapping data in json format on a c++ structure.
