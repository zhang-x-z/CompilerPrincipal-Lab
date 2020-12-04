#include "ascii_charset.h"
#include "re_utils.h"

void ascii_charset::complementary_set(unordered_set<string> &set)
{
    unordered_set<string> tmp(set);
    set.clear();
    for (int i = 0; i < 128; i++)
    {
        string c = re_utils::espace_basic_symbol(string(1, (char)i));
        if (tmp.find(c) == tmp.end())
        {
            set.insert(c);
        }
    }
}

void ascii_charset::universe_set(unordered_set<string> &set)
{
    set.clear();
    for (int i = 0; i < 128; i++)
    {
        string c = re_utils::espace_basic_symbol(string(1, (char)i));
        set.insert(c);
    }
}