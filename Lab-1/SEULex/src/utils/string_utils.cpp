#include "string_utils.h"

/*
 * void trim(string &s)
 * 去除字符串s前后的空格和制表符
 */
void string_utils::trim(string &s)
{
    if (!s.empty())
    {
        int index = 0;
        int len = s.length();
        while (index < len)
        {
            char c = s.at(index);
            if (c != ' ' && c != '\t')
                break;
            index++;
        }

        if (index == len)
        {
            s.clear();
            return;
        }

        if (index != 0)
        {
            s.erase(0, index);
        }

        len = s.length();
        index = len - 1;
        while (index >= 0)
        {
            char c = s.at(index);
            if (c != ' ' && c != '\t')
                break;
            index--;
        }

        if (index != len - 1)
        {
            s.erase(index);
        }
    }
}

void string_utils::split(const string &s, vector<string> &tokens, const string &delimiters)
{
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}
