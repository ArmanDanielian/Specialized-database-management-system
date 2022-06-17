// DateBase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Car.h"
#include "Engine.h"
#include <sstream>
#include <string>
#include <fstream>


void tokenize(std::string const& src, const std::string delim, std::string* dest)
{
    size_t start = 0;
    size_t end;
    size_t delim_len = delim.length();
    size_t i = 0;
    while ((end = src.find(delim, start)) != std::string::npos) {
        dest[i].assign(src.substr(start, end - start));
        start = end + delim_len;
        i++;
    }
    dest[i].assign(src.substr(start, end - start));
}

void save_data(Car* src1, Engine* src2, unsigned cars_len, unsigned engines_len)
{
    FILE* file = fopen("db.txt", "w");
    for (unsigned i = 0; i < cars_len; i++) {
        if (*(src1[i].get_mark()) != 0x00)
        {
            fprintf(file, "Car:{");
            fprintf(file, src1[i].get_mark());
            fprintf(file, ",");
            fprintf(file, src1[i].get_power());
            fprintf(file, ",");
            fprintf(file, src1[i].get_color());
            fprintf(file, "}\n");
        }
    }
    for (unsigned i = 0; i < engines_len; i++) {
        if (*(src2[i].get_type()) != 0x00)
        {
            fprintf(file, "Engine:{");
            fprintf(file, src2[i].get_type());
            fprintf(file, ",");
            fprintf(file, src2[i].get_capacity());
            fprintf(file, ",");
            fprintf(file, src2[i].get_manufacturer());
            fprintf(file, "}\n");
        }
    }

    fclose(file);
}

void createData(std::string dataType) {
    std::string splittedData[5];
    std::string temp;
    if (dataType == "Car") {       
        Car newCar;

        std::cout << "Enter mark: " << std::endl;
        getline(std::cin, temp);
        newCar.set_mark(temp);
        std::cout << "Enter power: " << std::endl;
        getline(std::cin, temp);
        newCar.set_power(temp);
        std::cout << "Enter color: " << std::endl;
        getline(std::cin, temp);
        newCar.set_color(temp);

        FILE* file = fopen("db.txt", "a");
        fprintf(file,"Car:{");
        fprintf(file, newCar.get_mark());
        fprintf(file, ",");
        fprintf(file, newCar.get_power());
        fprintf(file, ",");
        fprintf(file, newCar.get_color());
        fprintf(file, "}\n");
        fclose(file);
    }
    else if (dataType == "Engine") {
        Engine newEngine;
        std::cout << "Enter type: " << std::endl;
        getline(std::cin, temp);
        newEngine.set_type(temp);
        std::cout << "Enter capacity: " << std::endl;
        getline(std::cin, temp);
        newEngine.set_capacity(temp);
        std::cout << "Enter manufacturer: " << std::endl;
        getline(std::cin, temp);
        newEngine.set_manufacturer(temp);
        FILE* file = fopen("db.txt", "a");
        fprintf(file, "Engine:{");
        fprintf(file, newEngine.get_type());
        fprintf(file, ",");
        fprintf(file, newEngine.get_capacity());
        fprintf(file, ",");
        fprintf(file, newEngine.get_manufacturer());
        fprintf(file, "}\n");
        fclose(file);
    }
    
}

const unsigned  get_file_lines_counter(std::string dataType)
{
    std::fstream file;
    std::string temp;
    int lines_count = 0;
    file.open("db.txt", std::ios::in);
    if (file.is_open())
    {
        if (dataType == "Car") {
            while (getline(file, temp)) {
                if (temp.find("Car") != std::string::npos) 
                    lines_count++;
            }
        }
        else if (dataType == "Engine") {
            while (getline(file, temp)) {
                if (temp.find("Engine") != std::string::npos) 
                    lines_count++;
            }               
        }
        file.close();
        return lines_count;
    }
}


void read_file(Car* newCar, Engine* newEngine)
{
    std::fstream file;
    file.open("db.txt", std::ios::in);
    if (file.is_open())
    {
        std::string temp;
        char class_content[100];
        int i = 0;
        int j = 0;
        size_t start;
        size_t end;
        while (getline(file, temp))
        {
            if (temp.find("Car") != std::string::npos) {
                std::string cars[3];
                start = temp.find_first_of("{");
                end = temp.find_last_of("}");
                temp.copy(class_content, end - start - 1, start + 1);
                class_content[end - start - 1] = '\0';
                tokenize(class_content, ",", cars);
                newCar[i].set_mark(cars[0]);
                newCar[i].set_power(cars[1]);
                newCar[i].set_color(cars[2]);
                i++;
            }
            else if (temp.find("Engine") != std::string::npos) {
                std::string engine[3];
                start = temp.find_first_of("{");
                end = temp.find_last_of("}");
                temp.copy(class_content, end - start - 1, start + 1);
                class_content[end - start - 1] = '\0';
                tokenize(class_content, ",", engine);
                newEngine[j].set_type(engine[0]);
                newEngine[j].set_capacity(engine[1]);
                newEngine[j].set_manufacturer(engine[2]);
                j++;
            }
        }
        file.close();
    }

}

void selectData(std::string dataType, std::string data)
{
    unsigned count_cars = get_file_lines_counter("Car");
    unsigned count_engines = get_file_lines_counter("Engine");
    Car* newCar = new Car[count_cars]; // (e.g new Car[5])
    Engine* newEngine = new Engine[count_engines];
    read_file(newCar, newEngine);

    if (dataType == "Car") {
        if (data.find('*') != std::string::npos)
        {
            for (unsigned i = 0; i < count_cars; i++) {
                newCar[i].print_cars_content();
            }
        }
        else if (data.find("!=") != std::string::npos) {
            std::string temp[2];
            tokenize(data, "!=", temp);
            if (temp[0] == "mark") {
                for (unsigned i = 0; i < count_cars; i++) {
                    if (temp[1] != newCar[i].get_mark()) {
                        newCar[i].print_cars_content();
                    }
                }
            }
            else if (temp[0] == "power") {
                for (unsigned i = 0; i < count_cars; i++) {
                    if (temp[1] != newCar[i].get_power()){
                        newCar[i].print_cars_content();
                    }
                }
            }
            else if (temp[0] == "color") {
                for (unsigned i = 0; i < count_cars; i++) {
                    if (temp[1] != newCar[i].get_color()){
                        newCar[i].print_cars_content();
                    }
                }
            }

        }
        else if (data.find('=') != std::string::npos) {
            std::string temp[2];
            tokenize(data, "=", temp);
            if (temp[0] == "mark") {
                for (unsigned i = 0; i < count_cars; i++) {
                    if (temp[1] == newCar[i].get_mark()){
                        newCar[i].print_cars_content();
                    }
                }
            }
            if (temp[0] == "power") {
                for (unsigned i = 0; i < count_cars; i++) {
                    if (temp[1] == newCar[i].get_power()){
                        newCar[i].print_cars_content();
                    }
                }
            }
            if (temp[0] == "color") {
                for (unsigned i = 0; i < count_cars; i++) {
                    if (temp[1] == newCar[i].get_color()){
                        newCar[i].print_cars_content();
                    }
                }
            }
        }

    }

    else if (dataType == "Engine")
    {
        if (data.find('*') != std::string::npos)
        {
            for (unsigned i = 0; i < count_engines; i++) {
                newEngine[i].print_engines_content();
            }
        }
        else if (data.find("!=") != std::string::npos) {
            std::string temp[2];
            tokenize(data, "!=", temp);
            if (temp[0] == "type") {
                for (unsigned i = 0; i < count_engines; i++) {
                    if (temp[1] != newEngine[i].get_type()) {
                        newEngine[i].print_engines_content();
                    }
                }
            }
            else if (temp[0] == "capacity") {
                for (unsigned i = 0; i < count_engines; i++) {
                    if (temp[1] != newEngine[i].get_capacity()) {
                        newEngine[i].print_engines_content();
                    }
                }
            }
            else if (temp[0] == "manufacturer") {
                for (unsigned i = 0; i < count_engines; i++) {
                    if (temp[1] != newEngine[i].get_manufacturer()) {
                        newEngine[i].print_engines_content();
                    }
                }
            }
        }
        else if (data.find('=') != std::string::npos) {
            std::string temp[2];
            tokenize(data, "=", temp);
            if (temp[0] == "type") {
                for (unsigned i = 0; i < count_engines; i++) {
                    if (temp[1] == newEngine[i].get_type()) {
                        newEngine[i].print_engines_content();
                    }
                }
            }
            if (temp[0] == "capacity") {
                for (unsigned i = 0; i < count_engines; i++) {
                    if (temp[1] == newEngine[i].get_capacity()) {
                        newEngine[i].print_engines_content();
                    }
                }
            }
            if (temp[0] == "manufacturer") {
                for (unsigned i = 0; i < count_engines; i++) {
                    if (temp[1] == newEngine[i].get_manufacturer()) {
                        newEngine[i].print_engines_content();
                    }
                }
            }
        }

    }
       
     delete[] newCar;
     delete[] newEngine;

}


void deleteData(std::string dataType, std::string data)
{
    unsigned count_cars = get_file_lines_counter("Car");
    unsigned count_engines = get_file_lines_counter("Engine");
    Car* newCar = new Car[count_cars];
    Engine* newEngine= new Engine[count_engines];
    read_file(newCar, newEngine);

    if (dataType == "Car") {
        if (data.find('*') != std::string::npos)
        {
            for (unsigned i = 0; i < count_cars; i++) {
                newCar[i].set_mark("\0");
                newCar[i].set_power("\0");
                newCar[i].set_color("\0");
            }
        }
        else if (data.find("!=") != std::string::npos) {
            std::string temp[2];
            tokenize(data, "!=", temp);
            for (unsigned i = 0; i < count_cars; i++) {
                if ((temp[0] == "mark" && temp[1] != newCar[i].get_mark()) || \
                    (temp[0] == "power" && temp[1] != newCar[i].get_power()) || \
                    (temp[0] == "color" && temp[1] != newCar[i].get_color())) {
                    newCar[i].set_mark("\0");
                    newCar[i].set_power("\0");
                    newCar[i].set_color("\0");
                }                      
            }      
        }
        else if (data.find('=') != std::string::npos) {
            std::string temp[2];
            tokenize(data, "=", temp);
            for (unsigned i = 0; i < count_cars; i++) {
                if ((temp[0] == "mark" && temp[1] == newCar[i].get_mark()) || \
                    (temp[0] == "power" && temp[1] == newCar[i].get_power()) || \
                    (temp[0] == "color" && temp[1] == newCar[i].get_color())) {
                    newCar[i].set_mark("\0");
                    newCar[i].set_power("\0");
                    newCar[i].set_color("\0");
                }
            }         
        }

        
    }
    else if (dataType == "Engine") {
        if (data.find('*') != std::string::npos)
        {
            for (unsigned i = 0; i < count_engines; i++) {
                newEngine[i].set_type("\0");
                newEngine[i].set_capacity("\0");
                newEngine[i].set_manufacturer("\0");
            }
           
        }
        else if (data.find("!=") != std::string::npos) {
            std::string temp[2];
            tokenize(data, "!=", temp);

            for (unsigned i = 0; i < count_engines; i++) {
                if ((temp[0] == "type" && temp[1] != newEngine[i].get_type()) || \
                    (temp[0] == "capacity" && temp[1] != newEngine[i].get_capacity()) || \
                    (temp[0] == "manufacturer" && temp[1] != newEngine[i].get_manufacturer())) {
                    newEngine[i].set_type("\0");
                    newEngine[i].set_capacity("\0");
                    newEngine[i].set_manufacturer("\0");
                }
            }
            
        }
        else if (data.find('=') != std::string::npos) {
            std::string temp[2];
            tokenize(data, "=", temp);
            for (unsigned i = 0; i < count_engines; i++) {
                if ((temp[0] == "type" && temp[1] == newEngine[i].get_type()) || \
                    (temp[0] == "capacity" && temp[1] == newEngine[i].get_capacity()) || \
                    (temp[0] == "manufacturer" && temp[1] == newEngine[i].get_manufacturer())) {
                    newEngine[i].set_type("\0");
                    newEngine[i].set_capacity("\0");
                    newEngine[i].set_manufacturer("\0");
                }
            }
        }
    }
    save_data(newCar, newEngine, count_cars, count_engines);
    delete[] newCar;
    delete[] newEngine;
}


void query(std::string queryTokens[]) {

    if (queryTokens[0] == "ADD") {
        createData(queryTokens[1]);
    }
    else if (queryTokens[0] == "SELECT") {  // SELECT CAR WHERE color=red
        selectData(queryTokens[1], queryTokens[3]);
    }
    else if (queryTokens[0] == "DELETE") {
        deleteData(queryTokens[1], queryTokens[3]);
    }
    else {
        std::cout << "Enter Correct Command ! " << std::endl;
        std::cout << "**************HELP**************" << std::endl;
        std::cout << "ADD \'object' " << std::endl;
        std::cout << "SELECT \'object' WHERE \'args\' " << std::endl;
        std::cout << "DELETE \'object' WHERE \'args\' " << std::endl;
        std::cout << "**************END***************" << std::endl;
    }
}


int main()
{
    std::string userQuerry;
    std::cout << "**************HELP**************" << std::endl;
    std::cout << "ADD \'object' " << std::endl;
    std::cout << "SELECT \'object' WHERE \'args\' " << std::endl;
    std::cout << "DELETE \'object' WHERE \'args\' " << std::endl;
    std::cout << "**************END***************" << std::endl;
    while (userQuerry != "exit")
    {
        std::cout << "Enter Command" << std::endl;
        getline(std::cin, userQuerry);

        std::string splittedQuerry[10];
        tokenize(userQuerry, " ", splittedQuerry);

        query(splittedQuerry);
    }

       
    
    return 0;
}

