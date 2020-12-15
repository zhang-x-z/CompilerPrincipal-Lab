#pragma once
#include <unordered_map>
#include <vector>
#include "DFAState.h"
#include "rule.h"

class DFAO
{
public:
    DFAO();
    const vector<DFAState> &get_all_states();
    const unordered_map<int, rule> &get_all_end_states();
    int get_start_id() const;

private:
    void construct_DFAO();
    int start;
    vector<DFAState> all_states;
    unordered_map<int, rule> all_end;
};