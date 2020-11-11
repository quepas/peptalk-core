//
// Created by quepas on 11/11/2020.
//

#include <iostream>
#include "common.hpp"

using namespace peptalk;
using std::string;

void StdoutError(const string &peptalk_error, const string &papi_error) {
    std::cout << "Error\n"
              << "\tPeptalk=" << peptalk_error
              << "\tPAPI=" << papi_error << std::endl;
}
