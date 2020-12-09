#include "NFA.h"
#include "re_utils.h"
#include <vector>

NFA::NFA() : source(source_file::get_instance())
{
    construct_NFA();
}

void NFA::construct_NFA()
{
    vector<rule> rules = source->get_rules();
    for (rule r : rules)
    {
        queue<string> re_queue;
        re_utils::infix_to_postfix(r.get_pattern(), re_queue);
        //TODO: construct NFA
    }
}