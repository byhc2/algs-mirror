file(GLOB src . "*.cpp")

set(target )
foreach(onesrc ${src})
    get_filename_component(fname ${onesrc} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" tgt ${fname})
    list(APPEND target ${tgt})
endforeach()

# 获取当前源文件路径的名字
get_filename_component(basename ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# 若basename中有空格，替换成下划线
string(REPLACE " " "_" basename ${basename})

foreach(one ${target})
    add_executable(${one} ${one}.cpp)
    target_link_libraries(${one} algs)
    target_link_libraries(${one} utilalgs)
    set_target_properties(${one}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${basename}
        )
endforeach()
