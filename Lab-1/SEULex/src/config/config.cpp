#include "config.h"
#include <fstream>
#include <string>
#include <stdexcept>

int Config::buffer_size = 100;
Config *Config::config = new Config();

Config::Config()
{
    std::ifstream in("config.properties");
    if (!in)
    {
        throw std::runtime_error("Can not find configuration file config.properties.");
    }
    std::string line;
    std::string delim = "=";
    while (getline(in, line))
    {
        int index = line.find('=');
        if (index == line.npos)
            throw std::runtime_error("In config.properties: line: " + line + " Must hava '='");
        std::string options = line.substr(0, index);
        std::string value = line.substr(index + 1);
        if (value.length() == 0)
            throw std::runtime_error("In config.properties: line: " + line + " Property must has a value!");

        if (options == "buffer_size")
        {
            buffer_size = std::atoi(value.c_str());
        }
        //TODO: maybe have more config options
        else
        {
            throw std::runtime_error("In config.properties: Property: " + options + " is not allowed.");
        }
    }
    getline(in, line);
}

Config *Config::getInstance()
{
    return config;
}

int Config::get_buffer_size()
{
    return this->buffer_size;
}