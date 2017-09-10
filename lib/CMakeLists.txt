set(algs_src
        algsrandom.cpp
        algsnum.cpp
        algsout.cpp
        algsdraw.cpp
        algsmath.cpp
   )

add_library(algs SHARED ${algs_src})
target_link_libraries(algs m)

find_package(PkgConfig)
pkg_search_module(CAIRO REQUIRED cairo)
pkg_search_module(X11 REQUIRED x11)
target_link_libraries(algs ${CAIRO_LIBRARIES})
target_include_directories(algs PUBLIC ${CAIRO_INCLUDE_DIRS})
target_compile_options(algs PUBLIC ${CAIRO_CFLAGS_OTHER})

target_link_libraries(algs ${X11_LIBRARIES})
target_include_directories(algs PUBLIC ${X11_INCLUDE_DIRS})
target_compile_options(algs PUBLIC ${X11_CFLAGS_OTHER})
