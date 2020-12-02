#pragma once

#include <string>
#include <unordered_map>
#include "string_iterator.h"
#include "charset.h"
using namespace std;

class re_utils
{
public:
    static void replace_braces(string &, const unordered_map<string, string> &);
    static void replace_brackets(string &);
    static string espace_basic_symbol(const string &);

private:
    static string_iterator *get_string_iterator();
    static charset *get_charset();
    static string handle_bracket_espace(const string &);
};