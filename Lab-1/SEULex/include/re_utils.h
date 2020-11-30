#pragma once

#include <string>
#include <unordered_map>
using namespace std;

class re_utils
{
public:
    static void replace_braces(string &, const unordered_map<string, string> &);
};