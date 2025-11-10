#include "MyStruct.h"
#include "Operations.h"
#include "Timer.h"
using namespace std;

void gen_commands_file(const string& filename, int N, int CommandsType) {
	ofstream output_file(filename);
	if (!output_file.is_open()) {
		throw runtime_error("Error during opening file!");
	}
	mt19937 gen(std::random_device{}());
	uniform_real_distribution<double> dist(0.0, 100);

    vector<CommandsProbability> commands;

    switch (CommandsType) {
    case 10:
        commands = {
            {"read 0", 1}, {"write 0 1", 41},
            {"read 1", 42}, {"write 1 1", 47},
            {"read 2", 48}, {"write 2 1", 53},
            {"string", 100}
        };
        break;
    case 0: // equal probabilities
        commands = {
            {"read 0", 14.28}, {"write 0 1", 28.56},
            {"read 1", 42.84}, {"write 1 1", 57.12},
            {"read 2", 71.40}, {"write 2 1", 85.68},
            {"string", 100}
        };
        break;
    case 1:// custom probabilities
        commands = {
            {"read 1", 45}, {"write 1 1", 50},
            {"read 2", 95}, {"write 2 1", 100}
        };
        break;
    default:
        throw invalid_argument("Unknown CommandsType");
    }

    for (int i = 0; i < N; ++i) {
        double p = dist(gen);
        for (const auto& cmd : commands) {
            if (p < cmd.probability) {
                output_file << cmd.command << "\n";
                break;
            }
        }
    }
}

void generate_all_files(const vector<TestProfile>& profiles, int N) {
    cout << format("Generating {} command files ({} commands each)...\n",
        profiles.size() * 3, N);

    for (const auto& profile : profiles) {
        for (int i = 1; i <= 3; ++i) {
            const string filename = format("commands_{}_f{}.txt", profile.variant_prefix, i);
            gen_commands_file(filename, N, profile.commands_type);
        }
    }
    cout << "File generation complete.\n";
}

CommandList extract_commands_from_file(const string& filename) {
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw runtime_error("Error during opening file!");
    }
    
    CommandList commands;
    string command_line;
    while (getline(input_file, command_line)) {
        stringstream ss(command_line);
        string parsed_command;
        int i = 0, val = 0;
        ss >> parsed_command;
        if (parsed_command == "read") {
            ss >> i;
        }
        if (parsed_command == "write") {
            ss >> i >> val;
        }
        commands.emplace_back(parsed_command, i, val);
    }
    return commands;
}

void run_tests(MyStruct& data, const CommandList& commands) {
    for (const auto& command : commands) {

        const string& cmd = get<0>(command);
        const int& i = get<1>(command);
        const int& val = get<2>(command);

        if (cmd == "read") {
            data.get(i);
        }
        else if (cmd == "write") {
            data.set(i, val);
        }
        else if (cmd == "string") {
            data.to_string();
        }
    }
}
