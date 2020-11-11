//
// Created by quepas on 11/11/2020.
//

#include <papi.h>
#include "counting.hpp"

using namespace peptalk;
using namespace peptalk::counting;
using std::string;
using std::vector;

struct CountingInfo {
    int event_set = PAPI_NULL;
} global_counting_info;

bool Init(const vector<string>& performance_events, error_callback_type &OnErrorOrWarning /*= peptalk::StdoutError*/) {
    int retval;
    if (!PAPI_is_initialized()) {
        retval = PAPI_library_init(PAPI_VER_CURRENT);
        if (retval != PAPI_VER_CURRENT) {
            OnErrorOrWarning("PAPI initialisation failed", PAPI_strerror(retval));
            return false;
        }
    }
    global_counting_info.event_set = PAPI_NULL;
    if ((retval = PAPI_create_eventset(&global_counting_info.event_set)) != PAPI_OK) {
        OnErrorOrWarning("Failed to create an event set", PAPI_strerror(retval));
        return false;
    }
    int codes[performance_events.size()];
    for (size_t idx = 0; idx < performance_events.size(); ++idx) {
        auto event_name = performance_events[idx];
        if ((PAPI_event_name_to_code(event_name.c_str(), &codes[idx])) != PAPI_OK) {
            OnErrorOrWarning("Failed to retrieve code for event: " + event_name, PAPI_strerror(retval));
            return false;
        }
    }
    if ((retval = PAPI_add_events(global_counting_info.event_set, codes, performance_events.size())) != PAPI_OK) {
        OnErrorOrWarning("Failed to add performance events to the event set.", PAPI_strerror(retval));
        return false;
    }
    return true;
}

bool Start(peptalk::error_callback_type &OnErrorOrWarning /*= peptalk::StdoutError*/) {
    int retval;
    if ((retval = PAPI_start(global_counting_info.event_set)) != PAPI_OK) {
        OnErrorOrWarning("Failed to start the profiling.", PAPI_strerror(retval));
        return false;
    }
    return true;
}

vector<measurement_type> Stop(peptalk::error_callback_type &OnErrorOrWarning /*= peptalk::StdoutError*/) {
    auto num_perf_events = PAPI_num_events(global_counting_info.event_set);
    long long values[num_perf_events];
    int retval;

    if ((retval = PAPI_stop(global_counting_info.event_set, values)) != PAPI_OK) {
        OnErrorOrWarning("Failed to start the profiling.", PAPI_strerror(retval));
        return {};
    }
    if ((retval = PAPI_reset(global_counting_info.event_set)) != PAPI_OK) {
        OnErrorOrWarning("Failed to reset the counters.", PAPI_strerror(retval));
        return {};
    }
    vector<measurement_type> measurements;
    measurements.reserve(num_perf_events);
    for (int idx = 0; idx < num_perf_events; ++idx) {
        measurements.push_back(values[idx]);
    }
    return measurements;
}

