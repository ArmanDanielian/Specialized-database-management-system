#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	this->type = '\0';
	this->capacity = '\0';
	this->manufacturer = '\0';
}

Engine::Engine(const std::string type, const float capacity, const std::string manufacturer)
{
	this->type = type;
	this->capacity = capacity;
	this->manufacturer = manufacturer;
}

void Engine::set_type(std::string type)
{
	this->type = type;
}

void Engine::set_manufacturer(std::string manufacturer)
{
	this->manufacturer = manufacturer;
}

void Engine::set_capacity(std::string capacity)
{
	this->capacity = capacity;
}

const char* Engine::get_type()
{
	return this->type.data();
}

const char* Engine::get_manufacturer()
{
	return this->manufacturer.data();
}

const char* Engine::get_capacity(void)
{
	return this->capacity.data();
}

void Engine::print_engines_content(void)
{
	std::cout << "Engine:{" << type << "," << capacity << "," << manufacturer << "}" << std::endl;
}


Engine::~Engine()
{

}
