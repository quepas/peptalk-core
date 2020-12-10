//
// Created by quepas on 11/11/2020.
//

#include <iostream>
#include "profiling.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    string domain = "PAPI_TOT_INS";
    int overflow_sampling = 10000;
    vector<string> events = {"L1D:REPLACEMENT", "PAPI_L1_ICM"};
    peptalk::profiling::Init(domain, overflow_sampling, events, false);
    peptalk::profiling::Start();
    peptalk::profiling::Stop();
    auto measurement_1 = peptalk::profiling::GetProfile(0);
    for (int i = 0; i < measurement_1.size(); ++i) {
        cout << events[0] << " = " << measurement_1[i] << endl;
    }
    peptalk::profiling::Cleanup();
}