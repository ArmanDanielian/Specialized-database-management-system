#pragma once

#include <string>

class Car
{
private:
	std::string mark;
	std::string power;
	std::string color;

public:
	Car();
	Car(const std::string mark, const std::string power, const std::string color);
	void set_mark(std::string mark);
	void set_power(std::string power);
	void set_color (std::string color);
	const char* get_mark(void);
	const char* get_power(void);
	const char* get_color(void);
	void print_cars_content(void);
	~Car();
};

