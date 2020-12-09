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

private:
    void construct_NFA();
    source_file *source;
    map<string, rule> end_state;
    int start_state_id;
    unordered_map<int, NFAState> states;
};
