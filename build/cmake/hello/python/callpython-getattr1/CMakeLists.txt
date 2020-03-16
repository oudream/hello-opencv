
### callpython-getattr1
set(gsl_callpython-getattr1_files
        module1.h
        module1.cpp
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/python/callpython-getattr1 "${gsl_callpython-getattr1_files}" gsl_callpython-getattr1_files_filepaths)

add_executable(callpython-getattr1
        ${gsl_callpython-getattr1_files_filepaths}
        )

add_custom_command(
        TARGET callpython-getattr1
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy ${gs_hello_path}/python/callpython-getattr1/multiply.py
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/multiply.py
        )

target_link_libraries(callpython-getattr1
        ${PYTHON_LIBRARIES}
        )

mc_target_link_libraries(callpython-getattr1)

#compile static
mc_build_with_cc_static()
