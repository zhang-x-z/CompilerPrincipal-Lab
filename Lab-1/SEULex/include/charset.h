#pragma once
#include <unordered_set>
#include <string>
using namespace std;

class charset
{
public:
    virtual void complementary_set(unordered_set<string> &) = 0;
    virtual void universe_set(unordered_set<string> &) = 0;
    virtual ~charset(){}
};