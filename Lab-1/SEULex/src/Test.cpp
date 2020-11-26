#include <iostream>
#include <bitset>
#include <string>
using namespace std;

int main()
{
    const char *s = "中国";
    wchar_t t[] = {L'中', L'国'};
    cout << s[0] << endl;
    cout << s[1] << endl;
    return 0;
}