#include "utf8_string_iterator.h"
#include <stdexcept>

bool utf8_string_iterator::has_next()
{
    return curr_index < s.length();
}

void utf8_string_iterator::set_current_pos(int p)
{
    curr_index = p;
}

int utf8_string_iterator::get_current_pos()
{
    return curr_index - 1;
}

void utf8_string_iterator::set_string(const string &s)
{
    this->s = s;
    curr_index = 0;
}

const string utf8_string_iterator::next()
{
    if (!has_next())
        throw runtime_error("Reach the end. Can not get next character.");
    int res = judge();
    if (res == -1)
        throw runtime_error("Parser UTF-8 Error. Please check your input file encoding.");
    string a = "";
    for (int i = 0; i < res && curr_index < s.length(); i++)
    {
        a += s.at(curr_index);
        curr_index++;
    }
    return a;
}

int utf8_string_iterator::judge()
{
    unsigned char b1 = 0b10000000;
    unsigned char b2 = 0b11100000;
    unsigned char b3 = 0b11110000;
    unsigned char b4 = 0b11111000;

    char c = s.at(curr_index);
    unsigned char res = c & b1;
    int ans = -1;
    if (res == 0)
        ans = 1;
    res = c & b2;
    if (res == 0b11000000)
        ans = 2;
    res = c & b3;
    if (res == 0b11100000)
        ans = 3;
    res = c & b4;
    if (res == 0b11110000)
        ans = 4;
    return ans;
}
