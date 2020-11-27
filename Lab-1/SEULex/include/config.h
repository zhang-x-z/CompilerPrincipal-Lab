#pragma once
#include <unordered_set>
#include <string>

class Config
{
public:
    static Config *getInstance();
    int get_buffer_size();

private:
    Config();
    static int buffer_size;
    static Config *config;
};