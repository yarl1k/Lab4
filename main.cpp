#include "Operations.h"
#include "MyStruct.h"
#include "Timer.h"

using namespace std;
void runProfileTest(const string& profileName, int m, const CommandList& cmds1, const CommandList& cmds2, const CommandList& cmds3)
{
    cout << format("--- Testing profile: {} ---\n", profileName);
    MyStruct data(m);

    double time1 = timeit([&]() {
        run_tests(data, cmds1);
        });
    cout << format("1-thread time: {:.6f} sec\n", time1);

    double time2 = timeit([&]() {
        thread t1(run_tests, ref(data), cref(cmds1));
        thread t2(run_tests, ref(data), cref(cmds2));
        t1.join();
        t2.join();
        });
    cout << format("2-thread time: {:.6f} sec\n", time2);

    double time3 = timeit([&]() {
        thread t3(run_tests, ref(data), cref(cmds1));
        thread t4(run_tests, ref(data), cref(cmds2));
        thread t5(run_tests, ref(data), cref(cmds3));
        t3.join();
        t4.join();
        t5.join();
        });
    cout << format("3-thread time: {:.6f} sec\n", time3);

    cout << "------------------------------------------\n";
}


int main() {
    const int m = 3;
    const int N = 1000000;
    const vector<TestProfile> profiles = {
        {"Variant 10", "v10", 10}, {"Equal","eq",  0}, {"Custom","cust", 1} // 0 and 1 for other variants 
    };
    try {
        cout << "Loading files and running tests...\n";
        generate_all_files(profiles, N);
        for (const auto& profile : profiles) {

            string f1 = format("commands_{}_f1.txt", profile.variant_prefix);
            string f2 = format("commands_{}_f2.txt", profile.variant_prefix);
            string f3 = format("commands_{}_f3.txt", profile.variant_prefix);

            CommandList cmds1 = extract_commands_from_file(f1);
            CommandList cmds2 = extract_commands_from_file(f2);
            CommandList cmds3 = extract_commands_from_file(f3);

            runProfileTest(profile.variant, m, cmds1, cmds2, cmds3);
        }

        return 0;
    }
    catch (const exception& e) {
        cout << e.what();
        return 1;
    }
}