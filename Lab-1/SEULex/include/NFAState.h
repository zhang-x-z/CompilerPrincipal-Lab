#pragma once
#include <unordered_map>
#include <unordered_set>
using namespace std;

class NFAState
{
public:
    NFAState(int);
    NFAState(const NFAState &);
    void set_states_map(const string &, int);
    const unordered_multimap<string, int> &get_states_map() const;
    void find_epsilon_edge(unordered_set<int> &) const;
    void find_state_by_edge(const string &, unordered_set<int> &) const;
    int get_id() const;

private:
    int id;
    unordered_multimap<string, int> states_map;
};