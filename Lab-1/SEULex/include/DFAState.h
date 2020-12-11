#pragma once
#include <unordered_set>
#include <unordered_map>
using namespace std;

class DFAState
{
public:
    DFAState(int);
    DFAState(const DFAState &);
    void set_edges(const string &, int);
    void set_NFAStates(int);
    void set_NFAStates(const unordered_set<int> &);
    int get_id() const;
    unordered_set<int> &get_NFA_states();
    const unordered_map<string, int> &get_all_edges() const;
    int find_DFAState_by_edge(const string &);

private:
    int id;
    unordered_set<int> NFAStates;
    unordered_map<string, int> edges;
};
