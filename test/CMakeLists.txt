include_directories(AFTER ${CMAKE_SOURCE_DIR}/lib)

add_executable(test1 test1.cpp)
target_link_libraries(test1 algs)

add_executable(test2 test2.cpp)
target_link_libraries(test2 algs)

add_executable(test3 test3.cpp)
target_link_libraries(test3 algs)

add_executable(test4 test4.cpp)
target_link_libraries(test4 algs)

add_executable(sizeof sizeof.cpp)

add_executable(test5 test5.cpp)
