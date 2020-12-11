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
    int get_start_state_id() const;
    int is_contains_end(const unordered_set<int> &) const;
    void can_reach(const unordered_set<int> &, unordered_multimap<string, int> &, unordered_set<string> &);
    const rule &get_rule_by_id(int) const;
    const NFAState &find_state_by_id(int) const;
    const unordered_map<int, NFAState> &get_all_states() const;

private:
    void construct_NFA();
    source_file *source;
    map<int, rule> end_state;
    int start_state_id;
    unordered_map<int, NFAState> states;
};