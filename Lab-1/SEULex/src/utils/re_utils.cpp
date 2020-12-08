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
                            if (is_not)
                            {
                                charset *_set = get_charset();
                                _set->complementary_set(char_set);
                                delete _set;
                            }
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
    delete it;
    re = res;
}

void re_utils::replace_plus_question_and_check_parentheses(string &re)
{
    stack<string> search;
    stack<string> save;
    construct_stack(re, search);

    int parentheses_count = 0;

    while (!search.empty())
    {
        string tmp = search.top();
        search.pop();
        if (tmp == "?" || tmp == "+")
        {
            if (search.empty())
                throw runtime_error("Bad statement with " + tmp + " (Can not be the first symbol)");
            string _c = search.top();
            search.pop();
            if (!is_basic_symbol(_c) && _c != "+" && _c != "?")
            {
                save.push(")");
                if (tmp == "?")
                {
                    save.push(_c);
                    save.push("|");
                    save.push("\\@");
                }
                else
                {
                    save.push("*");
                    save.push(_c);
                    save.push(_c);
                }
                save.push("(");
            }
            else if (_c == ")")
            {
                int _count = 1;
                stack<string> _tmp_stack;
                bool finded = false;
                _tmp_stack.push(")");
                while (!search.empty())
                {
                    string _tmp = search.top();
                    search.pop();
                    if (_tmp == ")")
                        _count++;
                    else if (_tmp == "(")
                        _count--;
                    _tmp_stack.push(_tmp);
                    if (_count == 0)
                    {
                        finded = true;
                        break;
                    }
                }

                if (!finded)
                    throw runtime_error("')' doesn't have matched '('");
                if (tmp == "?")
                {
                    search.push("(");
                    search.push("\\@");
                    search.push("|");
                    while (!_tmp_stack.empty())
                    {
                        search.push(_tmp_stack.top());
                        _tmp_stack.pop();
                    }
                    search.push(")");
                }
                else
                {
                    stack<string> _tmp_stack2(_tmp_stack);
                    search.push("(");
                    while (!_tmp_stack2.empty())
                    {
                        search.push(_tmp_stack2.top());
                        _tmp_stack2.pop();
                    }

                    while (!_tmp_stack.empty())
                    {
                        search.push(_tmp_stack.top());
                        _tmp_stack.pop();
                    }

                    search.push("*");
                    search.push(")");
                }
            }
            else
                throw runtime_error("Bad statement with " + tmp + " (The character before " + tmp + " can not be " + _c + ")");
        }
        else
        {
            if (tmp == ")")
                parentheses_count++;
            else if (tmp == "(")
                parentheses_count--;
            save.push(tmp);
        }
        if (parentheses_count < 0)
            throw runtime_error("'(' doesn't have matched ')'");
    }

    if (parentheses_count > 0)
        throw runtime_error("')' doesn't have matched '('.");
    re.clear();
    while (!save.empty())
    {
        re.append(save.top());
        save.pop();
    }
}

void re_utils::handle_dot(string &re)
{
    int start = 0;
    int index = re.find_first_of('.', start);
    string res;
    while (index != re.npos)
    {
        res += re.substr(start, index - start);
        if (index == 0 || re.at(index - 1) != '\\')
        {
            res += "(";
            charset *_set = get_charset();
            unordered_set<string> set;
            _set->universe_set(set);
            delete _set;
            for (auto c : set)
            {
                res += c;
                res += "|";
            }
            res.erase(res.length() - 1);
            res += ")";
        }
        else
            res += ".";
        start = index + 1;
        index = re.find_first_of('.', start);
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

//(, ) *, |
bool re_utils::is_basic_symbol(const string &c)
{
    return (c == "(" || c == ")" || c == "*" || c == "|");
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

void re_utils::construct_stack(const string &re, stack<string> &s)
{
    string_iterator *it = get_string_iterator();
    it->set_string(re);
    it->set_current_pos(0);
    while (it->has_next())
    {
        string c = it->next();
        if (c != "\\")
            s.push(c);
        else
        {
            if (!it->has_next())
                throw runtime_error("No more character after \\");
            c += it->next();
            s.push(c);
        }
    }
    delete it;
}

void re_utils::construct_queue(const string &re, queue<string> &s)
{
    string_iterator *it = get_string_iterator();
    it->set_string(re);
    it->set_current_pos(0);
    while (it->has_next())
    {
        string c = it->next();
        if (c != "\\")
            s.push(c);
        else
        {
            if (!it->has_next())
                throw runtime_error("No more character after \\.");
            c += it->next();
            s.push(c);
        }
    }
    delete it;
}

void re_utils::infix_to_postfix(const string &re, queue<string> &a)
{
    
}