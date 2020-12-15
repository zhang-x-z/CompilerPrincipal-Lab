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
    int count_set = 1;
    for (auto i : dfa.get_all_end_states())
    {
        states_belong[i.first] = count_set;
        count_set++;
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

            if (dfa.get_all_states().at(first).get_all_edges().size() == 0)
            {
                for (int left = first + 1; left < states_belong.size(); left++)
                {
                    if (states_belong[left] != i)
                        continue;
                    if (dfa.get_all_states().at(left).get_all_edges().size() != 0)
                    {
                        states_belong[left] = count_set;
                        flag = true;
                    }
                }
                count_set++;
            }
            else
            {
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
            }

            if (flag)
                break;
        }
    }
    vector<int> states_state(dfa.get_all_states().size(), -1);
    vector<int> reper(count_set, -1);
    unordered_set<int> _tmp_set;
    int count = 0;
    for (int i = 0; i < states_belong.size(); i++)
    {
        if (_tmp_set.find(states_belong[i]) == _tmp_set.end())
        {
            _tmp_set.insert(states_belong[i]);
            states_state[i] = count;
            reper[states_belong[i]] = i;
            count++;
        }
        if (_tmp_set.size() == count_set)
            break;
    }

    for (int i = 0; i < dfa.get_all_states().size(); i++)
    {
        if (states_state[i] == -1)
            continue;
        DFAState _tmp_state(states_state[i]);
        for (auto edge : dfa.get_all_states().at(i).get_all_edges())
        {
            int des = states_state[reper[states_belong[edge.second]]];
            _tmp_state.set_edges(edge.first, des);
        }
        all_states.push_back(_tmp_state);
    }

    for (auto i : dfa.get_all_end_states())
    {
        int set_index = states_belong[i.first];
        all_end.insert(make_pair(states_state[reper[set_index]], i.second));
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