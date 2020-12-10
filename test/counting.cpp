//
// Created by quepas on 11/11/2020.
//

#include <iostream>
#include "counting.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    vector<string> events = {"L1D:REPLACEMENT", "PAPI_L1_ICM"};
    peptalk::counting::Init(events);
    peptalk::counting::Start();
    auto measurements = peptalk::counting::Stop();
    for (int i = 0; i < events.size(); ++i) {
        cout << events[i] << " = " << measurements[i] << endl;
    }
    peptalk::counting::Cleanup();
}