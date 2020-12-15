#pragma once
#include "DFA.h"
#include "source_file.h"
#include "code_data.h"

class generator
{
public:
    generator();
    void generate();

private:
    void generate_init_and_action(string &);
    void append_user_def();
    void append_init();
    void append_end_action();
    DFA dfa;
    string code;
};