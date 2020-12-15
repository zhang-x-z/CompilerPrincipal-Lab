#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <stdexcept>
//--------------------User Definition-------------------
//--------------------End User Definition-------------------
using namespace std;
const int buffer_size = 60;
char lex_buffer[buffer_size];
string lex_word = "";
int curr_index = 0;
int len = 0;
class DFA
{
public:
    DFA()
    {
        current_state = 0;
        init();
    }
    void restart()
    {
        current_state = 0;
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
    unordered_set<int> end_states;
    vector<unordered_map<string, int>> states;
    void init();
};
void read(int start);
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

void unread(const string &c)
{
    curr_index -= c.length();
}

void yylex()
{
    read(0);
    if (len == 0)
        throw runtime_error("Empty Input file.\n");
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
                throw runtime_error("Wrong Word at: " + lex_word + c + "\n");
        }
        else
            lex_word += c;
    }
    if (dfa.is_end_state())
        dfa.exec_end_action();
    else
        throw runtime_error("Wrong Word at: " + lex_word + "\n");
}
void DFA::init()
{
	unordered_map<string, int> empty;
	unordered_map<string, int> use;
	use.clear();
	use.insert(make_pair("6", 10));
	use.insert(make_pair("0", 7));
	use.insert(make_pair("2", 3));
	use.insert(make_pair("1", 4));
	use.insert(make_pair("7", 1));
	use.insert(make_pair("3", 2));
	use.insert(make_pair("9", 8));
	use.insert(make_pair("4", 9));
	use.insert(make_pair("5", 6));
	use.insert(make_pair("8", 5));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 17));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("0", 14));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("6", 11));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("9", 21));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 14));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("\.", 19));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("9", 21));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 14));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("3", 17));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("\.", 22));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 18));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("6", 11));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 17));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("0", 14));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 17));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("\.", 19));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("0", 14));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 17));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("\.", 19));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 18));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("0", 14));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 17));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("7", 18));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("0", 14));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("0", 23));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("2", 32));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("6", 11));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("0", 14));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("2", 15));
	use.insert(make_pair("1", 16));
	use.insert(make_pair("\.", 19));
	use.insert(make_pair("4", 20));
	use.insert(make_pair("9", 21));
	use.insert(make_pair("5", 12));
	use.insert(make_pair("8", 13));
	use.insert(make_pair("0", 14));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("7", 18));
	use.insert(make_pair("6", 11));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 38));
	use.insert(make_pair("3", 37));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("0", 33));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 39));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("2", 32));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("0", 23));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("5", 30));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("2", 32));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("0", 23));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 25));
	use.insert(make_pair("2", 32));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("0", 23));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 30));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("0", 23));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("2", 32));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("\.", 22));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 23));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("2", 32));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 23));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("2", 32));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("2", 32));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("0", 23));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("2", 32));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("0", 23));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("6", 26));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("2", 32));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("0", 23));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("9", 27));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("8", 29));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("9", 27));
	use.insert(make_pair("4", 28));
	use.insert(make_pair("5", 30));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("0", 23));
	use.insert(make_pair("\.", 22));
	use.insert(make_pair("2", 32));
	use.insert(make_pair("1", 31));
	use.insert(make_pair("6", 26));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("9", 39));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("0", 33));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("3", 37));
	use.insert(make_pair("7", 38));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("7", 38));
	use.insert(make_pair("3", 37));
	use.insert(make_pair("0", 33));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("0", 33));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("7", 38));
	use.insert(make_pair("3", 37));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("5", 34));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("0", 33));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("3", 37));
	use.insert(make_pair("7", 38));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 33));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("3", 37));
	use.insert(make_pair("7", 38));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("8", 35));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("0", 33));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("3", 37));
	use.insert(make_pair("7", 38));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 37));
	use.insert(make_pair("7", 38));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("0", 33));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 37));
	use.insert(make_pair("7", 38));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("0", 33));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("6", 36));
	use.insert(make_pair("3", 37));
	use.insert(make_pair("7", 38));
	use.insert(make_pair("0", 33));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("4", 40));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 37));
	use.insert(make_pair("7", 38));
	use.insert(make_pair("0", 33));
	use.insert(make_pair("6", 36));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 39));
	use.insert(make_pair("8", 35));
	use.insert(make_pair("5", 34));
	use.insert(make_pair("1", 41));
	use.insert(make_pair("2", 42));
	this->states.push_back(use);
	this->end_states.insert(37);
	this->end_states.insert(36);
	this->end_states.insert(35);
	this->end_states.insert(34);
	this->end_states.insert(33);
	this->end_states.insert(22);
	this->end_states.insert(21);
	this->end_states.insert(20);
	this->end_states.insert(18);
	this->end_states.insert(17);
	this->end_states.insert(6);
	this->end_states.insert(42);
	this->end_states.insert(5);
	this->end_states.insert(41);
	this->end_states.insert(4);
	this->end_states.insert(40);
	this->end_states.insert(3);
	this->end_states.insert(38);
	this->end_states.insert(1);
	this->end_states.insert(39);
	this->end_states.insert(2);
	this->end_states.insert(7);
	this->end_states.insert(8);
	this->end_states.insert(9);
	this->end_states.insert(10);
	this->end_states.insert(11);
	this->end_states.insert(12);
	this->end_states.insert(13);
	this->end_states.insert(14);
	this->end_states.insert(15);
	this->end_states.insert(16);
}
void end37()
{
	cout << "FLOAT" << endl;
}
void end36()
{
	cout << "FLOAT" << endl;
}
void end35()
{
	cout << "FLOAT" << endl;
}
void end34()
{
	cout << "FLOAT" << endl;
}
void end33()
{
	cout << "FLOAT" << endl;
}
void end22()
{
	cout << "FLOAT" << endl;
}
void end21()
{
	cout << "INT" << endl;
}
void end20()
{
	cout << "INT" << endl;
}
void end18()
{
	cout << "INT" << endl;
}
void end17()
{
	cout << "INT" << endl;
}
void end6()
{
	cout << "INT" << endl;
}
void end42()
{
	cout << "FLOAT" << endl;
}
void end5()
{
	cout << "INT" << endl;
}
void end41()
{
	cout << "FLOAT" << endl;
}
void end4()
{
	cout << "INT" << endl;
}
void end40()
{
	cout << "FLOAT" << endl;
}
void end3()
{
	cout << "INT" << endl;
}
void end38()
{
	cout << "FLOAT" << endl;
}
void end1()
{
	cout << "INT" << endl;
}
void end39()
{
	cout << "FLOAT" << endl;
}
void end2()
{
	cout << "INT" << endl;
}
void end7()
{
	cout << "INT" << endl;
}
void end8()
{
	cout << "INT" << endl;
}
void end9()
{
	cout << "INT" << endl;
}
void end10()
{
	cout << "INT" << endl;
}
void end11()
{
	cout << "INT" << endl;
}
void end12()
{
	cout << "INT" << endl;
}
void end13()
{
	cout << "INT" << endl;
}
void end14()
{
	cout << "INT" << endl;
}
void end15()
{
	cout << "INT" << endl;
}
void end16()
{
	cout << "INT" << endl;
}
void DFA::exec_end_action()
{
	switch (this->current_state)
	{
	case 37:
		end37();
		break;
	case 36:
		end36();
		break;
	case 35:
		end35();
		break;
	case 34:
		end34();
		break;
	case 33:
		end33();
		break;
	case 22:
		end22();
		break;
	case 21:
		end21();
		break;
	case 20:
		end20();
		break;
	case 18:
		end18();
		break;
	case 17:
		end17();
		break;
	case 6:
		end6();
		break;
	case 42:
		end42();
		break;
	case 5:
		end5();
		break;
	case 41:
		end41();
		break;
	case 4:
		end4();
		break;
	case 40:
		end40();
		break;
	case 3:
		end3();
		break;
	case 38:
		end38();
		break;
	case 1:
		end1();
		break;
	case 39:
		end39();
		break;
	case 2:
		end2();
		break;
	case 7:
		end7();
		break;
	case 8:
		end8();
		break;
	case 9:
		end9();
		break;
	case 10:
		end10();
		break;
	case 11:
		end11();
		break;
	case 12:
		end12();
		break;
	case 13:
		end13();
		break;
	case 14:
		end14();
		break;
	case 15:
		end15();
		break;
	case 16:
		end16();
		break;
	}
}
//--------------------User Code-------------------

//--------------------End User Code-------------------
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

