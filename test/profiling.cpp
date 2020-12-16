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
    int overflow_sampling = 10000;
    vector<string> events = {"PAPI_TOT_INS", "PAPI_SP_OPS"};
    peptalk::profiling::Init(events, true, overflow_sampling);
    peptalk::profiling::Start();
    float acc = 1.0f;
    // Should be exactly 10k single precision floating-point operations
    for (int k = 0; k < 10000; ++k) {
        acc = acc * -1.001f;
    }
    peptalk::profiling::Stop();
    cout << "Computation result = " << acc << endl;
    // Display information about profiles
    cout << "Profiles number = " << peptalk::profiling::GetNumProfile() << endl;
    cout << "Has instruction address = " << peptalk::profiling::HasInstructionAddress() << endl;
    // Display profile values
    for (int measurement_idx = 0; measurement_idx < peptalk::profiling::GetProfileSize(); ++measurement_idx) {
        for (int profile_idx = 0; profile_idx < peptalk::profiling::GetNumProfile(); ++profile_idx) {
            cout << peptalk::profiling::GetProfileEvent(profile_idx) << (profile_idx == 0 ? "* " : " ") << "= " << peptalk::profiling::GetProfile(profile_idx)[measurement_idx] << "; ";
        }
        if (peptalk::profiling::HasInstructionAddress()) {
            cout << "@" << peptalk::profiling::GetInstructionAddress()[measurement_idx];
        }
        cout << endl;
    }
    peptalk::profiling::Cleanup();
}