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
add_executable(test6 test6.cpp)
add_executable(test7 test7.cpp)

add_executable(test8 test8.cpp)
target_link_libraries(test8 algs)

add_executable(test9 test9.cpp)
target_link_libraries(test9 algs)

add_executable(test10 test10.cpp)
target_link_libraries(test10 algs)

add_executable(test11 test11.cpp)
target_link_libraries(test11 algs)

add_executable(test12 test12.cpp)
target_link_libraries(test12 algs)

add_executable(test13 test13.cpp)
target_link_libraries(test13 algs)
