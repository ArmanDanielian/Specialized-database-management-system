#pragma once

#include <string>

class Engine
{
private:
	std::string type;
	std::string capacity;
	std::string manufacturer;

public:
	Engine();
	Engine(const std::string type, const float capacity, const std::string manufacturer);
	void set_type(std::string type);
	void set_capacity(std::string type);
	void set_manufacturer(std::string manufacturer);
	const char* get_type(void);
	const char* get_capacity(void);
	const char* get_manufacturer(void);
	void print_engines_content(void);
	~Engine();

};

