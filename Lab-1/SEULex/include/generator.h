#pragma once
#include "DFA.h"

class generator
{
public:
    generator();
    void generate();

private:
    DFA dfa;
};