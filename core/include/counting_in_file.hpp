//
// Created by quepas on 15/04/2020.
//

#ifndef PEP_TALK_CORE_LIBRARIES_COUNTING_IN_FILE_HPP
#define PEP_TALK_CORE_LIBRARIES_COUNTING_IN_FILE_HPP

#include <functional>
#include <string>
#include <vector>
#include "common.hpp"

namespace peptalk::counting_in_file {

    bool Init(const std::string &result_file,
              const std::vector<std::string> &parameters_names,
              const std::vector<std::string> &performance_events,
              unsigned int num_measurements,
              peptalk::error_callback_type &OnErrorOrWarning);

    bool Start(const std::vector<std::string> &parameters, peptalk::error_callback_type &OnErrorOrWarning);

    bool Stop(peptalk::error_callback_type &OnErrorOrWarning);

    bool Close(peptalk::error_callback_type &OnErrorOrWarning);

}

#endif //PEP_TALK_CORE_LIBRARIES_COUNTING_IN_FILE_HPP
