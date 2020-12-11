//
// Created by quepas on 14/02/2020.
//

#include "profiling.hpp"

#include <iostream>
#include <papi.h>

using std::cerr;
using std::endl;
using std::function;
using std::string;
using std::to_string;
using std::vector;

using peptalk::error_callback_type;

namespace peptalk::profiling {

    struct ProfilingInfo {
        int event_set = PAPI_NULL;
        std::vector<peptalk::inst_address_type> instruction_address;
        // If dynamic allocation is not possible, create several measurement vectors 1, 2, 3, ...
        // TODO: use std::vector for the domain only!
        std::vector<peptalk::measurement_type>* measurements = nullptr;
        int overflow_event_codes = 0;
        int overflow_threshold = 1e4;
        bool has_inst_address = false;
    } global_profiling_info;

    void OverflowCallback(int event_set, void *address, long long overflow_vector, void *context) {
        const auto num_counters = PAPI_num_events(event_set);
        long long int counter_values[num_counters];

        int retval;
        if ((retval = PAPI_read(event_set, counter_values)) == PAPI_OK) {
            // Write measurements
            for (int i = 0; i < num_counters; ++i) {
                global_profiling_info.measurements[i].push_back(counter_values[i]);
            }
            // Write instruction address
            if (global_profiling_info.has_inst_address) {
                global_profiling_info.instruction_address.push_back(reinterpret_cast<peptalk::inst_address_type>(address));
            }
        } else {
            cerr << "Failed at reading overflow values" << PAPI_strerror(retval) << std::endl;
        }
    }

    bool
    Init(const std::vector<std::string> &measured_events, bool include_instruction_address,
         int overflow_threshold, peptalk::error_callback_type &OnErrorOrWarning /*= peptalk::StdoutError*/) {
        auto num_events = measured_events.size();
        global_profiling_info.overflow_threshold = overflow_threshold;
        global_profiling_info.measurements = new vector<measurement_type>[num_events];
        global_profiling_info.has_inst_address = include_instruction_address;

        int retval;
        if (!PAPI_is_initialized()) {
            retval = PAPI_library_init(PAPI_VER_CURRENT);
            if (retval != PAPI_VER_CURRENT) {
                OnErrorOrWarning("PAPI initialisation failed", PAPI_strerror(retval));
                return false;
            }
        }
        global_profiling_info.event_set = PAPI_NULL;
        if ((retval = PAPI_create_eventset(&global_profiling_info.event_set)) != PAPI_OK) {
            OnErrorOrWarning("Failed to create an event set", PAPI_strerror(retval));
            return false;
        }

        int event_codes[num_events];
        for (size_t idx = 0; idx < num_events; ++idx) {
            auto event_name = measured_events[idx];
            if ((PAPI_event_name_to_code(event_name.c_str(), &event_codes[idx])) != PAPI_OK) {
                OnErrorOrWarning("Failed to retrieve code for event" + event_name, PAPI_strerror(retval));
                return false;
            }
        }
        global_profiling_info.overflow_event_codes = event_codes[0];
        if ((retval = PAPI_add_events(global_profiling_info.event_set, event_codes, num_events)) !=
            PAPI_OK) {
            OnErrorOrWarning("Failed to add performance events to the event set", PAPI_strerror(retval));
            return false;
        }
        return true;
    }

    bool Start(const std::function<void(const std::string &, const std::string &)> &OnErrorOrWarning) {
        int retval;
        if ((retval = PAPI_overflow(global_profiling_info.event_set, global_profiling_info.overflow_event_codes,
                                    global_profiling_info.overflow_threshold, 0, OverflowCallback)) != PAPI_OK) {
            OnErrorOrWarning("Failed to start the profiling", PAPI_strerror(retval));
            return false;
        }
        if ((retval = PAPI_start(global_profiling_info.event_set)) != PAPI_OK) {
            OnErrorOrWarning("Failed to start the profiling", PAPI_strerror(retval));
            return false;
        }
        return true;
    }

    bool Stop(const function<void(const string &, const string &)> &OnErrorOrWarning) {
        auto num_events = PAPI_num_events(global_profiling_info.event_set);
        long long counter_values[num_events];
        int retval;

        if ((retval = PAPI_stop(global_profiling_info.event_set, counter_values)) != PAPI_OK) {
            OnErrorOrWarning("Failed to stop the profiling", PAPI_strerror(retval));
            return false;
        }
        for (int i = 0; i < num_events; ++i) {
            global_profiling_info.measurements[i].push_back(counter_values[i]);
        }

        if ((retval = PAPI_reset(global_profiling_info.event_set)) != PAPI_OK) {
            OnErrorOrWarning("Failed to reset the counters", PAPI_strerror(retval));
            return false;
        }
        // Detach the overflow callback and reset the overflow sampling
        if ((retval = PAPI_overflow(global_profiling_info.event_set, global_profiling_info.overflow_event_codes,
                                    0, 0, OverflowCallback)) != PAPI_OK) {
            OnErrorOrWarning("Failed to reset the overflow profiling", PAPI_strerror(retval));
            return false;
        }
        return true;
    }

    bool Cleanup(error_callback_type &OnErrorOrWarning) {
        int retval;
        if ((retval = PAPI_cleanup_eventset(global_profiling_info.event_set)) != PAPI_OK) {
            OnErrorOrWarning("Failed to cleanup the event set", PAPI_strerror(retval));
            return false;
        }
        if ((retval = PAPI_destroy_eventset(&global_profiling_info.event_set)) != PAPI_OK) {
            OnErrorOrWarning("Failed to destroy the event set", PAPI_strerror(retval));
            return false;
        }
        PAPI_shutdown();
        return true;
    }

    const std::vector<peptalk::measurement_type>& GetProfile(int index) {
        return global_profiling_info.measurements[index];
    }

    const std::vector<peptalk::inst_address_type>& GetInstructionAddress() {
        return global_profiling_info.instruction_address;
    }

}