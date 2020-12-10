#include "NFA.h"
#include "re_utils.h"
#include <vector>

NFA::NFA() : source(source_file::get_instance())
{
    construct_NFA();
}

void NFA::construct_NFA()
{
    int count = 0;
    vector<rule> rules = source->get_rules();
    for (rule r : rules)
    {
        queue<string> re_queue;
        re_utils::infix_to_postfix(r.get_pattern(), re_queue);
        //TODO: construct NFA
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
        //TODO: finish one rule
    }
}