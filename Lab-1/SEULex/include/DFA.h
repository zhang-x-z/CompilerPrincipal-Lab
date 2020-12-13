#pragma once
#include <vector>
#include <unordered_map>
#include "DFAState.h"
#include "rule.h"
#include "NFA.h"
using namespace std;

class DFA
{
public:
    DFA();
    const vector<DFAState> &get_all_states() const;
    const unordered_map<int, rule> &get_all_end_states() const;

private:
    void construct_DFA();
    int is_same_core(const unordered_multimap<int, unordered_set<int>> &, const unordered_set<int> &);
    int is_same_state(const unordered_set<int> &);
    unordered_map<int, rule> end_states;
    vector<DFAState> states;
};
