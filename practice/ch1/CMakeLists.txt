set(target
    1_1
    1_3
    1_5
    1_6
    1_7
    1_9
    1_10
    1_11
    1_12
    1_13
    1_14
    1_15
    1_16
    1_18
    )

# 获取当前源文件路径的名字
get_filename_component(basename ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# 若basename中有空格，替换成下划线
string(REPLACE " " "_" basename ${basename})

foreach(one ${target})
    add_executable(${one} ${one}.cpp)
    target_link_libraries(${one} algs)
    set_target_properties(${one}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${basename}
        )
endforeach()
