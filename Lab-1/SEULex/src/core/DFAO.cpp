#include "DFAO.h"
#include "DFA.h"

DFAO::DFAO()
{
    construct_DFAO();
}

void DFAO::construct_DFAO()
{
    DFA dfa;
    //TODO: optimization dfa
}

const vector<DFAState> &DFAO::get_all_states()
{
    return this->all_states;
}
const unordered_map<int, rule> &DFAO::get_all_end_states()
{
    return this->all_end;
}