#pragma once

#include <string>
#include <unordered_map>
#include "string_iterator.h"
#include "charset.h"
#include <stack>
#include <queue>
using namespace std;

class re_utils
{
public:
    static void replace_braces(string &, const unordered_map<string, string> &);
    static void replace_brackets(string &);
    static void replace_plus_question_and_check_parentheses(string &);
    static void handle_dot(string &);
    static void add_dot(string &);
    static string espace_basic_symbol(const string &);
    static bool is_basic_symbol(const string &);
    static void construct_stack(const string &, stack<string> &);
    static void construct_queue(const string &, queue<string> &);

private:
    static string_iterator *get_string_iterator();
    static charset *get_charset();
    static string handle_bracket_espace(const string &);
};