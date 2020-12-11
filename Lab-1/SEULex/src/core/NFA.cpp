#include "NFA.h"
#include "re_utils.h"
#include <vector>

NFA::NFA() : source(source_file::get_instance())
{
    construct_NFA();
}

const unordered_map<int, NFAState> &NFA::get_all_states() const
{
    return this->states;
}

const NFAState &NFA::find_state_by_id(int id) const
{
    return states.find(id)->second;
}

const rule &NFA::get_rule_by_id(int id) const
{
    return end_state.find(id)->second;
}

int NFA::is_contains_end(const unordered_set<int> &set) const
{
    for (auto t : end_state)
    {
        if (set.find(t.first) != set.end())
        {
            return t.first;
        }
    }
    return -1;
}

void NFA::find_epsilon_closure(const unordered_set<int> &core, unordered_set<int> &container)
{
    queue<int> q;
    for (auto i : core)
    {
        container.insert(i);
        q.push(i);
    }

    while (!q.empty())
    {
        int id = q.front();
        q.pop();
        unordered_set<int> _tmp;
        states.at(id).find_epsilon_edge(_tmp);
        for (auto i : _tmp)
        {
            if (container.find(i) == container.end())
            {
                container.insert(i);
                q.push(i);
            }
        }
    }
}

void NFA::can_reach(const unordered_set<int> &s, unordered_map<string, unordered_set<int>> &c)
{
    for (auto i : s)
    {
        for (auto e : states.find(i)->second.get_states_map())
        {
            if (e.first == "\\@")
                continue;
            auto f = c.find(e.first);
            if (f == c.end())
            {
                unordered_set<int> _tmp;
                _tmp.insert(e.second);
                c.insert(make_pair(e.first, _tmp));
            }
            else
                f->second.insert(e.second);
        }
    }
}

void NFA::construct_NFA()
{
    vector<int> start;
    int count = 0;
    for (rule r : source->get_rules())
    {
        queue<string> re_queue;
        re_utils::infix_to_postfix(r.get_pattern(), re_queue);
        stack<int> save;
        while (!re_queue.empty())
        {
            string tmp = re_queue.front();
            re_queue.pop();
            if (tmp == "|")
            {
                int e2 = save.top();
                save.pop();
                int s2 = save.top();
                save.pop();
                int e1 = save.top();
                save.pop();
                int s1 = save.top();
                save.pop();

                NFAState new_state1(count);
                NFAState new_state2(count + 1);
                new_state1.set_states_map("\\@", s1);
                new_state1.set_states_map("\\@", s2);
                states.find(e1)->second.set_states_map("\\@", count + 1);
                states.find(e2)->second.set_states_map("\\@", count + 1);
                states.insert(make_pair(count, new_state1));
                states.insert(make_pair(count + 1, new_state2));
                save.push(count);
                save.push(count + 1);
                count += 2;
            }
            else if (tmp == "*")
            {
                int e = save.top();
                save.pop();
                int s = save.top();
                save.pop();

                states.find(e)->second.set_states_map("\\@", s);
                NFAState new_state1(count);
                NFAState new_state2(count + 1);
                new_state1.set_states_map("\\@", count + 1);
                new_state1.set_states_map("\\@", s);
                states.find(e)->second.set_states_map("\\@", count + 1);
                states.insert(make_pair(count, new_state1));
                states.insert(make_pair(count + 1, new_state2));
                save.push(count);
                save.push(count + 1);
                count += 2;
            }
            else if (tmp == ".")
            {
                int e2 = save.top();
                save.pop();
                int s2 = save.top();
                save.pop();
                int e1 = save.top();
                save.pop();
                int s1 = save.top();
                save.pop();
                states.find(e1)->second.set_states_map("\\@", s2);
                save.push(s1);
                save.push(e2);
            }
            else
            {
                NFAState new_state1(count);
                NFAState new_state2(count + 1);
                new_state1.set_states_map(tmp, count + 1);
                states.insert(make_pair(count, new_state1));
                states.insert(make_pair(count + 1, new_state2));
                save.push(count);
                save.push(count + 1);
                count += 2;
            }
        }
        end_state.insert(make_pair(save.top(), r));
        save.pop();
        start.push_back(save.top());
    }

    int last = start[0];
    for (int i = 1; i < start.size(); i++)
    {
        int s = start[i];
        NFAState t(count);
        t.set_states_map("\\@", last);
        t.set_states_map("\\@", s);
        states.insert(make_pair(count, t));
        last = count;
        count++;
    }
    this->start_state_id = last;
}

int NFA::get_start_state_id() const
{
    return this->start_state_id;
}