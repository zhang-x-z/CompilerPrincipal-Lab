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
    // vector<string> v = file->get_user_definitions();
    // for (auto line : v)
    // {
    //     cout << line << endl;
    // }

    // string code = file->get_user_code();
    // cout << code;

    // cout << endl;
    // unordered_map<string, string> map = file->get_re_definitions();
    // cout << map["D"] << endl;

    vector<rule> rules = file->get_rules();
    cout << rules.size() << endl;
    for (rule r : rules)
    {
        cout << r.get_pattern() << endl;
        cout << r.get_actions().size() << endl;
        for (string a : r.get_actions())
        {
            cout << a << endl;
        }
    }
}

void test_re_utils_part()
{
    // unordered_map<string, string> map;
    // map.insert(make_pair("D", "(d|b)+"));
    // string re = "(a|c)*\\{D}\\{";
    // re_utils::replace_braces(re, map);
    // cout << re << endl;

    // re = "(a|b|c)*t[^abcdefghijklmnopqrstuvwxyz0123456789]"; //"\[ac]""(a|b|c)*t[ad-]""(a|b|c)*t[a[\\]""[a-e]""(a|b|c)*t[c-a]""(a|b|c)*t[-cd]"
    // re_utils::replace_brackets(re);
    // cout << re.at(0) << endl;
    // cout << re.at(1) << endl;
    // cout << re.at(2) << endl;

    // re = "[^abcdefghijklmnopqrstuvwxyz]";
    // re_utils::replace_brackets(re);
    // cout << re.length() << endl;

    // re = "[^abcdefghijklmnopqrstuvwxyz-](a|b)?";
    // re_utils::replace_brackets(re);
    // cout << re << endl;

    string re = "a+";
    re_utils::replace_plus_question_and_check_parentheses(re);
    cout << re << endl;

    re = "((a|b)+)?";
    re_utils::replace_plus_question_and_check_parentheses(re);
    cout << re << endl;

    re = "(a|b(q+))";
    re_utils::replace_plus_question_and_check_parentheses(re);
    cout << re << endl;

    re = "a|b?)a+";
    // re_utils::replace_plus_question_and_check_parentheses(re);

    re = "(a|b)a|b)+";
    //re_utils::replace_plus_question_and_check_parentheses(re);

    re = ".";
    // re_utils::handle_dot(re);
    // cout << re << endl;

    re = "(a|b|c).*";
    // re_utils::handle_dot(re);
    // cout << re << endl;

    re = "(a|c)*\\..*";
    //re_utils::handle_dot(re);
    //cout << re << endl;

    re = "(a|b)(c|d|e)*";
    re_utils::add_dot(re);
    cout << re << endl;

    re = "abcdef*(a|b)*";
    re_utils::add_dot(re);
    cout << re << endl;

    re = "a\\*b(c|d)(e|f)*p";
    re_utils::add_dot(re);
    cout << re << endl;

    re = "a\\b\\.\\\\\\t*\\((a|b)*\\n";
    re_utils::handle_espace(re);
    cout << re;
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

void test_re_utils()
{
    unordered_map<string, string> map;
    map.insert(make_pair("哈哈", "[a-z]*(d|b)+好?"));
    string re = "(我|你)?{哈哈}\\|冷";
    re_utils::pre_process_re(re, map);
    cout << re << endl;
}

void test_re_infix_to_postfix()
{
    string re = "(a|b)*|b.c.\\.";
    queue<string> a;
    re_utils::infix_to_postfix(re, a);
    while (!a.empty())
    {
        cout << a.front() << endl;
        a.pop();
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
    test_re_infix_to_postfix();
    return 1;
}