#include "NFAState.h"

NFAState::NFAState(int id) : id(id){};

NFAState::NFAState(const NFAState &s)
{
    this->id = s.id;
    for (auto t : s.states_map)
    {
        this->states_map.insert(make_pair(t.first, t.second));
    }
}

int NFAState::get_id() const
{
    return id;
}

void NFAState::set_states_map(const string &edge, int id)
{
    states_map.insert(make_pair(edge, id));
}

const unordered_multimap<string, int> &NFAState::get_states_map() const
{
    return states_map;
}

void NFAState::find_epsilon_edge(unordered_set<int> &set) const
{
    find_state_by_edge("\\@", set);
}

void NFAState::find_state_by_edge(const string &edge, unordered_set<int> &set) const
{
    int len = states_map.count(edge);
    auto beg = states_map.find(edge);
    for (int i = 0; i < len; i++, beg++)
    {
        set.insert(beg->second);
    }
}