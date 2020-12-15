#include "DFAO.h"
#include "DFA.h"

DFAO::DFAO()
{
    construct_DFAO();
}

void DFAO::construct_DFAO()
{
    DFA dfa;
    vector<int> states_belong(dfa.get_all_states().size(), 0);
    int count_set = 2;
    for (auto i : dfa.get_all_end_states())
    {
        states_belong[i.first] = 1;
    }
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (int i = 0; i < count_set; i++)
        {
            int first = -1;
            for (int j = 0; j < states_belong.size(); j++)
            {
                if (states_belong[j] != i)
                    continue;
                first = j;
                break;
            }
            for (auto edge : dfa.get_all_states().at(first).get_all_edges())
            {
                for (int left = first + 1; left < states_belong.size(); left++)
                {
                    if (states_belong[left] != i)
                        continue;
                    const DFAState *cur = &dfa.get_all_states().at(left);
                    auto find = cur->get_all_edges().find(edge.first);
                    if ((find == cur->get_all_edges().end()) || (states_belong[edge.second] != states_belong[find->second]))
                    {
                        states_belong[left] = count_set;
                        flag = true;
                    }
                }
                if (flag)
                {
                    count_set++;
                    break;
                }
            }
            if (flag)
                break;
        }
    }
}

const vector<DFAState> &DFAO::get_all_states()
{
    return this->all_states;
}
const unordered_map<int, rule> &DFAO::get_all_end_states()
{
    return this->all_end;
}