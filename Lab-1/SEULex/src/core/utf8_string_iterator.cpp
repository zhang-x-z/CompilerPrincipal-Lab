#include "utf8_string_iterator.h"

void utf8_string_iterator::set_string(const string &s)
{
    this->s = s;
    curr_index = 0;
}

const string utf8_string_iterator::next()
{
    int res = judge();
    string a = "";
    for (int i = 0; i < res; i++)
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
    if (res == 0)
        return 1;
    res = c & b2;
    if (res == 0b11000000)
        return 2;
    res = c & b3;
    if (res == 0b11100000)
        return 3;
    res = c & b4;
    if (res == 0b11110000)
        return 4;
}
