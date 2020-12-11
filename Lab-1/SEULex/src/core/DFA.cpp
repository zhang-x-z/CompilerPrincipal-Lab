#include "DFA.h"
#include <unordered_set>
#include <queue>

DFA::DFA()
{
    construct_DFA();
}

int DFA::is_same_core(const unordered_multimap<int, unordered_set<int>> &c, const unordered_set<int> &s)
{
    for (auto t : c)
    {
        if (t.second == s)
            return t.first;
    }
    return -1;
}

void DFA::construct_DFA()
{
    NFA nfa;
    queue<int> states_queue;

    unordered_multimap<int, unordered_set<int>> cores;
    unordered_set<int> first_core;
    first_core.insert(0);
    cores.insert(make_pair(0, first_core));

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
        int id = states_queue.front();
        states_queue.pop();
        unordered_multimap<string, int> reaches;
        unordered_set<string> edges;
        nfa.can_reach(states.at(id).get_NFA_states(), reaches, edges);
        for (string e : edges)
        {
            unordered_set<int> states_set;
            auto _tmp = reaches.find(e);
            for (int i = 0; i < reaches.count(e); i++, _tmp++)
                states_set.insert(_tmp->second);
            
        }
    }
}