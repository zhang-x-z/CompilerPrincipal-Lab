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
	this->start = 60;
	unordered_map<string, int> empty;
	unordered_map<string, int> use;
	use.clear();
	use.insert(make_pair("e", 56));
	this->states.push_back(use);
	this->states.push_back(empty);
	this->states.push_back(empty);
	this->states.push_back(empty);
	use.clear();
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("6", 31));
	use.insert(make_pair(".", 21));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("4", 23));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("6", 31));
	use.insert(make_pair(".", 21));
	this->states.push_back(use);
	this->states.push_back(empty);
	this->states.push_back(empty);
	use.clear();
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("0", 30));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair(".", 21));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("0", 30));
	this->states.push_back(use);
	this->states.push_back(empty);
	this->states.push_back(empty);
	this->states.push_back(empty);
	use.clear();
	use.insert(make_pair(".", 21));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("0", 30));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("6", 31));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair(".", 32));
	this->states.push_back(use);
	this->states.push_back(empty);
	use.clear();
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("0", 30));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 30));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	this->states.push_back(use);
	this->states.push_back(empty);
	use.clear();
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("0", 30));
	use.insert(make_pair(".", 21));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("2", 39));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("0", 42));
	use.insert(make_pair("7", 43));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("3", 35));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("3", 25));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("8", 29));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 24));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("8", 29));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("3", 25));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 25));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("6", 31));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("7", 24));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("6", 31));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 24));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("6", 31));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("4", 23));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("7", 24));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair(".", 21));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("6", 31));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 24));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("8", 29));
	use.insert(make_pair("5", 28));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("3", 25));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("9", 22));
	use.insert(make_pair("4", 23));
	use.insert(make_pair("6", 31));
	use.insert(make_pair("3", 25));
	use.insert(make_pair("7", 24));
	use.insert(make_pair("5", 28));
	use.insert(make_pair("8", 29));
	use.insert(make_pair(".", 21));
	use.insert(make_pair("0", 30));
	use.insert(make_pair("1", 26));
	use.insert(make_pair("2", 27));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 45));
	use.insert(make_pair("7", 46));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("2", 49));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("0", 53));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("9", 48));
	this->states.push_back(use);
	this->states.push_back(empty);
	use.clear();
	use.insert(make_pair("7", 43));
	use.insert(make_pair("3", 35));
	use.insert(make_pair("2", 39));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("0", 42));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("8", 36));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 43));
	use.insert(make_pair("3", 35));
	use.insert(make_pair("2", 39));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("0", 42));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("5", 37));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 42));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("7", 43));
	use.insert(make_pair("2", 39));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("3", 35));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("9", 41));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("2", 39));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("0", 42));
	use.insert(make_pair("3", 35));
	use.insert(make_pair("7", 43));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 42));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("3", 35));
	use.insert(make_pair("7", 43));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("2", 39));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 42));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("3", 35));
	use.insert(make_pair("7", 43));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("2", 39));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("0", 42));
	use.insert(make_pair("3", 35));
	use.insert(make_pair("7", 43));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("2", 39));
	use.insert(make_pair("1", 38));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 42));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("3", 35));
	use.insert(make_pair("7", 43));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("2", 39));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 35));
	use.insert(make_pair("7", 43));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("2", 39));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("8", 36));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("0", 42));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("4", 40));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 43));
	use.insert(make_pair("3", 35));
	use.insert(make_pair("2", 39));
	use.insert(make_pair("1", 38));
	use.insert(make_pair("6", 34));
	use.insert(make_pair("9", 41));
	use.insert(make_pair("4", 40));
	use.insert(make_pair("0", 42));
	use.insert(make_pair("5", 37));
	use.insert(make_pair("8", 36));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("7", 46));
	use.insert(make_pair("3", 45));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("2", 49));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("9", 48));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("0", 53));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("6", 44));
	use.insert(make_pair("9", 48));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("0", 53));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("7", 46));
	use.insert(make_pair("3", 45));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("2", 49));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("4", 47));
	use.insert(make_pair("9", 48));
	use.insert(make_pair("0", 53));
	use.insert(make_pair("2", 49));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("3", 45));
	use.insert(make_pair("7", 46));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 45));
	use.insert(make_pair("7", 46));
	use.insert(make_pair("9", 48));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("2", 49));
	use.insert(make_pair("0", 53));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("9", 48));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("2", 49));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("7", 46));
	use.insert(make_pair("3", 45));
	use.insert(make_pair("0", 53));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("0", 53));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("9", 48));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("3", 45));
	use.insert(make_pair("7", 46));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("2", 49));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("9", 48));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("0", 53));
	use.insert(make_pair("2", 49));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("3", 45));
	use.insert(make_pair("7", 46));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 45));
	use.insert(make_pair("7", 46));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("2", 49));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("9", 48));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("0", 53));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("3", 45));
	use.insert(make_pair("7", 46));
	use.insert(make_pair("0", 53));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("9", 48));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("2", 49));
	use.insert(make_pair("1", 50));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("9", 48));
	use.insert(make_pair("4", 47));
	use.insert(make_pair("6", 44));
	use.insert(make_pair("5", 52));
	use.insert(make_pair("8", 51));
	use.insert(make_pair("0", 53));
	use.insert(make_pair("7", 46));
	use.insert(make_pair("3", 45));
	use.insert(make_pair("1", 50));
	use.insert(make_pair("2", 49));
	this->states.push_back(use);
	this->states.push_back(empty);
	this->states.push_back(empty);
	this->states.push_back(empty);
	use.clear();
	use.insert(make_pair("a", 57));
	use.insert(make_pair("G", 57));
	use.insert(make_pair("Y", 57));
	use.insert(make_pair("*", 57));
	use.insert(make_pair("B", 57));
	use.insert(make_pair("u", 57));
	use.insert(make_pair("<", 57));
	use.insert(make_pair("\v", 57));
	use.insert(make_pair("F", 57));
	use.insert(make_pair("J", 57));
	use.insert(make_pair("j", 57));
	use.insert(make_pair("'", 57));
	use.insert(make_pair("3", 57));
	use.insert(make_pair("T", 57));
	use.insert(make_pair("9", 57));
	use.insert(make_pair("N", 57));
	use.insert(make_pair("^", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("g", 57));
	use.insert(make_pair("h", 57));
	use.insert(make_pair("\\", 59));
	use.insert(make_pair(")", 57));
	use.insert(make_pair("C", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("0", 57));
	use.insert(make_pair("p", 57));
	use.insert(make_pair(":", 57));
	use.insert(make_pair("i", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("R", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("\r", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("r", 57));
	use.insert(make_pair("P", 57));
	use.insert(make_pair("6", 57));
	use.insert(make_pair("-", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair(">", 57));
	use.insert(make_pair("m", 57));
	use.insert(make_pair("M", 57));
	use.insert(make_pair("s", 57));
	use.insert(make_pair("/", 57));
	use.insert(make_pair("x", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("o", 57));
	use.insert(make_pair(",", 57));
	use.insert(make_pair("2", 57));
	use.insert(make_pair("[", 57));
	use.insert(make_pair("S", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("c", 57));
	use.insert(make_pair("O", 57));
	use.insert(make_pair(" ", 57));
	use.insert(make_pair("L", 57));
	use.insert(make_pair("I", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("8", 57));
	use.insert(make_pair("+", 57));
	use.insert(make_pair("n", 57));
	use.insert(make_pair("\f", 57));
	use.insert(make_pair("~", 57));
	use.insert(make_pair("A", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("_", 57));
	use.insert(make_pair("e", 57));
	use.insert(make_pair("U", 57));
	use.insert(make_pair("`", 57));
	use.insert(make_pair("!", 57));
	use.insert(make_pair("Z", 57));
	use.insert(make_pair("4", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("}", 57));
	use.insert(make_pair("%", 57));
	use.insert(make_pair("H", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("Q", 57));
	use.insert(make_pair("V", 57));
	use.insert(make_pair(".", 57));
	use.insert(make_pair("X", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("t", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("D", 57));
	use.insert(make_pair("W", 57));
	use.insert(make_pair(";", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("&", 57));
	use.insert(make_pair("y", 57));
	use.insert(make_pair("K", 57));
	use.insert(make_pair("\"", 33));
	use.insert(make_pair("", 57));
	use.insert(make_pair("(", 57));
	use.insert(make_pair("]", 57));
	use.insert(make_pair("f", 57));
	use.insert(make_pair("@", 57));
	use.insert(make_pair("E", 57));
	use.insert(make_pair("1", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("$", 57));
	use.insert(make_pair("?", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("5", 57));
	use.insert(make_pair("k", 57));
	use.insert(make_pair("d", 57));
	use.insert(make_pair("\t", 57));
	use.insert(make_pair("{", 57));
	use.insert(make_pair("z", 57));
	use.insert(make_pair("|", 57));
	use.insert(make_pair("=", 57));
	use.insert(make_pair("l", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("q", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("w", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("#", 57));
	use.insert(make_pair("7", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("b", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("v", 57));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("l", 64));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("Y", 57));
	use.insert(make_pair("*", 57));
	use.insert(make_pair("\v", 57));
	use.insert(make_pair("<", 57));
	use.insert(make_pair("n", 57));
	use.insert(make_pair("}", 57));
	use.insert(make_pair("\"", 57));
	use.insert(make_pair("K", 57));
	use.insert(make_pair("\n", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("x", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("o", 57));
	use.insert(make_pair("=", 57));
	use.insert(make_pair("l", 57));
	use.insert(make_pair("s", 57));
	use.insert(make_pair("M", 57));
	use.insert(make_pair("b", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("5", 57));
	use.insert(make_pair("!", 57));
	use.insert(make_pair("Z", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("4", 57));
	use.insert(make_pair("/", 57));
	use.insert(make_pair("~", 57));
	use.insert(make_pair("\f", 57));
	use.insert(make_pair("A", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("t", 57));
	use.insert(make_pair("G", 57));
	use.insert(make_pair("a", 57));
	use.insert(make_pair("0", 57));
	use.insert(make_pair("p", 57));
	use.insert(make_pair("C", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("F", 57));
	use.insert(make_pair(")", 57));
	use.insert(make_pair("^", 57));
	use.insert(make_pair("N", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair(":", 57));
	use.insert(make_pair("i", 57));
	use.insert(make_pair("u", 57));
	use.insert(make_pair("B", 57));
	use.insert(make_pair("?", 57));
	use.insert(make_pair("$", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("O", 57));
	use.insert(make_pair(".", 57));
	use.insert(make_pair("X", 57));
	use.insert(make_pair("`", 57));
	use.insert(make_pair("U", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("e", 57));
	use.insert(make_pair("_", 57));
	use.insert(make_pair(",", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("J", 57));
	use.insert(make_pair("j", 57));
	use.insert(make_pair("%", 57));
	use.insert(make_pair("H", 57));
	use.insert(make_pair("k", 57));
	use.insert(make_pair("d", 57));
	use.insert(make_pair("T", 57));
	use.insert(make_pair("3", 57));
	use.insert(make_pair("'", 57));
	use.insert(make_pair("{", 57));
	use.insert(make_pair("z", 57));
	use.insert(make_pair("Q", 57));
	use.insert(make_pair("V", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("+", 57));
	use.insert(make_pair("W", 57));
	use.insert(make_pair(";", 57));
	use.insert(make_pair("h", 57));
	use.insert(make_pair("\\", 57));
	use.insert(make_pair("&", 57));
	use.insert(make_pair("y", 57));
	use.insert(make_pair("f", 57));
	use.insert(make_pair("@", 57));
	use.insert(make_pair("E", 57));
	use.insert(make_pair("1", 57));
	use.insert(make_pair("(", 57));
	use.insert(make_pair("]", 57));
	use.insert(make_pair(" ", 57));
	use.insert(make_pair("L", 57));
	use.insert(make_pair("I", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("v", 57));
	use.insert(make_pair("6", 57));
	use.insert(make_pair("-", 57));
	use.insert(make_pair("P", 57));
	use.insert(make_pair("r", 57));
	use.insert(make_pair("\r", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("R", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("|", 57));
	use.insert(make_pair("9", 57));
	use.insert(make_pair("q", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("w", 57));
	use.insert(make_pair("g", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("2", 57));
	use.insert(make_pair("c", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("[", 57));
	use.insert(make_pair("S", 57));
	use.insert(make_pair("D", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("#", 57));
	use.insert(make_pair("7", 57));
	use.insert(make_pair("\t", 57));
	use.insert(make_pair("m", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("8", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair("", 57));
	use.insert(make_pair(">", 57));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("]", 10));
	use.insert(make_pair("\n", 11));
	use.insert(make_pair("n", 65));
	use.insert(make_pair("\r", 3));
	use.insert(make_pair("4", 13));
	use.insert(make_pair("}", 12));
	use.insert(make_pair("t", 67));
	use.insert(make_pair("9", 14));
	use.insert(make_pair("[", 7));
	use.insert(make_pair("\t", 6));
	use.insert(make_pair("8", 9));
	use.insert(make_pair("5", 8));
	use.insert(make_pair("6", 5));
	use.insert(make_pair(":", 1));
	use.insert(make_pair(" ", 2));
	use.insert(make_pair("7", 20));
	use.insert(make_pair("1", 4));
	use.insert(make_pair("f", 68));
	use.insert(make_pair(",", 16));
	use.insert(make_pair("0", 15));
	use.insert(make_pair("3", 17));
	use.insert(make_pair("{", 19));
	use.insert(make_pair("2", 18));
	use.insert(make_pair("\"", 57));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("s", 0));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("u", 66));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("l", 61));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("l", 54));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("u", 58));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("e", 55));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("r", 62));
	this->states.push_back(use);
	use.clear();
	use.insert(make_pair("a", 63));
	this->states.push_back(use);
	this->end_states.insert(35);
	this->end_states.insert(9);
	this->end_states.insert(31);
	this->end_states.insert(30);
	this->end_states.insert(29);
	this->end_states.insert(28);
	this->end_states.insert(27);
	this->end_states.insert(26);
	this->end_states.insert(25);
	this->end_states.insert(53);
	this->end_states.insert(24);
	this->end_states.insert(52);
	this->end_states.insert(23);
	this->end_states.insert(51);
	this->end_states.insert(22);
	this->end_states.insert(50);
	this->end_states.insert(21);
	this->end_states.insert(49);
	this->end_states.insert(20);
	this->end_states.insert(48);
	this->end_states.insert(33);
	this->end_states.insert(11);
	this->end_states.insert(12);
	this->end_states.insert(39);
	this->end_states.insert(2);
	this->end_states.insert(40);
	this->end_states.insert(3);
	this->end_states.insert(14);
	this->end_states.insert(42);
	this->end_states.insert(5);
	this->end_states.insert(13);
	this->end_states.insert(47);
	this->end_states.insert(10);
	this->end_states.insert(37);
	this->end_states.insert(54);
	this->end_states.insert(17);
	this->end_states.insert(7);
	this->end_states.insert(44);
	this->end_states.insert(41);
	this->end_states.insert(4);
	this->end_states.insert(38);
	this->end_states.insert(1);
	this->end_states.insert(43);
	this->end_states.insert(6);
	this->end_states.insert(15);
	this->end_states.insert(16);
	this->end_states.insert(8);
	this->end_states.insert(45);
	this->end_states.insert(34);
	this->end_states.insert(55);
	this->end_states.insert(18);
	this->end_states.insert(32);
	this->end_states.insert(56);
	this->end_states.insert(19);
	this->end_states.insert(36);
	this->end_states.insert(46);
}
void end35()
{
	cout << "FLOAT" << endl;
}
void end9()
{
	cout << "INT" << endl;
}
void end31()
{
	cout << "INT" << endl;
}
void end30()
{
	cout << "INT" << endl;
}
void end29()
{
	cout << "INT" << endl;
}
void end28()
{
	cout << "INT" << endl;
}
void end27()
{
	cout << "INT" << endl;
}
void end26()
{
	cout << "INT" << endl;
}
void end25()
{
	cout << "INT" << endl;
}
void end53()
{
	cout << "FLOAT" << endl;
}
void end24()
{
	cout << "INT" << endl;
}
void end52()
{
	cout << "FLOAT" << endl;
}
void end23()
{
	cout << "INT" << endl;
}
void end51()
{
	cout << "FLOAT" << endl;
}
void end22()
{
	cout << "INT" << endl;
}
void end50()
{
	cout << "FLOAT" << endl;
}
void end21()
{
	cout << "FLOAT" << endl;
}
void end49()
{
	cout << "FLOAT" << endl;
}
void end20()
{
	cout << "INT" << endl;
}
void end48()
{
	cout << "FLOAT" << endl;
}
void end33()
{
	cout << "STRING" << endl;
}
void end11()
{
	cout << "WIGHTSPACE" << endl;
}
void end12()
{
	cout << "RIGHT BRACE" << endl;
}
void end39()
{
	cout << "FLOAT" << endl;
}
void end2()
{
	cout << "WIGHTSPACE" << endl;
}
void end40()
{
	cout << "FLOAT" << endl;
}
void end3()
{
	cout << "WIGHTSPACE" << endl;
}
void end14()
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
void end13()
{
	cout << "INT" << endl;
}
void end47()
{
	cout << "FLOAT" << endl;
}
void end10()
{
	cout << "RIGHT BRACKET" << endl;
}
void end37()
{
	cout << "FLOAT" << endl;
}
void end54()
{
	cout << "NULL" << endl;
}
void end17()
{
	cout << "INT" << endl;
}
void end7()
{
	cout << "LEFT BRACKET" << endl;
}
void end44()
{
	cout << "FLOAT" << endl;
}
void end41()
{
	cout << "FLOAT" << endl;
}
void end4()
{
	cout << "INT" << endl;
}
void end38()
{
	cout << "FLOAT" << endl;
}
void end1()
{
	cout << "COLON" << endl;
}
void end43()
{
	cout << "FLOAT" << endl;
}
void end6()
{
	cout << "WIGHTSPACE" << endl;
}
void end15()
{
	cout << "INT" << endl;
}
void end16()
{
	cout << "COMMA" << endl;
}
void end8()
{
	cout << "INT" << endl;
}
void end45()
{
	cout << "FLOAT" << endl;
}
void end34()
{
	cout << "FLOAT" << endl;
}
void end55()
{
	cout << "TRUE" << endl;
}
void end18()
{
	cout << "INT" << endl;
}
void end32()
{
	cout << "FLOAT" << endl;
}
void end56()
{
	cout << "FALSE" << endl;
}
void end19()
{
	cout << "LEFT BRACE" << endl;
}
void end36()
{
	cout << "FLOAT" << endl;
}
void end46()
{
	cout << "FLOAT" << endl;
}
void DFA::exec_end_action()
{
	switch (this->current_state)
	{
	case 35:
		end35();
		break;
	case 9:
		end9();
		break;
	case 31:
		end31();
		break;
	case 30:
		end30();
		break;
	case 29:
		end29();
		break;
	case 28:
		end28();
		break;
	case 27:
		end27();
		break;
	case 26:
		end26();
		break;
	case 25:
		end25();
		break;
	case 53:
		end53();
		break;
	case 24:
		end24();
		break;
	case 52:
		end52();
		break;
	case 23:
		end23();
		break;
	case 51:
		end51();
		break;
	case 22:
		end22();
		break;
	case 50:
		end50();
		break;
	case 21:
		end21();
		break;
	case 49:
		end49();
		break;
	case 20:
		end20();
		break;
	case 48:
		end48();
		break;
	case 33:
		end33();
		break;
	case 11:
		end11();
		break;
	case 12:
		end12();
		break;
	case 39:
		end39();
		break;
	case 2:
		end2();
		break;
	case 40:
		end40();
		break;
	case 3:
		end3();
		break;
	case 14:
		end14();
		break;
	case 42:
		end42();
		break;
	case 5:
		end5();
		break;
	case 13:
		end13();
		break;
	case 47:
		end47();
		break;
	case 10:
		end10();
		break;
	case 37:
		end37();
		break;
	case 54:
		end54();
		break;
	case 17:
		end17();
		break;
	case 7:
		end7();
		break;
	case 44:
		end44();
		break;
	case 41:
		end41();
		break;
	case 4:
		end4();
		break;
	case 38:
		end38();
		break;
	case 1:
		end1();
		break;
	case 43:
		end43();
		break;
	case 6:
		end6();
		break;
	case 15:
		end15();
		break;
	case 16:
		end16();
		break;
	case 8:
		end8();
		break;
	case 45:
		end45();
		break;
	case 34:
		end34();
		break;
	case 55:
		end55();
		break;
	case 18:
		end18();
		break;
	case 32:
		end32();
		break;
	case 56:
		end56();
		break;
	case 19:
		end19();
		break;
	case 36:
		end36();
		break;
	case 46:
		end46();
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

