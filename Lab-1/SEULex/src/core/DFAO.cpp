#include "DFAO.h"
#include "DFA.h"

DFAO::DFAO()
{
    construct_DFAO();
}

void DFAO::construct_DFAO()
{
    DFA dfa;
    vector<unordered_set<int>> set_map;
    vector<int> states_belong(dfa.get_all_states().size());
    set_map.push_back(unordered_set<int>{});
    int set_num = 1;
    for (auto i : dfa.get_all_states())
    {
        if (dfa.get_all_end_states().find(i.get_id()) == dfa.get_all_end_states().end())
        {
            states_belong[i.get_id()] = 0;
            set_map[0].insert(i.get_id());
        }
        else
        {
            set_map.push_back(unordered_set<int>{i.get_id()});
            states_belong[i.get_id()] = set_num;
            set_num++;
        }
    }

    // all the states are end state
    if (set_map[0].size() == 0)
    {
        for (auto i : dfa.get_all_states())
        {
            DFAState _tmp(i.get_id());
            for (auto e : i.get_all_edges())
            {
                _tmp.set_edges(e.first, e.second);
            }
            all_states.push_back(_tmp);
        }

        for (auto i : dfa.get_all_end_states())
        {
            all_end.insert(i);
        }
        return;
    }

    bool flag = true;
    while (flag)
    {
        flag = false;
        //pick one set
        unordered_set<int> new_set;
        int splited = -1;
        for (int set_index = 0; set_index < set_num; set_index++)
        {
            //this set doesn't have element or has only one element
            if (set_map[set_index].size() <= 1)
                continue;
            //pick one state in this set
            unordered_set<int>::iterator stand_id = set_map[set_index].begin();
            const DFAState *stand = &dfa.get_all_states().at(*stand_id);
            // this state doesn't have any edge
            if (stand->get_all_edges().size() == 0)
            {
                unordered_set<int>::iterator find = set_map[set_index].begin();
                find++;
                while (find != set_map[set_index].end())
                {
                    if (dfa.get_all_states().at(*find).get_all_edges().size() != 0)
                    {
                        new_set.insert(*find);
                        flag = true;
                    }
                    find++;
                }
            }
            else
            {
                for (auto edge : stand->get_all_edges())
                {
                    unordered_set<int>::iterator it = set_map[set_index].begin();
                    it++;
                    while (it != set_map[set_index].end())
                    {
                        const DFAState *_tmp = &dfa.get_all_states().at(*it);
                        if (_tmp->get_all_edges().find(edge.first) == _tmp->get_all_edges().end() || states_belong[_tmp->get_all_edges().find(edge.first)->second] != states_belong[edge.second])
                        {
                            new_set.insert(*it);
                            flag = true;
                        }
                        it++;
                    }
                    if (flag)
                        break;
                }
            }
            if (flag)
            {
                splited = set_index;
                break;
            }
        }

        if (flag)
        {
            for (const auto &i : new_set)
            {
                set_map[splited].erase(i);
                states_belong[i] = set_num;
            }
            set_map.push_back(new_set);
            set_num++;
        }
    }

    this->start = states_belong[0];
    for (int i = 0; i < set_map.size(); i++)
    {
        DFAState _tmp(i);
        const DFAState *e = &dfa.get_all_states().at(*set_map[i].begin());
        for (const auto &edge : e->get_all_edges())
        {
            _tmp.set_edges(edge.first, states_belong[edge.second]);
        }
        all_states.push_back(_tmp);
    }

    for (const auto &i : dfa.get_all_end_states())
    {
        all_end.insert(make_pair(states_belong[i.first], i.second));
    }
}

int DFAO::get_start_id() const
{
    return this->start;
}

const vector<DFAState> &DFAO::get_all_states()
{
    return this->all_states;
}
const unordered_map<int, rule> &DFAO::get_all_end_states()
{
    return this->all_end;
}