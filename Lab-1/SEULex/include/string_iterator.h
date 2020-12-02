#pragma once
#include <string>
using namespace std;

class string_iterator
{
public:
    virtual const string next() = 0;
    virtual bool has_next() = 0;
    virtual void set_string(const string &) = 0;
    virtual void set_current_pos(int) = 0;
    virtual int get_current_pos() = 0;
};