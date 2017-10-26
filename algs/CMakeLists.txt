set(utilalgs_src
    counter.cpp
    geometry.cpp
    misc.cpp
   )

add_library(utilalgs SHARED ${utilalgs_src})
target_link_libraries(utilalgs algs)
