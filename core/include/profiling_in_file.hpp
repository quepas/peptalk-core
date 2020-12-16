//
// Created by quepas on 14/02/2020.
//

#ifndef PEP_TALK_PROFILING_HPP
#define PEP_TALK_PROFILING_HPP

#include <string>
#include <vector>
#include <functional>
#include "common.hpp"

namespace peptalk::profiling_in_file {

    bool
    Init(const std::string &profiling_result_file, const std::string &overflow_event, int overflow_threshold,
         const std::vector<std::string> &measured_events, bool include_instruction_address,
         peptalk::error_callback_type &OnErrorOrWarning);

    bool Start(const std::string &trace_header, peptalk::error_callback_type &OnErrorOrWarning);

    bool Stop(peptalk::error_callback_type &OnErrorOrWarning);

    bool Close(peptalk::error_callback_type &OnErrorOrWarning);

}

#endif //PEP_TALK_PROFILING_HPP
