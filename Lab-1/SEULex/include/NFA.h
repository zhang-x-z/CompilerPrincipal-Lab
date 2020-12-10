#pragma once
#include <unordered_map>
#include <map>
#include "source_file.h"
#include "NFAState.h"
#include "rule.h"
using namespace std;

class NFA
{
public:
    NFA();
    int get_start_state_id();
    const rule &get_rule_by_id(int) const;
    const NFAState &find_state_by_id(int) const;

private:
    void construct_NFA();
    source_file *source;
    map<int, rule> end_state;
    int start_state_id;
    unordered_map<int, NFAState> states;
};
