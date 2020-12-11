#include "DFA.h"
#include <unordered_set>
#include <queue>

DFA::DFA()
{
    construct_DFA();
}

void DFA::construct_DFA()
{
    NFA nfa;
    queue<int> states_queue;
    int count = 1;
    DFAState first(0);
    states_queue.push(0);
    nfa.find_state_by_id(nfa.get_start_state_id()).find_epsilon_edge(first.get_NFA_states());
    int end_id = nfa.is_contains_end(first.get_NFA_states());
    if (end_id != -1)
    {
        end_states.insert(make_pair(0, nfa.get_rule_by_id(end_id)));
    }
    states.push_back(first);
    while (!states_queue.empty())
    {
    }
}