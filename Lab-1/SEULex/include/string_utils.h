#pragma once
#include <string>
#include <vector>
using namespace std;

class string_utils
{
public:
    static void trim(string &s);
    static void split(const string &s, vector<string> &tokens, const string &delimiters = " ");
    static string change_to_printable_string(const string &);
};