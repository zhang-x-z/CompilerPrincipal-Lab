#include "DFAState.h"

DFAState::DFAState(int id) : id(id) {}

void DFAState::set_edges(const string &s, int id)
{
    this->edges.insert(make_pair(s, id));
}

void DFAState::set_NFAStates(int id)
{
    this->NFAStates.insert(id);
}

int DFAState::find_DFAState_by_edge(const string &e)
{
    return this->edges.find(e)->second;
}

int DFAState::get_id() const
{
    return id;
}