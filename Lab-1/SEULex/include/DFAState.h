#include <unordered_set>
#include <unordered_map>
using namespace std;

class DFAState
{
public:
    DFAState(int);
    void set_edges(const string &, int);
    void set_NFAStates(int);
    int get_id() const;
    int find_DFAState_by_edge(const string &);

private:
    int id;
    unordered_set<int> NFAStates;
    unordered_map<string, int> edges;
};
