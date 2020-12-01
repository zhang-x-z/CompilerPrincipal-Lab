#pragma once
#include "string_iterator.h"

class utf8_string_iterator : public string_iterator
{
public:
    const string next();
    void set_string(const string &s);
    bool has_next();
    void set_current_pos(int);
    int get_current_pos();

private:
    int judge();
    int curr_index;
    string s;
};