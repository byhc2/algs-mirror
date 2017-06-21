set(algs_src
        algsrandom.cpp
        algsnum.cpp
        algsout.cpp
        algsdraw.cpp
   )

add_library(algs SHARED ${algs_src})
target_link_libraries(algs m)

find_package(PkgConfig)
pkg_search_module(CAIRO REQUIRED cairo)
target_link_libraries(algs ${CAIRO_LIBRARIES})
target_include_directories(algs PUBLIC ${CAIRO_INCLUDE_DIRS})
target_compile_options(algs PUBLIC ${CAIRO_CFLAGS_OTHER})
