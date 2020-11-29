#include "rule.h"

rule::rule(const string &s, const vector<string> &v)
{
    pattern = s;
    for (auto l : v)
    {
        actions.push_back(l);
    }
}

rule::rule(const rule &r)
{
    this->pattern = r.pattern;
    for (auto v : r.actions)
    {
        this->actions.push_back(v);
    }
}

const string &rule::get_pattern()
{
    return pattern;
}

const vector<string> &rule::get_actions()
{
    return actions;
}