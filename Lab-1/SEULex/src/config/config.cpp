#include "config.h"
#include <fstream>
#include <stdexcept>

Config *Config::config = new Config();

Config::Config()
{
    ifstream in("config.properties");
    if (!in)
    {
        throw runtime_error("Can not find configuration file config.properties.");
    }
    string line;
    string delim = "=";
    while (getline(in, line))
    {
        int index = line.find('=');
        if (index == line.npos)
            throw runtime_error("In config.properties: line: " + line + " Must hava '='");
        string options = line.substr(0, index);
        string value = line.substr(index + 1);
        if (value.length() == 0)
            throw runtime_error("In config.properties: line: " + line + " Property must has a value!");

        if (options == "buffer_size")
        {
            buffer_size = atoi(value.c_str());
        }
        else if (options == "source_file_location")
        {
            source_file_location = value;
        }
        else if (options == "encoding")
        {
            if (value == "utf8" || value == "UTF8" || value == "UTF-8" || value == "utf-8")
                encoding = UTF8;
            //TODO: add more encodingS
            else
                throw runtime_error("In config.properties: Line: " + line + "\nEncoding: " + value + " is not supported.");
        }
        else if (options == "charset")
        {
            if (value == "unicode" || value == "Unicode" || value == "UNICODE")
                charset = UNICODE;
            else if (value == "ascii" || value == "Ascii" || value == "ASCII")
                charset = ASCII;
            //TODO: add more charset
            else
                throw runtime_error("In config.properties: Line: " + line + "\nCharset: " + value + " is not supported.");
        }
        //TODO: maybe have more config options
        else
        {
            throw runtime_error("In config.properties: Property: " + options + " is not allowed.");
        }
    }
    getline(in, line);
}

Config *Config::get_instance()
{
    return config;
}

int Config::get_buffer_size()
{
    return this->buffer_size;
}

const string &Config::get_source_file_loaction()
{
    return this->source_file_location;
}

int Config::get_encoding()
{
    return encoding;
}

int Config::get_charset()
{
    return charset;
}

void Config::delete_instance()
{
    delete config;
}