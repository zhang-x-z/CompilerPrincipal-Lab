#include <vector>
#include <unordered_map>
#include "DFAState.h"
#include "rule.h"
#include "NFA.h"
using namespace std;

class DFA
{
public:
    DFA();

private:
    void construct_DFA();
    int is_same_core(const unordered_multimap<int, unordered_set<int>> &, const unordered_set<int> &);
    int is_same_state(const unordered_set<int> &);
    unordered_map<int, rule> end_states;
    vector<DFAState> states;
};
