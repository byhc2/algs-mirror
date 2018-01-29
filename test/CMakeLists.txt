file(GLOB src . "*.cpp")

set(target )
foreach(onesrc ${src})
    get_filename_component(fname ${onesrc} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" tgt ${fname})
    list(APPEND target ${tgt})
endforeach()

foreach(one ${target})
    add_executable(${one} ${one}.cpp)
    target_link_libraries(${one} algs)
    target_link_libraries(${one} utilalgs)
endforeach()
