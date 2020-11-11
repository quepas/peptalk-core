//
// Created by quepas on 11/11/2020.
//

#ifndef PEPTALK_CORE_LIBRARIES_COUNTING_HPP
#define PEPTALK_CORE_LIBRARIES_COUNTING_HPP

#include <string>
#include <vector>
#include "common.hpp"

namespace peptalk::counting {

    bool Init(const std::vector<std::string>& performance_events,
              peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    bool Start(peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    std::vector<peptalk::measurement_type> Stop(peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

}

#endif //PEPTALK_CORE_LIBRARIES_COUNTING_HPP
