#include <unordered_map>
using namespace std;

class NFAState
{
public:
    NFAState(int id);

private:
    int id;
    unordered_multimap<string, int> statesMap;
};