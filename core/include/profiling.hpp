//
// Created by quepas on 14/02/2020.
//

#ifndef PEP_TALK_CORE_LIBRARIES_PROFILING_HPP
#define PEP_TALK_CORE_LIBRARIES_PROFILING_HPP

#include <string>
#include <vector>
#include <functional>
#include "common.hpp"

namespace peptalk::profiling {

    bool
    Init(const std::string &overflow_event, int overflow_threshold,
         const std::vector<std::string> &measured_events, bool include_instruction_address,
         peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    bool Start(peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    bool Stop(peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    bool Cleanup(peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    const std::vector<peptalk::measurement_type>& GetProfile(int index);

    const std::vector<peptalk::inst_address_type>& GetInstructionAddress();

}

#endif //PEP_TALK_CORE_LIBRARIES_PROFILING_HPP