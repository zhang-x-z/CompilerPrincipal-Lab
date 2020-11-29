#pragma once

#include <string>
#include <vector>
using namespace std;

class rule
{
public:
    rule(const rule &);
    rule(const string &, const vector<string> &);
    const string &get_pattern();
    const vector<string> &get_actions();

private:
    string pattern;
    vector<string> actions;
};