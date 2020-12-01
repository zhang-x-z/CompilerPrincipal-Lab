#pragma once
#include <string>
using namespace std;

#define UTF8 1
#define ASCII 1
#define UNICODE 2

class Config
{
public:
    static Config *get_instance();
    int get_buffer_size();
    static void delete_instance();
    const string &get_source_file_loaction();
    int get_encoding();
    int get_charset();

private:
    Config();
    int buffer_size;
    int encoding;
    int charset;
    static Config *config;
    string source_file_location;
};