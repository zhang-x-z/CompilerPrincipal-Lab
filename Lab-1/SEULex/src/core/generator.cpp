#include "generator.h"
#include "config.h"
#include "string_utils.h"
#include <fstream>

void generator::append_init()
{
    string init_code = "void DFA::init()\n{\n";
    init_code.append("\tthis->start = " + to_string(dfa.get_start_id()) + ";\n");
    init_code.append("\tunordered_map<string, int> empty;\n");
    init_code.append("\tunordered_map<string, int> use;\n");
    for (auto i : dfa.get_all_states())
    {
        if (i.get_all_edges().empty())
            init_code.append("\tthis->states.push_back(empty);\n");
        else
        {
            init_code.append("\tuse.clear();\n");
            for (auto t : i.get_all_edges())
            {
                init_code.append("\tuse.insert(make_pair(\"" + string_utils::change_to_printable_string(t.first) + "\", " + to_string(t.second) + "));\n");
            }
            init_code.append("\tthis->states.push_back(use);\n");
        }
    }
    for (auto t : dfa.get_all_end_states())
    {
        init_code.append("\tthis->end_states.insert(" + to_string(t.first) + ");\n");
    }
    init_code.append("}\n");
    code.append(init_code);
}

void generator::append_end_action()
{
    string end_code = "";
    const string sign = "void end";
    for (auto i : dfa.get_all_end_states())
    {
        end_code.append(sign + to_string(i.first) + "()\n{\n");
        for (auto r : i.second.get_actions())
        {
            end_code.append("\t").append(r).append("\n");
        }
        end_code.append("}\n");
    }
    end_code.append("void DFA::exec_end_action()\n{\n");
    end_code.append("\tswitch (this->current_state)\n\t{\n");
    for (auto t : dfa.get_all_end_states())
    {
        string _tmp = to_string(t.first);
        end_code.append("\tcase " + _tmp + ":\n");
        end_code.append("\t\tend" + _tmp + "();\n");
        end_code.append("\t\tbreak;\n");
    }
    end_code.append("\t}\n}\n");
    code.append(end_code);
}

void generator::append_user_def()
{
    code.append("//--------------------User Definition-------------------\n");
    for (auto i : source_file::get_instance()->get_user_definitions())
    {
        code.append(i).append("\n");
    }
    code.append("//--------------------End User Definition-------------------\n");
}

generator::generator()
{
    code.append(include);
    append_user_def();
    code.append("using namespace std;\n");
    code.append("const int buffer_size = " + to_string(Config::get_instance()->get_buffer_size()) + ";\n")
        .append(data)
        .append(dfa_code);
    //TODO: add more encoding
    code.append("void read(int start);\n");
    if (Config::get_instance()->get_encoding() == UTF8)
        code.append(read_utf8);
    code.append(core);
    append_init();
    append_end_action();
    code.append("//--------------------User Code-------------------\n");
    code.append(source_file::get_instance()->get_user_code()).append("\n");
    code.append("//--------------------End User Code-------------------\n");
    code.append(main_code);
}

void generator::generate()
{
    ofstream out;
    out.open("lex.cpp", ios::out);
    if (!out.is_open())
        throw runtime_error("Generator file failed. Can not open file lex.cpp.\n");
    out << code << endl;
    out.flush();
    out.close();
}