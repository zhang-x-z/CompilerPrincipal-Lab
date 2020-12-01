#pragma once
#include <string>
using namespace std;


class string_iterator
{
public:
    virtual const string next() = 0;
    virtual void set_string(const string&) = 0;
};