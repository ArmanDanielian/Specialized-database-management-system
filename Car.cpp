#include "Car.h"
#include <iostream>

Car::Car()
{
    this->mark =  '\0';
    this->power = '\0';
    this->color = '\0';
}

Car::Car(const std::string mark, const std::string power, const std::string color)
{
    this->mark = mark;
    this->power = power;
    this->color = color;
}

void Car::set_mark(std::string mark)
{
    this->mark = mark;
}
void Car::set_power(std::string power)
{
    this->power = power;
}
void Car::set_color(std::string color)
{
    this->color = color;
}

const char* Car::get_mark(void)
{
    return this->mark.data();
}
const char* Car::get_power(void)
{
    return this->power.data();
}
const char* Car::get_color(void)
{
    return this->color.data();
}

void Car::print_cars_content(void)
{
    std::cout << "Car:{" << mark << "," << power << "," << color << "}" << std::endl;
}



Car::~Car()
{

}
