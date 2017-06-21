set(algs_src
        algsrandom.cpp
        algsnum.cpp
        algsout.cpp
   )

add_library(algs SHARED ${algs_src})
target_link_libraries(algs m)
