//
// Created by quepas on 11/11/2020.
//

#ifndef PEPTALK_CORE_LIBRARIES_COMMON_HPP
#define PEPTALK_CORE_LIBRARIES_COMMON_HPP

#include <functional>
#include <string>

namespace peptalk {

    typedef const std::function<void(const std::string &, const std::string &)> error_callback_type;
    typedef unsigned long long int inst_address_type;
    typedef long long int measurement_type;

    // Default implementation of the error_callback_type
    void StdoutError(const std::string &peptalk_error, const std::string &papi_error);

}

#endif //PEPTALK_CORE_LIBRARIES_COMMON_HPP
