#include "re_utils.h"
#include <iostream>

void re_utils::replace_braces(string &re, const unordered_map<string, string> &map)
{
    int start = 0;
    string res = "";
    int index = re.find_first_of('{', start);
    if (index == re.npos)
        return;
    while (index != re.npos)
    {
        cout << start << " " << index << endl;
        cout << re.substr(start, index) << endl;
        res += re.substr(start, index);
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

void re_utils::replace_brackets(string & re)
{
}