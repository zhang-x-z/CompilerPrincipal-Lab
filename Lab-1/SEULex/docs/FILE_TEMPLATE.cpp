#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <stdexcept>
using namespace std;

//REMIND: buffer_size can not less than 50
const int buffer_size = 15;
char lex_buffer[buffer_size];
string lex_word = "";
int curr_index = 0;
int len = 0;

class DFA
{
public:
    DFA()
    {
        init();
        current_state = start;
    }
    void restart()
    {
        current_state = start;
    }
    bool next(const string &edge)
    {
        unordered_map<string, int>::iterator it = states.at(current_state).find(edge);
        if (it == states.at(current_state).end())
            return false;
        current_state = it->second;
        return true;
    }
    bool is_end_state()
    {
        return !(end_states.find(current_state) == end_states.end());
    }
    void exec_end_action();

private:
    int current_state;
    int start;
    unordered_set<int> end_states;
    vector<unordered_map<string, int>> states;
    void init();
};

void read(int start)
{
    if (!cin.eof())
    {
        cin.read(lex_buffer + start, buffer_size - start);
        len = cin.gcount();
    }
    else
        len = 0;
}

bool read_next(string &s)
{
    s.clear();
    if (curr_index == len)
    {
        read(0);
        curr_index = 0;
        if (len == 0)
            return false;
    }

    char c = lex_buffer[curr_index];
    unsigned char b1 = 0b10000000;
    unsigned char b2 = 0b11100000;
    unsigned char b3 = 0b11110000;
    unsigned char b4 = 0b11111000;

    unsigned char res = c & b1;
    int ans = -1;
    if (res == 0)
        ans = 1;
    res = c & b2;
    if (res == 0b11000000)
        ans = 2;
    res = c & b3;
    if (res == 0b11100000)
        ans = 3;
    res = c & b4;
    if (res == 0b11110000)
        ans = 4;

    if (curr_index + ans - 1 >= len)
    {
        int _count = 0;
        for (int i = curr_index; i < len; i++, _count++)
        {
            lex_buffer[_count] = lex_buffer[i];
        }
        read(_count);
        curr_index = 0;
    }
    for (int i = 0; i < ans; i++)
    {
        s.append(string(1, lex_buffer[curr_index]));
        curr_index++;
    }
    return true;
}

void unread(const string &c)
{
    curr_index -= c.length();
}

void yylex()
{
    read(0);
    if (len == 0)
        throw runtime_error("Empty Input file.");
    DFA dfa;
    string c;
    while (read_next(c))
    {
        if (!dfa.next(c))
        {
            if (dfa.is_end_state())
            {
                lex_word.clear();
                dfa.exec_end_action();
                dfa.restart();
                unread(c);
            }
            else
                throw runtime_error("Wrong Word: " + lex_word + c + "\n");
        }
        else
            lex_word += c;
    }
    if (dfa.is_end_state())
        dfa.exec_end_action();
    else
        throw runtime_error("Wrong Word at: " + lex_word + "\n");
}

//TODO: need to remove later

void end1()
{
    cout << 0 << endl;
}

void end2()
{
    cout << 1 << endl;
}

void DFA::init()
{
    this->start = 0;
    unordered_map<string, int> m;
    m.insert(make_pair("a", 1));
    m.insert(make_pair("b", 2));
    this->states.push_back(m);
    m.clear();
    this->states.push_back(m);
    this->states.push_back(m);
    this->end_states.insert(1);
    this->end_states.insert(2);
}

void DFA::exec_end_action()
{
    switch (this->current_state)
    {
    case 1:
        end1();
        break;
    case 2:
        end2();
        break;
    default:
        break;
    }
}

int main()
{
    try
    {
        yylex();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}