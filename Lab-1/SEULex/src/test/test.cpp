#include <config.h>
#include <iostream>
using namespace std;

int main()
{
    Config *config = Config::getInstance();
    cout << config->get_buffer_size() << endl;
}