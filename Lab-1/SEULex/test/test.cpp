#include "config.h"
#include "tinyxml2.h"
#include "string_utils.h"
#include "source_file.h"
#include "re_utils.h"
#include "string_iterator.h"
#include "utf8_string_iterator.h"
#include <iostream>
#include <string>
#include <bitset>
using namespace std;
using namespace tinyxml2;

void test_tinyxml2()
{
    try
    {
        XMLDocument doc;
        int res = doc.LoadFile("test.xml");
        XMLElement *e = doc.RootElement();
        cout << e->NoChildren() << endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void test_string_utils()
{
    string s = "    \t  \t  ";
    string_utils::trim(s);
    cout << s.empty() << endl;
    s.clear();
    string_utils::trim(s);
    cout << s.empty() << endl;
    s = "ssss   \t ";
    string_utils::trim(s);
    cout << s << "T" << endl;
    s = "  \t  ssssss";
    string_utils::trim(s);
    cout << s << "T" << endl;
    s = "\t\t\t  sss\t\t ss\t   ";
    string_utils::trim(s);
    cout << s << "T" << endl;
}

void test_source_file()
{
    source_file *file = source_file::get_instance();
    vector<string> v = file->get_user_definitions();
    for (auto line : v)
    {
        cout << line << endl;
    }

    string code = file->get_user_code();
    cout << code;

    cout << endl;
    unordered_map<string, string> map = file->get_re_definitions();
    cout << map["D"] << endl;

    vector<rule> rules = file->get_rules();
    for (rule r : rules)
    {
        cout << r.get_pattern() << endl;
        for (string a : r.get_actions())
        {
            cout << a << endl;
        }
    }
}

void test_re_utils()
{
    unordered_map<string, string> map;
    map.insert(make_pair("D", "(d|b)+"));
    string re = "(a|c)*\\{D}\\{";
    re_utils::replace_braces(re, map);
    cout << re << endl;

    re = "(a|c|b)*t[a-d]";
    re_utils::replace_brackets(re);
    cout << re << endl;
}

void test_utf8_string_iterator()
{
    string_iterator *p = new utf8_string_iterator();
    p->set_string("我和你abc");
    while (p->has_next())
    {
        string s = p->next();
        cout << s << endl;
    }
}

int main()
{
    // XMLDocument doc;
    // doc.LoadFile("test.xml");
    // XMLElement *r = doc.FirstChildElement();
    // r = r->FirstChildElement();
    // string s(r->GetText());
    // for (int i = 0; i < s.length(); i++)
    // {
    //     bitset<8> set(s.at(i));
    //     cout << set << endl;
    // }
    test_re_utils();
    return 1;
}