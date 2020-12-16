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

    /*
     * The first measured event is the overflow event
     */
    bool
    Init(const std::vector<std::string> &measured_events, bool include_instruction_address,
         int overflow_threshold, peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    bool Start(peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    bool Stop(peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    bool Cleanup(peptalk::error_callback_type &OnErrorOrWarning = peptalk::StdoutError);

    const std::vector<peptalk::measurement_type>& GetProfile(int index);

    std::string GetProfileEvent(int index);

    int GetNumProfile();

    long GetProfileSize();

    bool HasInstructionAddress();

    const std::vector<peptalk::inst_address_type>& GetInstructionAddress();

}

#endif //PEP_TALK_CORE_LIBRARIES_PROFILING_HPP
