add_executable(test_counting counting.cpp)
target_link_libraries(test_counting peptalk_core stdc++fs)

add_executable(test_profiling profiling.cpp)
target_link_libraries(test_profiling peptalk_core stdc++fs)
