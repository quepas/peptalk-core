add_library( peptalk_core SHARED src/counting_in_file.cpp src/profiling_in_file.cpp src/timing.cpp src/common.cpp src/counting.cpp)
target_include_directories( peptalk_core PUBLIC include/ )
target_link_libraries( peptalk_core peptalk_io papi )
set_property( TARGET peptalk_core PROPERTY POSITION_INDEPENDENT_CODE ON )

add_library( peptalk_core_static STATIC src/counting_in_file.cpp src/profiling_in_file.cpp src/timing.cpp  src/common.cpp src/counting.cpp)
target_include_directories( peptalk_core_static PUBLIC include/ )
target_link_libraries( peptalk_core_static peptalk_io_static papi stdc++fs )
set_property( TARGET peptalk_core_static PROPERTY POSITION_INDEPENDENT_CODE ON )
