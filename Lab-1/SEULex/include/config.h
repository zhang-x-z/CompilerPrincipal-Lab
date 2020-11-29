#pragma once
#include <string>
using namespace std;

class Config
{
public:
    static Config *get_instance();
    int get_buffer_size();
    static void delete_instance();
    const string &get_source_file_loaction();

private:
    Config();
    int buffer_size;
    static Config *config;
    string source_file_location;
};