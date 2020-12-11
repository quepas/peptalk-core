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
    vector<string> events = {"PAPI_SP_OPS"};
    peptalk::profiling::Init(domain, overflow_sampling, events, true);
    peptalk::profiling::Start();
    float acc = 1.0f;
    // Should be exactly 10k single precision floating-point operations
    for (int k = 0; k < 10000; ++k) {
        acc = acc * -1.001f;
    }
    peptalk::profiling::Stop();
    cout << "acc=" << acc << endl;
    auto inst = peptalk::profiling::GetProfile(0);
    auto fp_ops = peptalk::profiling::GetProfile(1);
    auto address = peptalk::profiling::GetInstructionAddress();
    for (int i = 0; i < fp_ops.size(); ++i) {
        cout << domain << "=" << inst[i] << "; "
             << events[0] << "=" << fp_ops[i] << "; @"
             << address[i] << endl;
    }
    peptalk::profiling::Cleanup();
}