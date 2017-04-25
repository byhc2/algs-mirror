set(algs_src
        stdrandom.cpp
        stdnum.cpp
   )

add_library(algs SHARED ${algs_src})
target_link_libraries(algs m)
