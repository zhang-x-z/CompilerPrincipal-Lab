#include "re_utils.h"

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
    while (index != re.npos)
    {
        res += re.substr(start, index - start);
        if (index == 0 || re.at(index - 1) != '\\')
        {
            int count = index + 1;
            bool is_not = false;
            if (re.at(index + 1) == '^')
            {
                count++;
                is_not = true;
            }
            bool espace = false;
            bool finded = false;
            while (count < re.length())
            {
                if (re.at(count) == '\\' && !espace)
                    espace = true;
                else
                {
                    if (espace)
                    {
                                        }
                }
            }
        }
        else
        {
            res.erase(res.length() - 1);
            res += '{';
            start = index + 1;
        }
    }
}