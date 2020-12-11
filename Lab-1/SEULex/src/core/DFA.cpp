#include "DFA.h"
#include <unordered_set>
#include <queue>

DFA::DFA()
{
    construct_DFA();
}

const vector<DFAState> &DFA::get_all_states() const
{
    return this->states;
}

const unordered_map<int, rule> &DFA::get_all_end_states() const
{
    return this->end_states;
}

const vector<int> &DFA::get_useful_states_id() const
{
    return this->useful_id;
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

int DFA::is_same_state(const unordered_set<int> &set)
{
    for (auto s : states)
    {
        if (s.get_NFA_states() == set)
        {
            return s.get_id();
        }
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

    unordered_set<int> _tmp_first_set;
    _tmp_first_set.insert(nfa.get_start_state_id());
    nfa.find_epsilon_closure(_tmp_first_set, first.get_NFA_states());

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
        unordered_map<string, unordered_set<int>> reaches;
        nfa.can_reach(states[id].get_NFA_states(), reaches);
        for (auto edge : reaches)
        {
            int flag = is_same_core(cores, edge.second);
            if (flag != -1)
                states[id].set_edges(edge.first, flag);
            else
            {
                unordered_set<int> closure;
                nfa.find_epsilon_closure(edge.second, closure);
                int _tmp_id = is_same_state(closure);
                if (_tmp_id == -1)
                {
                    DFAState _tmp_state(count);
                    _tmp_state.set_NFAStates(closure);
                    end_id = nfa.is_contains_end(closure);
                    if (end_id != -1)
                    {
                        end_states.insert(make_pair(count, nfa.get_rule_by_id(end_id)));
                    }
                    states.push_back(_tmp_state);
                    states_queue.push(count);
                    cores.insert(make_pair(count, edge.second));
                    states[id].set_edges(edge.first, count);
                    count++;
                }
                else
                {
                    states[id].set_edges(edge.first, _tmp_id);
                    cores.insert(make_pair(_tmp_id, edge.second));
                }
            }
        }
    }
}

//TODO: optimize DFA
void DFA::optimization_DFA()
{
    for (int i = 0; i < states.size(); i++)
    {
        useful_id.push_back(i);
    }
}