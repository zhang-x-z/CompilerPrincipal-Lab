#pragma once
#include <string>
using namespace std;

const string include = "\
#include <vector>\n\
#include <unordered_map>\n\
#include <unordered_set>\n\
#include <iostream>\n\
#include <stdexcept>\n";

const string data = "\
char lex_buffer[buffer_size];\n\
string lex_word = \"\";\n\
int curr_index = 0;\n\
int len = 0;\n";

const string dfa_code = "\
class DFA\n\
{\n\
public:\n\
    DFA()\n\
    {\n\
        current_state = 0;\n\
        init();\n\
    }\n\
    void restart()\n\
    {\n\
        current_state = 0;\n\
    }\n\
    bool next(const string &edge)\n\
    {\n\
        unordered_map<string, int>::iterator it = states.at(current_state).find(edge);\n\
        if (it == states.at(current_state).end())\n\
            return false;\n\
        current_state = it->second;\n\
        return true;\n\
    }\n\
    bool is_end_state()\n\
    {\n\
        return !(end_states.find(current_state) == end_states.end());\n\
    }\n\
    void exec_end_action();\n\
\n\
private:\n\
    int current_state;\n\
    unordered_set<int> end_states;\n\
    vector<unordered_map<string, int>> states;\n\
    void init();\n\
};\n";

const string core = "\
void read(int start)\n\
{\n\
    if (!cin.eof())\n\
    {\n\
        cin.read(lex_buffer + start, buffer_size - start);\n\
        len = cin.gcount();\n\
    }\n\
    else\n\
        len = 0;\n\
}\n\
\n\
void unread(const string &c)\n\
{\n\
    curr_index -= c.length();\n\
}\n\
\n\
void yylex()\n\
{\n\
    read(0);\n\
    if (len == 0)\n\
        throw runtime_error(\"Empty Input file.\\n\");\n\
    DFA dfa;\n\
    string c;\n\
    while (read_next(c))\n\
    {\n\
        if (!dfa.next(c))\n\
        {\n\
            if (dfa.is_end_state())\n\
            {\n\
                lex_word.clear();\n\
                dfa.exec_end_action();\n\
                dfa.restart();\n\
                unread(c);\n\
            }\n\
            else\n\
                throw runtime_error(\"Wrong Word at: \" + lex_word + c + \"\\n\");\n\
        }\n\
        else\n\
            lex_word += c;\n\
    }\n\
    if (dfa.is_end_state())\n\
        dfa.exec_end_action();\n\
    else\n\
        throw runtime_error(\"Wrong Word at: \" + lex_word + \"\\n\");\n\
}\n";

//TODO: add more charset
const string read_utf8 = "\
bool read_next(string &s)\n\
{\n\
    s.clear();\n\
    if (curr_index == len)\n\
    {\n\
        read(0);\n\
        curr_index = 0;\n\
        if (len == 0)\n\
            return false;\n\
    }\n\
\n\
    char c = lex_buffer[curr_index];\n\
    unsigned char b1 = 0b10000000;\n\
    unsigned char b2 = 0b11100000;\n\
    unsigned char b3 = 0b11110000;\n\
    unsigned char b4 = 0b11111000;\n\
\n\
    unsigned char res = c & b1;\n\
    int ans = -1;\n\
    if (res == 0)\n\
        ans = 1;\n\
    res = c & b2;\n\
    if (res == 0b11000000)\n\
        ans = 2;\n\
    res = c & b3;\n\
    if (res == 0b11100000)\n\
        ans = 3;\n\
    res = c & b4;\n\
    if (res == 0b11110000)\n\
        ans = 4;\n\
\n\
    if (curr_index + ans - 1 >= len)\n\
    {\n\
        int _count = 0;\n\
        for (int i = curr_index; i < len; i++, _count++)\n\
        {\n\
            lex_buffer[_count] = lex_buffer[i];\n\
        }\n\
        read(_count);\n\
        curr_index = 0;\n\
    }\n\
    for (int i = 0; i < ans; i++)\n\
    {\n\
        s.append(string(1, lex_buffer[curr_index]));\n\
        curr_index++;\n\
    }\n\
    return true;\n\
}\n";

const string main_code = "\
int main()\n\
{\n\
    try\n\
    {\n\
        yylex();\n\
    }\n\
    catch (const std::exception &e)\n\
    {\n\
        std::cerr << e.what() << '\\n';\n\
    }\n\
}\n";