set(algsprg_src
        binary_search
   )

get_filename_component(basename ${CMAKE_CURRENT_SOURCE_DIR} NAME)

foreach(one ${algsprg_src})
    add_executable(${one} ${one}.cpp)
    target_link_libraries(${one} algs)
    set_target_properties(${one}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${basename}
        )
endforeach()
