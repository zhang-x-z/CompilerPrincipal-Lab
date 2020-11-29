#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "rule.h"
#include "tinyxml2.h"
#include "config.h"
using namespace tinyxml2;
using namespace std;

class source_file
{
public:
    static source_file *get_instance();
    static void delete_instance();
    const vector<string> &get_user_definitions();
    const vector<rule> &get_rules();
    const string &get_user_code();
    const unordered_map<string, string> &get_re_definitions();

private:
    source_file();
    void parserXML();
    void parser_user_definitions(XMLElement *);
    void parser_re_definitions(XMLElement *);
    void parser_rules(XMLElement *);
    void parser_user_code(XMLElement *);
    string pre_process_re(const string &, int);
    static source_file *source;
    Config *config;
    vector<string> user_definitions;
    unordered_map<string, string> re_definitions;
    vector<rule> rules;
    string user_code;
};