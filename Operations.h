#pragma once
#include "MyStruct.h"
#include <fstream>
#include <exception>

using namespace std;

using CommandList = vector<tuple<string, int, int>>;

struct CommandsProbability {
    string command;
    double probability;
};

struct TestProfile {
    string variant;
    string variant_prefix;
    int commands_type;
};

void gen_commands_file(const string& filename, int N, int CommandsType);
vector<tuple<string, int, int>> extract_commands_from_file(const string& filename);
void run_tests(MyStruct& data, const CommandList& commands);
void generate_all_files(const vector<TestProfile>& profiles, int N);
void runProfileTest(const string& profileName, int m, const CommandList& cmds1, const CommandList& cmds2, const CommandList& cmds3);