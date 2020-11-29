#include "source_file.h"
#include "string_utils.h"

source_file *source_file::source = new source_file();

source_file::source_file() : config(Config::get_instance())
{
    parserXML();
}

string source_file::pre_process_re(const string &re, int line_num)
{
    vector<string> lines;
    string_utils::split(re, lines, "\n");
    bool has = false;
    string res;
    for (string line : lines)
    {
        string_utils::trim(line);
        if (!line.empty())
        {
            if (has)
                throw runtime_error("In source file: " + config->get_source_file_loaction() + ":\nCan only have one regular experssion. Line: " + to_string(line_num));
            //TODO: normalize re
            res = line;
            has = true;
        }
    }
    return res;
}

void source_file::parser_user_definitions(XMLElement *p)
{
    if (p->GetText() == 0)
        return;
    string content(p->GetText());
    vector<string> lines;
    string_utils::split(content, lines, "\n");
    for (string line : lines)
    {
        string_utils::trim(line);
        if (!line.empty())
            user_definitions.push_back(line);
    }
}

void source_file::parser_re_definitions(XMLElement *p)
{
    XMLElement *c = p->FirstChildElement();
    while (c != 0)
    {
        string name(c->Name());
        if (c->GetText() == 0)
            throw runtime_error("In source file: " + config->get_source_file_loaction() + ":\nMust have one and only one regular experssion. Line: " + to_string(c->GetLineNum()));
        string re(c->GetText());
        string line = pre_process_re(re, c->GetLineNum());
        if (line.empty())
            throw runtime_error("In source file: " + config->get_source_file_loaction() + ":\nMust have one and only one regular experssion. Line: " + to_string(c->GetLineNum()));
        pair<unordered_map<string, string>::iterator, bool> res = re_definitions.insert(make_pair(name, line));
        if (!res.second)
            throw runtime_error("When insert Regular expression: " + line + ". Something went wrong.");
        c = c->NextSiblingElement();
    }
}

void source_file::parser_rules(XMLElement *p)
{
    XMLElement *e = p->FirstChildElement("rule");
    while (e != 0)
    {
        XMLElement *re_ele = e->FirstChildElement("re");
        XMLElement *action_ele = e->FirstChildElement("action");
        if (re_ele == 0 || action_ele == 0)
            throw runtime_error("In source file: " + config->get_source_file_loaction() + ":\nOne <rule> must have <re> and <action>. Line: " + to_string(e->GetLineNum()));
        if (re_ele->GetText() == 0)
            throw runtime_error("In source file: " + config->get_source_file_loaction() + "\n<re> tag can not be empty. Line: " + to_string(re_ele->GetLineNum()));
        if (action_ele->GetText() == 0)
            throw runtime_error("In source file: " + config->get_source_file_loaction() + "\n<action> tag can not be empty. Line: " + to_string(action_ele->GetLineNum()));
        string re(re_ele->GetText());
        string line = pre_process_re(re, e->GetLineNum());
        if (line.empty())
            throw runtime_error("In source file: " + config->get_source_file_loaction() + "\n<re> tag can not be empty. Line: " + to_string(action_ele->GetLineNum()));
        vector<string> lines;
        string action(action_ele->GetText());
        string_utils::split(action, lines, "\n");
        vector<string> res;
        for (auto v : lines)
        {
            string_utils::trim(v);
            if (!v.empty())
            {
                res.push_back(v);
            }
        }
        if (res.empty())
            throw runtime_error("In source file: " + config->get_source_file_loaction() + "\n<action> tag can not be empty. Line: " + to_string(action_ele->GetLineNum()));
        //TODO: ADD TO RULES
        rules.push_back(rule(line, res));
        e = e->FirstChildElement("rule");
    }
}

void source_file::parser_user_code(XMLElement *p)
{
    if (p->GetText() == 0)
        return;
    string raw_code(p->GetText());
    string_utils::trim(raw_code);
    user_code = raw_code;
}

void source_file::parserXML()
{
    XMLDocument doc;
    int res = doc.LoadFile(config->get_source_file_loaction().c_str());
    if (res != 0)
        throw runtime_error("Open source file: " + config->get_source_file_loaction() + " failed. Please check your config.properties file.");

    if (doc.NoChildren())
        throw runtime_error("Empty source file: " + config->get_source_file_loaction());
    XMLElement *root = doc.RootElement();
    if (root == 0 || root->NextSiblingElement() != 0)
        throw runtime_error("Source file: " + config->get_source_file_loaction() + ": Must have one and only one root.");

    string root_name(root->Name());
    if (root_name != "Lex")
        throw runtime_error("In source file: " + config->get_source_file_loaction() + ":\nRoot tag's name must be <Lex>. Line: " + to_string(root->GetLineNum()));

    XMLElement *first = root->FirstChildElement();
    if (first == 0)
        throw runtime_error("Source file: " + config->get_source_file_loaction() + " has no content.");

    XMLElement *user_def = root->FirstChildElement("userDefinitions");
    XMLElement *re_def = root->FirstChildElement("reDefinitions");
    XMLElement *rules_part = root->FirstChildElement("rules");
    XMLElement *code = root->FirstChildElement("userCode");

    if (rules_part == 0)
        throw runtime_error("In source file: " + config->get_source_file_loaction() + ": Must have <rules> tag.");

    if (user_def != 0)
        parser_user_definitions(user_def);
    if (re_def != 0)
        parser_re_definitions(re_def);
    parser_rules(rules_part);
    if (code != 0)
        parser_user_code(code);

    //TODO: judge whether <rules> has content
    if (rules.empty())
        throw runtime_error("In source file: " + config->get_source_file_loaction() + ":\n<rules> must have content. Line: " + to_string(rules_part->GetLineNum()));
}

source_file *source_file::get_instance()
{
    return source;
}

void source_file::delete_instance()
{
    delete source;
}

const vector<string> &source_file::get_user_definitions()
{
    return user_definitions;
}

const vector<rule> &source_file::get_rules()
{
    return rules;
}

const string &source_file::get_user_code()
{
    return user_code;
}

const unordered_map<string, string> &source_file::get_re_definitions()
{
    return re_definitions;
}