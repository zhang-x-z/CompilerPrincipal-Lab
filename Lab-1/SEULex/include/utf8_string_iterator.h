#pragma once
#include "string_iterator.h"

class utf8_string_iterator : public string_iterator
{
public:
    const string next();
    void set_string(const string &s);

private:
    int judge();
    int curr_index;
    string s;
};