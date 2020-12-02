#include "re_utils.h"
#include "config.h"
#include "utf8_string_iterator.h"
#include "ascii_charset.h"
#include <unordered_set>

void re_utils::replace_braces(string &re, const unordered_map<string, string> &map)
{
    int start = 0;
    string res = "";
    int index = re.find_first_of('{', start);
    if (index == re.npos)
        return;
    while (index != re.npos)
    {
        res += re.substr(start, index - start);
        if (index == 0 || re.at(index - 1) != '\\')
        {
            string name = "";
            bool finded = false;
            for (int i = index + 1; i < re.length(); i++)
            {
                char cur = re.at(i);
                char before = re.at(i - 1);
                if (cur == '}' && before != '\\')
                {
                    start = i + 1;
                    finded = true;
                    break;
                }
                if (cur == '}')
                    name.erase(name.length() - 1);
                name += cur;
            }

            if (!finded)
                throw runtime_error("Unclosed brace.");
            if (map.find(name) == map.end())
                throw runtime_error(name + " in {} not found.");
            res += "(" + (map.at(name)) + ")";
        }
        else
        {
            res.erase(res.length() - 1);
            res += '{';
            start = index + 1;
        }
        index = re.find_first_of('{', start);
    }
    res += re.substr(start);
    re = res;
}

void re_utils::replace_brackets(string &re)
{
    int start = 0;
    string res = "";
    int index = re.find_first_of('[');
    if (index == re.npos)
        return;
    string_iterator *it = get_string_iterator();
    it->set_string(re);
    while (index != re.npos)
    {
        res += re.substr(start, index - start);
        if (index == 0 || re.at(index - 1) != '\\')
        {
            int start_pos = index + 1;
            bool is_not = false;
            if (re.at(index + 1) == '^')
            {
                is_not = true;
                start_pos++;
            }

            it->set_current_pos(start_pos);

            unordered_set<string> char_set;

            bool is_espace = false;
            bool is_finded = false;
            string last_char;
            while (it->has_next())
            {
                string c = it->next();
                if (c == "\\" && !is_espace)
                    is_espace = true;
                else
                {
                    if (is_espace)
                    {
                        is_espace = false;
                        last_char = handle_bracket_espace(c);
                        char_set.insert(last_char);
                    }
                    else
                    {
                        if (c == "-")
                        {
                            int curr_pos = it->get_current_pos();
                            if (curr_pos == index + 1)
                            {
                                char_set.insert("-");
                                last_char = "-";
                            }
                            else
                            {
                                if (!it->has_next())
                                    throw runtime_error("Unclosed bracket.");
                                string next_char = it->next();
                                if (next_char == "]")
                                {
                                    char_set.insert("-");
                                    it->set_current_pos(curr_pos + 1);
                                }
                                else
                                {
                                    if (last_char.length() != 1 || next_char.length() != 1)
                                        throw runtime_error("Bad statement with -.");
                                    char lc = last_char.at(0);
                                    char nc = next_char.at(0);
                                    if ((lc <= 'z' && lc >= 'a' && nc <= 'z' && nc >= 'a' && lc <= nc) || (lc <= 'Z' && lc >= 'A' && nc <= 'Z' && nc >= 'A' && lc <= nc) || (lc <= '9' && lc >= '0' && nc <= '9' && nc >= '0' && lc <= nc))
                                    {
                                        char _t = lc;
                                        while (_t <= nc)
                                        {
                                            _t += 1;
                                            string _tmp(1, _t);
                                            char_set.insert(_tmp);
                                            //TODO: change last char
                                            last_char = "had"; //make [a-c-f] illegel
                                        }
                                    }
                                    else
                                        throw runtime_error("Bad statement with -.");
                                }
                            }
                        }
                        else if (c == "]")
                        {
                            //TODO: end
                            is_finded = true;
                            charset *_set = get_charset();
                            if (is_not)
                                _set->complementary_set(char_set);
                            res += "(";
                            for (auto _c : char_set)
                            {
                                res += _c;
                                res += "|";
                            }
                            res.erase(res.length() - 1);
                            res += ")";
                            start = it->get_current_pos() + 1;
                            break;
                        }
                        else
                        {
                            last_char = espace_basic_symbol(c);
                            char_set.insert(last_char);
                        }
                    }
                }
            }
            if (!is_finded)
                throw runtime_error("Unclosed bracket.");
        }
        else
        {
            res.erase(res.length() - 1);
            res += '[';
            start = index + 1;
        }
        index = re.find_first_of('[', start);
    }
    res += re.substr(start);
    re = res;
}

string re_utils::handle_bracket_espace(const string &c)
{
    string ans;
    if (c == "t")
        ans = "\t";
    else if (c == "n")
        ans = "\n";
    else if (c == "f")
        ans = "\f";
    else if (c == "v")
        ans = "\v";
    else if (c == "r")
        ans = "\r";
    else if (c == "+")
        ans = "\\+";
    else if (c == "(")
        ans = "\\(";
    else if (c == "?")
        ans = "\\?";
    else if (c == "*")
        ans = "\\*";
    else if (c == ".")
        ans = "\\.";
    else if (c == "\\")
        ans = "\\\\";
    else if (c == "|")
        ans = "\\|";
    else
    {
        string tmp = espace_basic_symbol(c);
        if (tmp != c)
            ans = tmp;
        else
            ans = c;
    }
    return ans;
}

string re_utils::espace_basic_symbol(const string &c)
{
    string ans;
    if (c == "+")
        ans = "\\+";
    else if (c == "(")
        ans = "\\(";
    else if (c == ")")
        ans = "\\)";
    else if (c == "?")
        ans = "\\?";
    else if (c == "*")
        ans = "\\*";
    else if (c == ".")
        ans = "\\.";
    else if (c == "\\")
        ans = "\\\\";
    else if (c == "|")
        ans = "\\|";
    else
        ans = c;
    return ans;
}

string_iterator *re_utils::get_string_iterator()
{
    string_iterator *p = nullptr;
    if (Config::get_instance()->get_encoding() == UTF8)
        p = new utf8_string_iterator();
    return p;
}

charset *re_utils::get_charset()
{
    charset *p = nullptr;
    if (Config::get_instance()->get_charset() == ASCII)
        p = new ascii_charset();
    //TODO: add unicode charset
    //else if ()
    return p;
}