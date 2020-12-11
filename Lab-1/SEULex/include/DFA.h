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
    unordered_map<int, rule> end_states;
    vector<DFAState> states;
};
