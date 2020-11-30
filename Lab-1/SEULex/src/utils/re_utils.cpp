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
        res += re.substr(start, index);
        char c = re.at(index - 1);
        if (index == 0 || re.at(index - 1) != '\\')
        {
            string name = "";
            bool finded = false;
            bool is_espace = false;
            for (int i = index + 1; i < re.length(); i++)
            {
                char c = re.at(i);
                if (c == '\\' && !is_espace)
                    is_espace = true;
                else
                {
                    if (c == '}')
                    {
                        if (is_espace)
                            is_espace = false;
                        else
                        {
                            start = i + 1;
                            finded = true;
                            break;
                        }
                    }
                    if (c == '\\')
                        is_espace = false;
                    name += c;
                }
            }

            if (!finded)
                throw runtime_error("Unclosed brace.");
            if (map.find(name) == map.end())
                throw runtime_error(name + " in {} not found.");
            res += "(" + (map.at(name)) + ")";
        }
        else
        {
            res += '{';
            start = index + 1;
        }
        index = re.find_first_of('{', start);
    }
    res += re.substr(start);
    re = res;
}