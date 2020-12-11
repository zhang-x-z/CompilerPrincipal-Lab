#include "DFAState.h"

DFAState::DFAState(int id) : id(id) {}

DFAState::DFAState(const DFAState &d)
{
    this->id = d.id;
    for (auto i : d.edges)
    {
        this->edges.insert(i);
    }

    for (auto i : d.NFAStates)
    {
        this->NFAStates.insert(i);
    }
}

unordered_set<int> &DFAState::get_NFA_states()
{
    return this->NFAStates;
}

void DFAState::set_edges(const string &s, int id)
{
    this->edges.insert(make_pair(s, id));
}

void DFAState::set_NFAStates(int id)
{
    this->NFAStates.insert(id);
}

void DFAState::set_NFAStates(const unordered_set<int> &s)
{
    for (auto i : s)
    {
        NFAStates.insert(i);
    }
}

int DFAState::find_DFAState_by_edge(const string &e)
{
    return this->edges.find(e)->second;
}

int DFAState::get_id() const
{
    return id;
}
