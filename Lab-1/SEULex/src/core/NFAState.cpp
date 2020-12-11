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
    auto all = states_map.find(edge);
    while (all != states_map.end())
    {
        set.insert(all->second);
    }
}