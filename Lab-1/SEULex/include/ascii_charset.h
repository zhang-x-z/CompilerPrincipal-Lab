#pragma once
#include "charset.h"

class ascii_charset : public charset
{
public:
    void complementary_set(unordered_set<string> &);
    void universe_set(unordered_set<string> &);
};