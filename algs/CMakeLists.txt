set(utilalgs_src
    counter.cpp
   )

add_library(utilalgs SHARED ${utilalgs_src})
target_link_libraries(utilalgs algs)
